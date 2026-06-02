#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "lista.h"

typedef struct
{
    tNodoLista* posicion;
    int vidas;
    int puntos;
    int protegido;
    int pierdeTurno;
} Jugador;

#endif // JUGADOR_H_INCLUDED
