#ifndef PARTIDA_H_INCLUDED
#define PARTIDA_H_INCLUDED

#include "lista.h"
#include "bandido.h"
#include "jugador.h"
#include "cola.h"

typedef struct
{
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

typedef struct
{
    unsigned proteccionActual;
    unsigned proteccionSiguiente;
} tProteccion;

void empezarPartida(tLista * tablero, tJugador * jugador, tBandido *bandidos, unsigned cantCasillas, unsigned cantBandidos, tPartida *partida);
void finalizarPartida(tLista *tablero,tJugador jugador,tPartida partida, tProteccion proteccion, unsigned cantCasillas);

unsigned resolverDadoJugador(tLista *posJugador,char *direccion, tCasilla *casillaAct);
void resolverMovimientos(tLista tablero,tLista * posJugador, tBandido * bandidos, tCola * colaTurno,tCasilla * casillaAct, tJugador * jugador, unsigned cantBandidos, unsigned cantCasillas, tProteccion *proteccion,unsigned *pierdeTurno);

void recibirDmg(tLista tablero, tLista *posJugador, tCasilla * casillaAct, tJugador *jugador);
void eliminarBandidosEnPosicion(tBandido *bandidos, unsigned cantBandidos, tLista *posicion);
void moverBandido(tBandido *bandidos, tCasilla *casilla,tMovimiento mov,unsigned posBandido, unsigned cantBandidos);
int hayColision(const tBandido *bandido, tLista *posJugador);

void mostrarPantalla(tLista tablero, tJugador *jugador, unsigned cantCasillas, tProteccion proteccion);
#endif // PARTIDA_H_INCLUDED
