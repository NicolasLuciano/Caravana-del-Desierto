#include "../headers/jugador.h"
#include "../headers/dado.h"
#include "../headers/partida.h"

void inicializarJugador(tJugador * jugador, int vidasInicio)
{
    jugador->vidas = vidasInicio;
    jugador->puntos = 0;
}

void encolarJugador(tLista *posJugador, tCasilla casillaAct, tCola *colaTurno, tCola *colaRegistro, int direccion, unsigned dado,unsigned cantCasillas)
{
    unsigned pasosAdelante, pasosAtras;
    tMovimiento movJugador;

    if(casillaAct.numCasilla+dado >cantCasillas)
    {
        pasosAdelante=cantCasillas-casillaAct.numCasilla;
        pasosAtras=dado-pasosAdelante;

        movJugador.casillas=pasosAdelante;
        movJugador.direccion=ADELANTE;
        ponerEnCola(colaRegistro,&movJugador,sizeof(tMovimiento));

        movJugador.casillas=pasosAdelante;
        movJugador.direccion=ADELANTE;
        ponerEnCola(colaRegistro,&movJugador,sizeof(tMovimiento));

        dado=pasosAdelante-pasosAtras;
    }
    movJugador.direccion=direccion;
    movJugador.casillas=dado;

    ponerEnCola(colaTurno,&movJugador,sizeof(tMovimiento));
    //moverEnLista(posJugador,direccion);
}
