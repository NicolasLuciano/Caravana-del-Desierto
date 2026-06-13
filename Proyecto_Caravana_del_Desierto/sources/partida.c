#include "../headers/archivos.h"
#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"
#include "../headers/partida.h"
#include "../headers/bandido.h"

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
    while(jugador->vidas>0 && casillaAct.tipo!=SALIDA )
    {

        mostrarTablero(*tablero,cantCasillas);

        printf("El dado esta siendo lanzado\n");
        dado=tirar_dado(DADO_JUGADOR);
        printf("DADO: %d\n", dado);
        printf("Elija la direccion a moverse\n");
        printf("ADELANTE: %c\tATRAS: %c\n",ADELANTE,ATRAS);
        printf("\n");
        scanf(" %c", &direccion);

        printf("CASILLA: %d\n", casillaAct.numCasilla);
        if(direccion==ATRAS && (int)casillaAct.numCasilla-dado<1)
        {
            printf("No es posible moverse hacia atras, sera movido hacia adelante\n");
            direccion=ADELANTE;
        }

        casillaAct.jugador = SIN_JUGADOR;
        modificarEnPosLista(&posJugador, 0, &casillaAct, sizeof(tCasilla));

        encolarJugador(&posJugador,casillaAct,&colaTurno,&colaRegistro,direccion,dado,cantCasillas);
        encolarBandidos(bandidos,&colaTurno,cantBandidos,cantCasillas);
        resolverMovimientos(*tablero,&posJugador,bandidos,&colaTurno,&casillaAct,jugador,cantBandidos,cantCasillas);

        recuperarDatoLista(&posJugador,0,&casillaAct,sizeof(tCasilla));
    }
}

void resolverMovimientos(tLista tablero,tLista * posJugador, tBandido * bandidos, tCola * colaTurno,tCasilla * casillaAct, tJugador * jugador, unsigned cantBandidos, unsigned cantCasillas)
{
    tMovimiento mov;
    tCasilla casillaBandido;
    unsigned i,contBandido, colision, bandidoColision;

    colision=SIN_COLISION;

    sacarDeCola(colaTurno, &mov, sizeof(tMovimiento));
    for(i=0; i<mov.casillas; i++)
        moverEnLista(posJugador,mov.direccion);

    recuperarDatoLista(posJugador,0,casillaAct,sizeof(tCasilla));
    casillaAct->jugador = HAY_JUGADOR;
    modificarEnPosLista(posJugador, 0, casillaAct, sizeof(tCasilla));

    bandidoColision=0;
    if(casillaAct->bandido==HAY_BANDIDO)
    {
        mostrarTablero(tablero,cantCasillas);

        casillaAct->jugador = SIN_JUGADOR;
        casillaAct->bandido=SIN_BANDIDO;
        modificarEnPosLista(posJugador,0,casillaAct,sizeof(tCasilla));
        while(bandidoColision<cantBandidos && compararLista(posJugador,&(bandidos+bandidoColision)->posicion)==0)
            bandidoColision++;

        (bandidos+bandidoColision)->vivo=MUERTO;

        copiarPosicionLista(posJugador,tablero); //DEVOLVEMOS AL JUGADOR AL INICIO

        recuperarDatoLista(posJugador, 0, casillaAct, sizeof(tCasilla));
        casillaAct->jugador = HAY_JUGADOR;
        modificarEnPosLista(posJugador, 0, casillaAct, sizeof(tCasilla));

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

            recuperarDatoLista(&(bandidos+contBandido)->posicion,0,&casillaBandido,sizeof(tCasilla));
            casillaBandido.bandido=HAY_BANDIDO;
            modificarEnPosLista(&(bandidos+contBandido)->posicion,0,&casillaBandido,sizeof(tCasilla));

            if(compararLista(posJugador,&(bandidos+contBandido)->posicion)== LISTAS_IGUALES )
            {
                (bandidos+contBandido)->vivo=MUERTO;

                mostrarTablero(tablero,cantCasillas);

                casillaBandido.bandido=SIN_BANDIDO;
                modificarEnPosLista(&(bandidos+contBandido)->posicion,0,&casillaBandido,sizeof(tCasilla));

                if(colision==SIN_COLISION) //Si hubo colision, significa que el jugador esta en el inicio, asique si hay una segunda colision en el inicio, solo mato al bandido
                {
                    casillaAct->jugador = SIN_JUGADOR;
                    modificarEnPosLista(posJugador, 0, casillaAct, sizeof(tCasilla));

                    copiarPosicionLista(posJugador,tablero); //DEVOLVEMOS AL JUGADOR AL INICIO

                    recuperarDatoLista(posJugador, 0, casillaAct, sizeof(tCasilla));
                    casillaAct->jugador = HAY_JUGADOR;
                    modificarEnPosLista(posJugador, 0, casillaAct, sizeof(tCasilla));

                    jugador->vidas--;
                    colision=HAY_COLISION;
                }
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
