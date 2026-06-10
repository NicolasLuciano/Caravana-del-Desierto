#include "../headers/jugador.h"
#include "../headers/constantesymacros.h"
#include "../headers/tablero.h"
#include "../headers/dado.h"

void inicializarJugador(tJugador* jugador, tNodoLista* posInicial, int vidasInicio)
{
    jugador->posicion = posInicial;
    jugador->vidas = vidasInicio;
    jugador->puntos = 0;
    jugador->protegido = 0;
    jugador->pierdeTurno = 0;
}

/*void moverJugador(tLista *tablero, tNodoLista ** posJugador,tCola *colaMovimientos, int direccion, unsigned dado,unsigned cantCasillas)
{
    tCasilla casillaAct;
    unsigned pasosAdelante, pasosAtras,i;
    int casillaJugador;

    recuperarDatoLista(posJugador,0,&casillaAct,sizeof(tCasilla));

    if(direccion==ATRAS)
    {
        if(casillaAct.numCasilla -dado<1) //HAY QUE  VALIDAR ESTO ANTES DE ENTRAR A LA FUNCION
            moverEnLista(posJugador,dado,ADELANTE);
        else
            moverEnLista(posJugador,dado,ATRAS);
    }
    else
    {
        if(casillaAct.numCasilla+dado>cantCasillas)
        {
            pasosAdelante=cantCasillas-casillaAct.numCasilla;
            pasosAtras=dado-pasosAdelante;
            moverEnLista(posJugador,pasosAdelante-pasosAtras,ADELANTE);
        }
        else
            moverEnLista(posJugador,dado,ADELANTE);
    }
}*/
