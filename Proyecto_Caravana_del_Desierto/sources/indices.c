#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../headers/indices.h"
#include "../headers/archivos.h"
#include "../headers/constantesymacros.h"
void mostrarIndice(void* dato, unsigned tam)
{
    tIndice indice = *(tIndice*)dato;
    printf("%s %d\n",indice.nombreDeUsuario, indice.numRegistro);
}
int compararUsuarios(const void *a, const void *b)
{
    const tIndice *ua = (tIndice *)a;
    const tIndice *ub = (tIndice *)b;
    return strcmp(ua->nombreDeUsuario,ub->nombreDeUsuario);
}

int validarUsuario(const char* usuario)
{
    if(*usuario == '\0')
        return CADENA_INVALIDA;

    while(*usuario)
    {
        if(!isalpha(*usuario) && !isdigit(*usuario) && *usuario != '_' && *usuario != '.')
            return CADENA_INVALIDA;

        usuario++;
    }

    return TODO_OK;
}

int validarNombreApellido(const char* texto)
{
    if(*texto == '\0')
        return CADENA_INVALIDA;
    while(*texto)
    {
        if(!isalpha(*texto) && *texto != ' ')
            return CADENA_INVALIDA;

        texto++;
    }

    return TODO_OK;
}

int leerCadena(char * cadena, int (*validarCad)(const char *))
{
    int validacion;
    if(strchr(cadena, '\n') == NULL)
    {
        int c;
        while((c = getchar()) != '\n' && c != EOF)
            ;

        printf("Demasiados caracteres.\n");
        validacion = CADENA_INVALIDA;
    }
    else
    {
        cadena[strlen(cadena)-1] = '\0';
        validacion = validarCad(cadena);
    }
    return validacion;
}

void cargarArchivoOrdenadoEnIndiceBalanceadoEnvoltorio(tArbol *pa, FILE *fp)
{
    size_t bytes;
    int cantidad;

    fseek(fp, 0, SEEK_END);
    bytes = ftell(fp);
    cantidad = bytes / sizeof(tIndice);

    if (cantidad > 0)
        cargarArchivoOrdenadoEnIndiceBalanceado(pa, fp, INICIO_DEL_ARCHIVO, cantidad-1);
}

void cargarArchivoOrdenadoEnIndiceBalanceado(tArbol *pa, FILE *fp, int inicio,int fin)
{
    size_t medio = (fin+inicio)/2;
    tIndice indice;

    if (inicio > fin)
        return;

    fseek(fp, medio*sizeof(tIndice), SEEK_SET);
    fread(&indice, 1, sizeof(tIndice), fp);

    insertarArbol(pa, &indice, sizeof(tIndice), compararUsuarios);

    cargarArchivoOrdenadoEnIndiceBalanceado(pa, fp, inicio, medio-1);
    cargarArchivoOrdenadoEnIndiceBalanceado(pa, fp, medio+1, fin);
}


void identificarUsuario(tUsuario *usuario, tArbol *arbol)
{
    FILE *pfIndice, *pfUsuarios;
    int resultadoBusqueda, validacion;
    char opcion;
    tIndice indice;
    char cadValidacion[NOMBRE_DE_USUARIO_TAM];

    pfUsuarios = fopen(NOMARCH_USER,"a+b");
    if(!pfUsuarios)
    {
        perror(NOMARCH_USER);
        return;
    }

    pfIndice = fopen(NOMARCH_INDEX, "a+b");
    if(!pfIndice)
    {
        fclose(pfUsuarios);
        perror(NOMARCH_INDEX);
        return;
    }
    cargarArchivoOrdenadoEnIndiceBalanceadoEnvoltorio(arbol,pfIndice);

    do
    {
        opcion=NO;
        system("cls");
        printf("\n====================================\n");
        printf("         INICIO DE SESION\n");
        printf("====================================\n");
        printf("INGRESE NOMBRE DE USUARIO: ");

        do
        {
            fflush(stdin);
            fgets(cadValidacion, sizeof(cadValidacion), stdin);
            validacion=leerCadena(cadValidacion,validarUsuario);
            if(validacion==CADENA_INVALIDA)
                printf("\n---NOMBRE DE USUARIO INVALIDO---\nINGRESE NUEVAMENTE: ");
        }
        while(validacion==CADENA_INVALIDA);
        strcpy(indice.nombreDeUsuario,cadValidacion);

        resultadoBusqueda=buscarEnArbol(arbol,&indice,sizeof(indice),compararUsuarios);

        if(NO_ENCONTRADO!=resultadoBusqueda)
        {
            fseek(pfUsuarios,indice.numRegistro * sizeof(tUsuario),SEEK_SET);

            fread(usuario,sizeof(tUsuario),1,pfUsuarios);
            printf("\nUSUARIO ENCONTRADO.\n");
            printf("SOS %s %s? (S/N)", usuario->nombre, usuario->apellido);
            do
            {
                scanf(" %c",&opcion);
                opcion=toupper(opcion);
                if(opcion!=SI && opcion!=NO)
                    printf("OPCION INVALIDA. INGRESE NUEVAMENTE\n");
            }
            while(opcion!=SI && opcion!=NO);
            if(SI==opcion)
            {
                printf("_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");
                printf("   BIENVENIDO NUEVAMENTE %s!\n",usuario->nombreDeUsuario);
                printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-\n");
                system("pause");
            }
        }

    }
    while( NO==opcion && NO_ENCONTRADO!=resultadoBusqueda);

    if(NO_ENCONTRADO==resultadoBusqueda)
    {
        printf("\n\n====================================\n");
        printf("        REGISTRO DE USUARIO\n");
        printf("====================================\n");
        printf("\nINGRESE SU NOMBRE: ");

        strcpy(usuario->nombreDeUsuario,indice.nombreDeUsuario);
        do
        {
            fflush(stdin);
            fgets(cadValidacion, sizeof(cadValidacion), stdin);
            validacion=leerCadena(cadValidacion,validarNombreApellido);
            if(validacion==CADENA_INVALIDA)
                printf("\n---NOMBRE INVALIDO---\nINGRESE NUEVAMENTE: ");
        }
        while(validacion==CADENA_INVALIDA);
        strcpy(usuario->nombre,cadValidacion);

        printf("\nINGRESE SU APELLIDO: ");

        do
        {
            fflush(stdin);
            fgets(cadValidacion, sizeof(cadValidacion), stdin);
            validacion=leerCadena(cadValidacion,validarNombreApellido);
            if(validacion==CADENA_INVALIDA)
                printf("\n---APELLIDO INVALIDO---\nINGRESE NUEVAMENTE: ");
        }
        while(validacion==CADENA_INVALIDA);
        strcpy(usuario->apellido,cadValidacion);

        fflush(pfUsuarios);
        fseek(pfUsuarios,0,SEEK_END);
        indice.numRegistro = ftell(pfUsuarios) / sizeof(tUsuario);

        fwrite(usuario,sizeof(tUsuario),1,pfUsuarios);

        fflush(pfIndice);
        fwrite(&indice,sizeof(tIndice),1,pfIndice);

    }

    fclose(pfIndice);
    fclose(pfUsuarios);
}
