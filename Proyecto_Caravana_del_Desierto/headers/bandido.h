#ifndef BANDIDO_H_INCLUDED
#define BANDIDO_H_INCLUDED
#include "lista.h"
typedef struct
{
    tNodoLista *posicion;
    char vivo;
    int direccion;
} tBandido;

tBandido * crearBandidos( unsigned cantBandidos);

#endif // BANDIDO_H_INCLUDED
