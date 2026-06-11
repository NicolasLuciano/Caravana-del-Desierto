#include "../headers/jugador.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"

void inicializarJugador(tJugador * jugador, int vidasInicio)
{
    jugador->vidas = vidasInicio;
    jugador->puntos = 0;
}

void moverJugador(tLista *posJugador, tCasilla casillaAct, tCola *colaMovimientos, int direccion, unsigned dado,unsigned cantCasillas)
{
    unsigned pasosAdelante, pasosAtras;


    if(casillaAct.numCasilla+dado >cantCasillas)
    {
        pasosAdelante=cantCasillas-casillaAct.numCasilla;
        pasosAtras=dado-pasosAdelante;
        dado=pasosAdelante-pasosAtras;
    }

    moverEnLista(posJugador,dado);
}
