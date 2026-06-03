#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"

int generarTablero(tLista *tablero,const tConfig *configuracion)
{
    int * vecPosiciones, *auxVec;
    char casilla;

    vecPosiciones=malloc(sizeof(int)*configuracion->cantCasillas);
    if(NULL==vecPosiciones)
        return SIN_MEM;


    casilla = 'I';
    insertarFinLis(tablero, &casilla, sizeof(casilla));

    casilla = '.';
    for(int i =1; i< configuracion->cantCasillas-1; i++)
            insertarFinLis(tablero, &casilla, sizeof(casilla));

    casilla = 'F';
    insertarFinLis(tablero, &casilla, sizeof(casilla));

    auxVec=vecPosiciones;

    mezclarPosiciones(vecPosiciones,configuracion->cantCasillas);

    distribuirPremios(tablero,configuracion->cantPremios,&auxVec);

    distribuirOasis(tablero,configuracion->cantOasis,&auxVec);
    distribuirTormentas(tablero,configuracion->cantTormentas,&auxVec);
    distribuirVidasExtra(tablero,configuracion->cantVidasExtra,&auxVec);
    free(vecPosiciones);
    return 0;
}

void mezclarPosiciones(int * vecPosiciones,int cantCasillas)
{
    int i,j,aux;

    for(i=0;i<cantCasillas;i++)
        vecPosiciones[i]=i;

    for(i = cantCasillas-2; i > 0; i--)
    {
        j = rand() % (i + 1);

        aux = vecPosiciones[i];
        vecPosiciones[i] = vecPosiciones[j];
        vecPosiciones[j] = aux;
    }
}


void distribuirPremios(tLista* tablero,int cantPremios, int ** vecPosiciones)
{
    char casilla;
    tNodoLista * nodoConfig;
    int i;
    casilla = 'P';
    for(i = 0; i < cantPremios; i++)
    {
        nodoConfig=*tablero;
        (*vecPosiciones)++;
        moverEnLista(&nodoConfig,**vecPosiciones,ADELANTE);
        memcpy(nodoConfig->dato,&casilla,sizeof(casilla));
    }
}

void distribuirOasis(tLista* tablero,int cantOasis,int ** vecPosiciones)
{
    char casilla;
    tNodoLista * nodoConfig;
    int i;
    casilla = 'O';
    for(i = 0; i < cantOasis; i++)
    {
        nodoConfig=*tablero;
        (*vecPosiciones)++;
        moverEnLista(&nodoConfig,**vecPosiciones,ADELANTE);
        memcpy(nodoConfig->dato,&casilla,sizeof(casilla));
    }
}

void distribuirVidasExtra(tLista* tablero,int cantVidasExtras,int ** vecPosiciones)
{
    char casilla;
    tNodoLista * nodoConfig;
    int i;
    casilla = 'V';
    for(i = 0; i < cantVidasExtras; i++)
    {
        nodoConfig=*tablero;
        (*vecPosiciones)++;
        moverEnLista(&nodoConfig,**vecPosiciones,ADELANTE);
        memcpy(nodoConfig->dato,&casilla,sizeof(casilla));
    }
}

void distribuirTormentas(tLista* tablero, int cantTormentas, int ** vecPosiciones)
{
    char casilla;
    tNodoLista * nodoConfig;
    int i;
    casilla = 'T';
    for(i = 0; i < cantTormentas; i++)
    {
        nodoConfig=*tablero;
        (*vecPosiciones)++;
        moverEnLista(&nodoConfig,**vecPosiciones,ADELANTE);
        memcpy(nodoConfig->dato,&casilla,sizeof(casilla));
    }
}
