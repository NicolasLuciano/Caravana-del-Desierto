#include "../headers/jugador.h"
#include "../headers/constantesymacros.h"
#include "../headers/tablero.h"
#include "../headers/dado.h"

void moverJugador(tLista *tablero, tNodoLista ** posJugador,tCola *colaMovimientos, int direccion, unsigned dado,unsigned cantCasillas)
{
    tCasilla casillaAct;
    unsigned pasosAdelante, pasosAtras,i;

    while(compararNodos())

    recuperarDatoLista(*posJugador,&casillaAct,sizeof(tCasilla));
    if(direccion==ATRAS)
    {
        if(casillaAct.numCasilla -dado<1) //CAPAZ HAY QUE  VALIDAR ESTO ANTES DE ENTRAR A LA FUNCION
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
            moverEnLista(posJugador,pasosAdelante,ADELANTE);
            moverEnLista(posJugador,pasosAtras,ATRAS);
        }
        else
            moverEnLista(posJugador,dado,ADELANTE);
    }
}
