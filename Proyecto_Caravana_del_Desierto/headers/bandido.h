#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED
#include "../headers/lista.h"
#include "../headers/cola.h"
#include "../headers/constantesymacros.h"


typedef struct
{
    tNodoLista *posicion;
    char vivo;
    int direccion;
} tBandido;


tBandido * crearBandidos( unsigned cantBandidos);

void moverBandidos(tLista *tablero, tBandido *vBandidos,tCola *colaMovimientos,unsigned cantBandidos);
#endif // BANDIDO_H_INCLUDED
