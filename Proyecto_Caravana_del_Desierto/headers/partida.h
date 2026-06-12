#ifndef PARTIDA_H_INCLUDED
#define PARTIDA_H_INCLUDED

#include "lista.h"
#include "bandido.h"
#include "jugador.h"
#include "cola.h"

typedef struct
{
    int idPartida;
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
    unsigned puntos;
    unsigned movimientos;
    char resultado;
} tPartida;

typedef struct
{
    char direccion;
    unsigned casillas;
} tMovimiento;

void empezarPartida(tLista * tablero, tJugador * jugador, tBandido *bandidos, unsigned cantCasillas, unsigned cantBandidos);
void resolverMovimientos(tLista * posJugador, tBandido * bandidos, tCola * colaTurno,tCasilla * casillaAct, tJugador * jugador, unsigned cantBandidos);

#endif // PARTIDA_H_INCLUDED
