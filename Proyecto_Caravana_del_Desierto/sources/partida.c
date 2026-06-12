#include "../headers/archivos.h"
#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"
#include "../headers/partida.h"

void empezarPartida(tLista * tablero, tJugador * jugador, tBandido *bandidos, unsigned cantCasillas, unsigned cantBandidos)
{
    tLista posJugador;
    int dado;
    tCasilla casillaAct;
    tCola colaTurno, colaRegistro;
    char direccion;

    copiarPosicionLista(&posJugador,*tablero);
    crearCola(&colaTurno);
    crearCola(&colaRegistro);

    recuperarDatoLista(&posJugador,0,&casillaAct,sizeof(tCasilla));
    while(jugador->vidas>0)
    {
        mostrarTablero(*tablero,cantCasillas);

        printf("Lanzar Dado\n");
        dado=tirar_dado(DADO_JUGADOR);
        printf("Elija la direccion a moverse\n");
        printf("ADELANTE: %c\tATRAS: %c\n",ADELANTE,ATRAS);
        printf("\n");
        scanf("%c", &direccion);


        if(direccion==ATRAS && casillaAct.numCasilla-dado<1)
        {
            printf("No es posible moverse hacia atras, sera movido hacia adelante\n");
            direccion=ADELANTE;
        }

        encolarJugador(&posJugador,casillaAct,&colaTurno,&colaRegistro,direccion,dado,cantCasillas);
        resolverMovimientos(&posJugador,bandidos,&colaTurno,&casillaAct,jugador,cantBandidos);

    }
}

void resolverMovimientos(tLista * posJugador, tBandido * bandidos, tCola * colaTurno,tCasilla * casillaAct, tJugador * jugador, unsigned cantBandidos)
{
    tMovimiento mov;
    tCasilla casillaBandido;
    unsigned i,contBandido, colision, bandidoColision;

    colision=SIN_COLISION;

    sacarDeCola(colaTurno, &mov, sizeof(tMovimiento));
    for(i=0; i<mov.casillas; i++)
        moverEnLista(posJugador,mov.direccion); //en vez de hacer este for, conviene copiar la posJugador a el inicio del tablero

    recuperarDatoLista(posJugador,0,casillaAct,sizeof(tCasilla));

    bandidoColision=0;
    if(casillaAct->bandido==HAY_BANDIDO)
    {
        casillaAct->bandido=SIN_BANDIDO;
        modificarEnPosLista(posJugador,0,casillaAct,sizeof(tCasilla));
        while(bandidoColision<cantBandidos && compararLista(posJugador,&(bandidos+bandidoColision)->posicion)==0)
            bandidoColision++;

        (bandidos+bandidoColision)->vivo=MUERTO;
        for(i=1; i<casillaAct->numCasilla; i++)
            moverEnLista(posJugador,ATRAS);

        jugador->vidas--;

        colision=HAY_COLISION;
    }


    contBandido=0;
    while(!colaVacia(colaTurno))
    {
        if((bandidos+contBandido)->vivo==VIVO)
        {
            sacarDeCola(colaTurno, &mov, sizeof(tMovimiento));

            recuperarDatoLista(&(bandidos+contBandido)->posicion,0,&casillaBandido,sizeof(tCasilla));
            casillaBandido.bandido=SIN_BANDIDO;
            modificarEnPosLista(&(bandidos+contBandido)->posicion,0,&casillaBandido,sizeof(tCasilla));

            for(i=0; i<mov.casillas; i++)
                moverEnLista(&(bandidos+contBandido)->posicion,mov.direccion);

            if(compararLista(posJugador,&(bandidos+contBandido)->posicion)==LISTAS_IGUALES )
            {
                (bandidos+contBandido)->vivo=MUERTO;
                if(colision==SIN_COLISION)
                {
                    for(i=1; i<casillaAct->numCasilla; i++)
                        moverEnLista(posJugador,ATRAS);

                    jugador->vidas--;

                    colision=HAY_COLISION;

                }

            }
            else
            {
                recuperarDatoLista(&(bandidos+contBandido)->posicion,0,&casillaBandido,sizeof(tCasilla));
                casillaBandido.bandido=HAY_BANDIDO;
                modificarEnPosLista(&(bandidos+contBandido)->posicion,0,&casillaBandido,sizeof(tCasilla));
            }

        }
        else
        {
            if(HAY_COLISION==colision && contBandido==bandidoColision)
                sacarDeCola(colaTurno, &mov, sizeof(tMovimiento));
        }
        contBandido++;
    }
}
