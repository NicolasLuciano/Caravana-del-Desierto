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

    cargarIndices(&arbol,NOMARCH_INDEX);
    rewind(pfIndice);

    do
    {
        printf("INGRESE NOMBRE DE USUARIO: ");
        scanf("%s", indice.nombreDeUsuario);
        resultadoBusqueda=buscarEnArbol(&arbol,&indice,sizeof(indice),compararUsuarios);
        printf("-->%d",resultadoBusqueda);
        system("pause");

        if(NO_ENCONTRADO!=resultadoBusqueda)
        {
            fseek(pfUsuarios,indice.numRegistro,SEEK_SET);

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
    while(NO_ENCONTRADO==resultadoBusqueda && NO==validacion);

    if(NO_ENCONTRADO==resultadoBusqueda)
    {


        printf("BIENVENIDO %s POR FAVOR INGRESE SU NOMBRE: ",indice.nombreDeUsuario);
        scanf("%s",usuario->nombre);
        printf("\nINGRESE SU APELLIDO: ");
        scanf("%s",usuario->apellido);
        strcpy(usuario->nombreDeUsuario,indice.nombreDeUsuario);

        fflush(pfUsuarios);
        fwrite(usuario,sizeof(*usuario),1,pfUsuarios);
        fseek(pfUsuarios,-1,SEEK_CUR);
        indice.numRegistro = ftell(pfUsuarios)/sizeof(tUsuario);

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

