#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "lista.h"
#include "cola.h"
typedef struct
{
    tNodoLista* posicion;
    unsigned vidas;
    unsigned puntos;
    char protegido;
    char pierdeTurno;
} Jugador;

void moverJugador(tLista *tablero, tNodoLista ** posJugador,tCola *colaMovimientos, int direccion, unsigned dado,unsigned cantCasillas);


#endif // JUGADOR_H_INCLUDED
