#include <stdio.h>
#include <string.h>
#include "../headers/indices.h"
#include "../headers/archivos.h"
#include <ctype.h>


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

    pfIndice = fopen(NOMARCH_INDEX, "ab");
    if(!pfIndice)
    {
        fclose(pfUsuarios);
        perror(NOMARCH_INDEX);
        return;
    }
    cargarIndices(arbol,NOMARCH_INDEX);
    opcion=NO;

    do
    {
        system("cls");
        printf("\n====================================\n");
        printf("         INICIO DE SESION\n");
        printf("====================================\n");
        printf("INGRESE NOMBRE DE USUARIO: ");

        do
        {
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

        fwrite(usuario,sizeof(*usuario),1,pfUsuarios);

        fflush(pfIndice);
        fwrite(&indice,sizeof(indice),1,pfIndice);

    }

    fclose(pfIndice);
    fclose(pfUsuarios);
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
