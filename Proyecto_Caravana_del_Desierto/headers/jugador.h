#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "lista.h"
#include "cola.h"
#include "constantesymacros.h"

typedef struct
{
    char nickname[NICKNAME_TAM];
    char name[NAME_TAM];
    char surname[SURNAME_TAM];
} tUsuario;

typedef struct
{
    tUsuario usuario;
    tNodoLista* posicion;
    unsigned vidas;
    unsigned puntos;
    char protegido;
    char pierdeTurno;
} tJugador;



void moverJugador(tLista *tablero, tNodoLista ** posJugador,tCola *colaMovimientos, int direccion, unsigned dado,unsigned cantCasillas);
void inicializarJugador(tJugador* jugador, tNodoLista* posInicial, int vidasInicio);


#endif // JUGADOR_H_INCLUDED
