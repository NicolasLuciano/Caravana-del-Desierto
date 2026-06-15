#include "../headers/archivos.h"
#include "../headers/lista.h"
#include "../headers/constantesymacros.h"
#include "../headers/arbol.h"

int cargarConfig(const char* nombreArch, tConfig* configuracion)
{
    FILE *fp;
    fp=fopen(nombreArch, "rt");
    if(!fp)
        return ARCH_ERROR;

    fscanf(fp, "cantidad_posiciones: %d\n", &configuracion->cantCasillas);
    fscanf(fp, "vidas_inicio: %d\n", &configuracion->vidasIniciales);
    fscanf(fp, "maximo_bandidos: %d\n", &configuracion->cantBandidos);
    fscanf(fp, "maximo_premios: %d\n", &configuracion->cantPremios);
    fscanf(fp, "maximo_vidas_extra: %d\n", &configuracion->cantVidasExtra);
    fscanf(fp, "maximo_oasis: %d\n", &configuracion->cantOasis);
    fscanf(fp, "maximo_tormentas: %d", &configuracion->cantTormentas);


    fclose(fp);
    return TODO_OK;
}

int guardarPartida(tPartida partida, const char * nombreArchivo)
{
    FILE * pf;

    pf=fopen(nombreArchivo,"ab");
    if(NULL==pf)
        return ARCH_ERROR;

    fwrite(&partida, sizeof(tPartida), 1, pf);
    fclose(pf);

    return TODO_OK;
}

int guardarTablero(const tLista* tablero, const char* nombreArchivo)
{
    FILE* fp = fopen(nombreArchivo, "wt");
    if(fp == NULL)
        return ARCH_ERROR;
    recorrerListaArchivo(tablero, fp, escribirCasilla);
    fclose(fp);

    return TODO_OK;
}

void escribirCasilla(FILE* fp, const void* dato)
{
    tCasilla casilla = *(tCasilla*)dato;
    char linea[10];

    linea[0] = '\0';

    if(casilla.tipo != VACIA)
        sprintf(linea, "%c ", casilla.tipo);

    if(casilla.jugador == HAY_JUGADOR)
        sprintf(linea + strlen(linea), "%c ", JUGADOR);

    if(casilla.bandido == HAY_BANDIDO)
        sprintf(linea + strlen(linea), "%c ", BANDIDO);

    if(strlen(linea) > 0)
    {
        linea[strlen(linea)-1] = '\0';

        if(strlen(linea) > 1)
            fprintf(fp,"%02d: [%s]\n", casilla.numCasilla, linea);
        else
            fprintf(fp,"%02d: %s\n", casilla.numCasilla, linea);
    }
    else
        fprintf(fp,"%02d: %c\n", casilla.numCasilla, casilla.tipo);
}

int cargarIndices(tArbol *arbol,char *nombreArchivo)
{
    FILE *fp;
    tIndice indice;
    fp = fopen(nombreArchivo,"rb");
    if(!fp)
        return ARCH_ERROR;
    while(fread(&indice,sizeof(indice),1,fp)==1)
        insertarArbol(arbol,&indice,sizeof(indice),compararUsuarios);
    fclose(fp);
    return TODO_OK;
}

int compararUsuarios(const void *a, const void *b)
{
    const tIndice *ua = (tIndice *)a;
    const tIndice *ub = (tIndice *)b;
    return strcmp(ua->nombreDeUsuario,ub->nombreDeUsuario);
}






