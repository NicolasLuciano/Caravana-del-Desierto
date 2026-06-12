#include "../headers/archivos.h"
#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"
#include "../headers/partida.h"
#include "../headers/cola.h"

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
        mostrarTablero(tablero,cantCasillas);

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

        encolarJugador(&posJugador,casillaAct,&colaTurno,&colaRegistro,direccion,dado,cantCasillas);
        resolverMovimientos();

    }
}

void resolverMovimientos(tLista * posJugador, tBandido * bandidos, tCola * colaTurno,tCasilla * casillaAct, tJugador * jugador)
{
    tMovimiento mov;
    tCasilla casillaBandido;
    int i,contBandido, colision;

    colision=SIN_COLISION;

    desencolar(&colaTurno, &mov, sizeof(tMovimiento));
    for(i=0; i<mov.casillas; i++)
        moverEnLista(posJugador,mov.direccion);

    recuperarDatoLista(posJugador,0,casillaAct,sizeof(tCasilla));


    if(casillaAct->bandido==HAY_BANDIDO)
    {
        i=0;
        casillaAct->bandido=SIN_BANDIDO;
        modificarEnPosLista(posJugador,0,casillaAct,sizeof(tCasilla));
        while(i<cantBandidos && compararLista(posJugador,&(bandidos+i)->posicion)==0)
            i++;

        (bandidos+i)->vivo=MUERTO;
        //LOGICA PARA MOVER EL BANDIDO MUERTO ATRAS
        for(i=1; i<casillaAct->numCasilla; i++)
            moverEnLista(posJugador,ATRAS);

        jugador->vidas--;

        colision=HAY_COLISION;
    }


    contBandido=0;
    while(!colaVacia(colaTurno))
    {
        desencolar(&colaTurno, &mov, sizeof(tMovimiento));
        if((bandidos+contBandido)->vivo==VIVO)
        {
            recuperarDatoLista(&(bandidos+contBandido)->posicion,0,&casillaBandido,sizeof(tCasilla));
            casillaBandido.bandido=SIN_BANDIDO;
            modificarEnPosLista(posJugador,0,&casillaBandido,sizeof(tCasilla));

            for(i=0; i<mov.casillas; i++)
                moverEnLista(&(bandidos+contBandido)->posicion,mov.direccion);

            if(compararLista(posJugador,&(bandidos+contBandido)->posicion)==1 ) //MAGIC NUMBER?
            {
                (bandidos+i)->vivo=MUERTO;
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
        contBandido++;
    }
}
