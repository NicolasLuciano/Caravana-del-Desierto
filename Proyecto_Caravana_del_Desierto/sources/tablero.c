#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"

int generarTablero(tLista *tablero,const tConfig *configuracion)
{
    int * vecPosiciones, *auxVec;
    tCasilla c;

    vecPosiciones=malloc(sizeof(int)*configuracion->cantCasillas);
    if(NULL==vecPosiciones)
        return SIN_MEM;

    c.premio=0;
    c.vidaExtra=0;
    c.oasis=0;
    c.tormenta=0;
    c.salida=0;


    c.inicio=1;
    insertarFinLis(tablero, &c, sizeof(tCasilla));
    c.inicio=0;

    for(int i =1; i< configuracion->cantCasillas-1; i++)
        {
            insertarFinLis(tablero, &c, sizeof(tCasilla));
        }

    c.salida=1;
    insertarFinLis(tablero, &c, sizeof(tCasilla));

    auxVec=vecPosiciones;

    mezclarPosiciones(vecPosiciones,configuracion->cantCasillas);

    distribuirPremios(tablero,configuracion->cantPremios,&auxVec);

    distribuirOasis(tablero,configuracion->cantCasillas,configuracion->cantOasis);
    distribuirTormentas(tablero,configuracion->cantCasillas,configuracion->cantTormentas);
    distribuirVidasExtra(tablero,configuracion->cantCasillas,configuracion->cantVidasMax);
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
    tCasilla c;
    tNodoLista * nodoConfig;
    int i;

    c.premio=1;
    c.vidaExtra=0;
    c.oasis=0;
    c.tormenta=0;
    c.salida=0;
    c.salida=0;

    for(i = 0; i < cantPremios; i++)
    {
        nodoConfig=*tablero;
        (*vecPosiciones)++;
        moverEnLista(&nodoConfig,**vecPosiciones,ADELANTE);

    }
}

void distribuirOasis(tLista* tablero,int cantCasillas,int cantOasis)
{
    tCasilla* c;
    int i;
    for(i = 0; i < cantOasis; i++)
    {
        c = obtenerCasillaLibreAleatoria(tablero,cantCasillas);
        c->oasis = 1;
    }
}

void distribuirVidasExtra(tLista* tablero,int cantCasillas,int cantVidasExtra)
{
    tCasilla* c;
    int i;
    for(i = 0; i < cantVidasExtra; i++)
    {
        c = obtenerCasillaLibreAleatoria(tablero,cantCasillas);
        c->vidaExtra = 1;
    }
}

void distribuirTormentas(tLista* tablero, int cantCasillas, int cantTormentas)
{
    tCasilla* c;
    int i;
    for(i = 0; i < cantTormentas; i++)
    {
        c = obtenerCasillaLibreAleatoria(tablero,cantCasillas);
        c->tormenta = 1;
    }
}

