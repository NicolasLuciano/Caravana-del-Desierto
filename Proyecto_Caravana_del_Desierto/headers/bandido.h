#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED
#include "lista.h"
#include "cola.h"
typedef struct
{
    tNodoLista *posicion;
    char vivo;
    int direccion;
} tBandido;


tBandido * crearBandidos( unsigned cantBandidos);

void moverBandidos(tLista *tablero, tBandido *vBandidos,tCola *colaMovimientos,unsigned cantBandidos);
#endif // BANDIDO_H_INCLUDED
