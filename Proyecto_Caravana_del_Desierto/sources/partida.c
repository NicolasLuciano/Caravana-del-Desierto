#include "../headers/lista.h"
#include "../headers/archivos.h"
#include "../headers/tablero.h"
#include "../headers/bandido.h"
#include "../headers/jugador.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"
#include "../headers/partida.h"

void empezarPartida(tLista * tablero, tJugador * jugador, tBandido *bandidos, unsigned cantCasillas)
{
    tLista posJugador;
    int dado,direccion;
    tCasilla casillaAct;
    tCola colaTurno, colaRegistro;

    copiarPosicionLista(&posJugador,*tablero);
    crearCola(&colaTurno);
    crearCola(&colaRegistro);

    recuperarDatoLista(&posJugador,0,&casillaAct,sizeof(tCasilla));
    while(jugador->vidas>0)
    {
        mostrarTablero(tablero,configuracion.cantCasillas);

        printf("Lanzar Dado\n");
        dado=tirar_dado(DADO_JUGADOR);
        printf("Elija la direccion a moverse\n");
        printf("ADELANTE: %d\tATRAS: %d\n",ADELANTE,ATRAS);
        printf("\n");
        scanf("%d", &direccion);

        if(direccion==ATRAS && casillaAct.numCasilla-dado<1)
        {
            printf("No es posible moverse hacia atras, sera movido hacia adelante\n");
            direccion=ADELANTE;
        }

        moverJugador(&posJugador,casillaAct,&colaTurno,&colaRegistro,direccion,dado,cantCasillas);


        recuperarDatoLista(&posJugador,0,&casillaAct,sizeof(tCasilla));
    }
}
