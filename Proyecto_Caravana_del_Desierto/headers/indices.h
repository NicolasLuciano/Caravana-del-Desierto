#ifndef INDICES_H_INCLUDED
#define INDICES_H_INCLUDED

#include "constantesymacros.h"

typedef struct
{
    char nickname[TAM_NICKNAME];
} tClave;

typedef struct
{
    unsigned indice;
    tClave clave;
} tIndice;

#endif // INDICES_H_INCLUDED
