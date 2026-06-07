#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include <time.h>

int generarTablero(tLista *tablero,const tConfig configuracion, tBandido * bandidos)
{
    int * vecPosiciones, *auxVec,i;
    tCasilla casilla;
    srand(time(NULL));


    vecPosiciones=malloc(sizeof(int)*configuracion.cantCasillas);
    if(NULL==vecPosiciones)
        return SIN_MEM;


    casilla.tipo = 'I';
    casilla.numCasilla=1;
    insertarFinLis(tablero, &casilla, sizeof(tCasilla));

    casilla.tipo = '.';
    for( i =1; i< configuracion.cantCasillas-1; i++)
    {
        casilla.numCasilla=i+1;
        insertarFinLis(tablero, &casilla, sizeof(tCasilla));
    }

    casilla.numCasilla=configuracion.cantCasillas;
    casilla.tipo = 'S';
    insertarFinLis(tablero, &casilla, sizeof(tCasilla));

    auxVec=vecPosiciones;

    mezclarPosiciones(vecPosiciones,configuracion.cantCasillas);
    distribuirPremios(tablero,configuracion.cantPremios,&auxVec);
    distribuirOasis(tablero,configuracion.cantOasis,&auxVec);
    distribuirTormentas(tablero,configuracion.cantTormentas,&auxVec);
    distribuirVidasExtra(tablero,configuracion.cantVidasExtra,&auxVec);
    distribuirBandidos(tablero, bandidos, configuracion.cantBandidos,&auxVec);
    free(vecPosiciones);
    return 0;
}

void mezclarPosiciones(int * vecPosiciones,int cantCasillas)
{
    int i,j,aux;

    for(i=0;i<cantCasillas;i++)
        vecPosiciones[i]=i;

    for(i = cantCasillas-2; i > 1; i--)
    {
        j = (rand() % i) + 1;

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
        memcpy(nodoConfig->dato,&casilla,sizeof(casilla)); //CAMBIAR PARA NO ACCEDER DIRECTAMENTE AL DATO
    }
}

void distribuirBandidos(tLista * tablero, tBandido * bandidos, int cantBandidos, int ** vecPosiciones)
{
    int i;
    tNodoLista * nodoMov;

    for(i=0;i<cantBandidos;i++)
    {
        nodoMov=*tablero;
        (*vecPosiciones)++;
        moverEnLista(&nodoMov,**vecPosiciones,ADELANTE);
        (bandidos+i)->posicion=nodoMov;
        (bandidos+i)->direccion=ADELANTE;
    }
}

void mostrarTablero(const tLista* tablero, const tBandido*bandidos, unsigned cantBandidos)
{
    tNodoLista * tableroAux;
    tCasilla casilla;
    int i;

    tableroAux=*tablero;
    while(tableroAux->nodoSig != *tablero )
    {
        i=0;
        recuperarDatoLista(tableroAux,&casilla,sizeof(tCasilla));

        while(i<cantBandidos && tableroAux!=(bandidos+i)->posicion)
            i++;

        if(tableroAux==(bandidos+i)->posicion)
            printf("%02d:B\n",casilla.numCasilla);
        else
            printf("%02d:%c\n",casilla.numCasilla,casilla.tipo);

        tableroAux=tableroAux->nodoSig;
    }
    recuperarDatoLista(tableroAux,&casilla,sizeof(tCasilla));
    printf("%02d:%c\n",casilla.numCasilla,casilla.tipo);

}
