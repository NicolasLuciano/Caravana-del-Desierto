#include <stdio.h>
#include <string.h>
#include "../headers/indices.h"
#include "../headers/arbol.h"
#include "../headers/archivos.h"
void identificarUsuario(tUsuario *usuario)
{
    FILE *pfIndice, *pfUsuarios;
    int resultadoBusqueda;
    char validacion;
    tIndice indice;
    tArbol arbol;

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
    crearArbol(&arbol);
    cargarIndices(&arbol,NOMARCH_INDEX);
    validacion=NO;
    do
    {
        printf("INGRESE NOMBRE DE USUARIO: ");
        scanf("%s", indice.nombreDeUsuario);
        resultadoBusqueda=buscarEnArbol(&arbol,&indice,sizeof(indice),compararUsuarios);

        if(NO_ENCONTRADO!=resultadoBusqueda)
        {
            fseek(pfUsuarios,indice.numRegistro * sizeof(tUsuario),SEEK_SET);

            fread(usuario,sizeof(tUsuario),1,pfUsuarios);
            printf("SOS %s %s? SI(S)/NO(N)", usuario->nombre, usuario->apellido);
            do
            {
                scanf(" %c",&validacion);
                if(validacion!=SI && validacion!=NO)
                    printf("OPCION INVALIDA. INGRESE NUEVAMENTE\n");
            }
            while(validacion!=SI && validacion!=NO);
            if(SI==validacion)
                printf("BIENVENIDO NUEVAMENTE %s!\n",usuario->nombreDeUsuario);
            system("pause");
        }

    }
    while( NO==validacion && NO_ENCONTRADO!=resultadoBusqueda);

    if(NO_ENCONTRADO==resultadoBusqueda)
    {
        printf("BIENVENIDO %s POR FAVOR INGRESE SU NOMBRE: ",indice.nombreDeUsuario);
        scanf("%s",usuario->nombre);
        printf("\nINGRESE SU APELLIDO: ");
        scanf("%s",usuario->apellido);
        strcpy(usuario->nombreDeUsuario,indice.nombreDeUsuario);

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

