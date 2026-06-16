#include "../headers/jugador.h"
#include "../headers/dado.h"
#include "../headers/constantesymacros.h"
#include "../headers/partida.h"

void inicializarJugador(tJugador * jugador, int vidasInicio)
{
    jugador->vidas = vidasInicio;
    jugador->puntos = 0;
}

void encolarJugador(tLista *posJugador, tCasilla casillaAct, tCola *colaTurno, tCola *colaRegistro, int direccion, unsigned dado,unsigned cantCasillas, unsigned *movimientos)
{
    unsigned pasosAdelante, pasosAtras;
    tMovimiento movJugador;
    if(dado)
    {
        if(ADELANTE==direccion && casillaAct.numCasilla+dado >cantCasillas)
        {
            pasosAdelante=cantCasillas-casillaAct.numCasilla;
            pasosAtras=dado-pasosAdelante;

            movJugador.casillas=pasosAdelante;
            movJugador.direccion=ADELANTE;
            ponerEnCola(colaRegistro,&movJugador,sizeof(tMovimiento));

            movJugador.casillas=pasosAtras;
            movJugador.direccion=ATRAS;
            ponerEnCola(colaRegistro,&movJugador,sizeof(tMovimiento));
            (*movimientos)++;
            if(pasosAdelante > pasosAtras)
            {
                movJugador.casillas = pasosAdelante - pasosAtras;
                movJugador.direccion = ADELANTE;
            }
            else
            {
                movJugador.casillas = pasosAtras - pasosAdelante;
                movJugador.direccion = ATRAS;
            }
        }
        else
        {
            movJugador.direccion = direccion;
            movJugador.casillas = dado;
            ponerEnCola(colaRegistro,&movJugador,sizeof(tMovimiento));
        }
    }

        ponerEnCola(colaTurno,&movJugador,sizeof(tMovimiento));
        (*movimientos)++;
}
