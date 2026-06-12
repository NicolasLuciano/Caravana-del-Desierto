#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED
#include "../headers/lista.h"
#include "../headers/cola.h"
#include "../headers/constantesymacros.h"


typedef struct
{
    tLista posicion;
    unsigned vivo;
    char direccion;
} tBandido;


tBandido * crearBandidos( unsigned cantBandidos);

void encolarBandidos(tBandido *vBandidos,tCola *colaMovimientos,unsigned cantBandidos, unsigned cantCasillas);
#endif // BANDIDO_H_INCLUDED
