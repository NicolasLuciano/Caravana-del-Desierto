#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED
#include "lista.h"
typedef struct
{
    tNodoLista *posicion;
    char vivo;
} tBandido;

tBandido * crearBandidos( unsigned cantBandidos);

#endif // BANDIDO_H_INCLUDED
