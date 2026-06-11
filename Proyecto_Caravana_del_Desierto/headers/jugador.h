#ifndef JUGADOR_H_INCLUDED
#define JUGADOR_H_INCLUDED

#include "lista.h"
#include "cola.h"
#include "constantesymacros.h"
#include "tablero.h"

typedef struct
{
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
    char nombre[NOMBRE_TAM];
    char apellido[APELLIDO_TAM];
} tUsuario;

typedef struct
{
    tUsuario usuario;
    unsigned vidas;
    unsigned puntos;
} tJugador;



void moverJugador(tLista *posJugador, tCasilla casillaAct, tCola *colaTurno, tCola *colaRegistro, int direccion, unsigned dado,unsigned cantCasillas);
void inicializarJugador(tJugador * jugador, int vidasInicio);


#endif // JUGADOR_H_INCLUDED
