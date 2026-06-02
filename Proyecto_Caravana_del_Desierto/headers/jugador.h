#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "lista.h"

typedef struct
{
    tNodoLista* posicion;
    unsigned vidas;
    unsigned puntos;
    char protegido;
    char pierdeTurno;
} Jugador;

#endif // JUGADOR_H_INCLUDED
