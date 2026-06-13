#include "../headers/archivos.h"
#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"
#include "../headers/partida.h"
#include "../headers/bandido.h"
#include <windows.h>

void empezarPartida(tLista * tablero, tJugador * jugador, tBandido *bandidos, unsigned cantCasillas, unsigned cantBandidos)
{
    tLista posJugador;
    int dado;
    tCasilla casillaAct;
    tCola colaTurno, colaRegistro;
    char direccion;
    unsigned pierdeTurno;
    tProteccion proteccion;
    copiarPosicionLista(&posJugador,*tablero);
    crearCola(&colaTurno);
    crearCola(&colaRegistro);
    pierdeTurno= NO_PIERDE_TURNO;
    proteccion.proteccionActual = NO_PROTEGIDO;
    proteccion.proteccionSiguiente = NO_PROTEGIDO;
    recuperarDatoLista(&posJugador,0,&casillaAct,sizeof(tCasilla));
    while(jugador->vidas>0 && casillaAct.tipo!=SALIDA )
    {
        proteccion.proteccionActual = proteccion.proteccionSiguiente;
        proteccion.proteccionSiguiente = NO_PROTEGIDO;
        system("cls");
        printf("====================================\n");
        printf("\tESTADISTICAS JUGADOR\n");
        printf("====================================\n");
        printf("VIDAS: %d\tPUNTOS: %d\n\n",jugador->vidas,jugador->puntos);
        mostrarTablero(*tablero,cantCasillas);
        dado=tirar_dado(DADO_JUGADOR);
        if(PIERDE_TURNO==pierdeTurno)
            dado=0;
        pierdeTurno=NO_PIERDE_TURNO;
        printf("\n\nLANZANDO DADO...\n");
        Sleep(MILISEGUNDOS);
        printf("[DADO]: %d\n",dado);
        printf("[MOVERSE]\n");
        printf("(%c) ADELANTE\n(%c) ATRAS\n",ADELANTE,ATRAS);

        do
        {

            scanf(" %c", &direccion);
            if(direccion!=ADELANTE && direccion!=ATRAS)
            {
                printf("INGRESE ENTRADA VALIDA.\n %c o %c\n",ADELANTE,ATRAS);
            }
        }
        while(direccion!=ADELANTE && direccion!=ATRAS);

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
        resolverMovimientos(*tablero,&posJugador,bandidos,&colaTurno,&casillaAct,jugador,cantBandidos,cantCasillas,&proteccion,&pierdeTurno);

        recuperarDatoLista(&posJugador,0,&casillaAct,sizeof(tCasilla));
    }
}

void resolverMovimientos(tLista tablero,tLista * posJugador, tBandido * bandidos, tCola * colaTurno,tCasilla * casillaAct, tJugador * jugador, unsigned cantBandidos, unsigned cantCasillas, tProteccion *proteccion,unsigned *pierdeTurno)
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

        casillaAct->bandido=SIN_BANDIDO;
        while(bandidoColision<cantBandidos && compararLista(posJugador,&(bandidos+bandidoColision)->posicion)==0)
            bandidoColision++;
        recibirDmg(tablero,posJugador,casillaAct,jugador);
        colision=HAY_COLISION;
    }
    else
    {
        if(casillaAct->tipo!=VACIA)
        {
            switch(casillaAct->tipo)
            {
            case VIDAEXTRA:
                jugador->vidas++;
                printf("OBTUVISTE UNA VIDA EXTRA\n");
                break;
            case PREMIO:
                jugador->puntos++;
                printf("OBTUVISTE UN PREMIO\n");
                break;
            case TORMENTA:
                if(NO_PROTEGIDO==proteccion->proteccionActual)
                    *pierdeTurno = PIERDE_TURNO;
                break;
            case OASIS:
                proteccion->proteccionSiguiente = PROTEGIDO;
                break;
            default:
                break;
            }
            casillaAct->tipo=VACIA;
            modificarEnPosLista(posJugador, 0, casillaAct, sizeof(tCasilla));
        }
    }

    contBandido=0;
    while(!colaVacia(colaTurno) && contBandido<cantBandidos)
    {
        if((bandidos+contBandido)->vivo==VIVO)
        {
            sacarDeCola(colaTurno, &mov, sizeof(tMovimiento));

            moverBandido(bandidos,&casillaBandido,mov,contBandido,cantBandidos);

            if(hayColision((bandidos+contBandido),posJugador))
            {
                (bandidos+contBandido)->vivo=MUERTO;
                casillaBandido.bandido=SIN_BANDIDO;
                modificarEnPosLista(&(bandidos+contBandido)->posicion,0,&casillaBandido,sizeof(tCasilla));

                if(colision==SIN_COLISION) //Si hubo colision, significa que el jugador esta en el inicio, asique si hay una segunda colision en el inicio, solo mato al bandido
                {
                    recibirDmg(tablero,posJugador,casillaAct,jugador);
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

void recibirDmg(tLista tablero, tLista *posJugador, tCasilla * casillaAct, tJugador *jugador)
{
    casillaAct->jugador = SIN_JUGADOR;
    modificarEnPosLista(posJugador, 0, casillaAct, sizeof(tCasilla));

    copiarPosicionLista(posJugador,tablero);

    recuperarDatoLista(posJugador, 0, casillaAct, sizeof(tCasilla));
    casillaAct->jugador = HAY_JUGADOR;
    modificarEnPosLista(posJugador, 0, casillaAct, sizeof(tCasilla));

    jugador->vidas--;
}

void moverBandido(tBandido *bandidos, tCasilla *casilla,tMovimiento mov,unsigned posBandido, unsigned cantBandidos)
{
    int i;
    recuperarDatoLista(&(bandidos+posBandido)->posicion,0,casilla,sizeof(tCasilla));
    casilla->bandido=SIN_BANDIDO;
    modificarEnPosLista(&(bandidos+posBandido)->posicion,0,casilla,sizeof(tCasilla));

    for(i=0; i<mov.casillas; i++)
        moverEnLista(&(bandidos+posBandido)->posicion,mov.direccion);

    recuperarDatoLista(&(bandidos+posBandido)->posicion,0,casilla,sizeof(tCasilla));
    while(SALIDA==casilla->tipo || HAY_BANDIDO==casilla->bandido)
    {
        moverEnLista(&(bandidos+posBandido)->posicion,mov.direccion);
        recuperarDatoLista(&(bandidos+posBandido)->posicion,0,casilla,sizeof(tCasilla));
    }
    casilla->bandido=HAY_BANDIDO;
    modificarEnPosLista(&(bandidos+posBandido)->posicion,0,casilla,sizeof(tCasilla));
}

int hayColision(const tBandido *bandido, tLista *posJugador)
{
    return compararLista(posJugador,&bandido->posicion)== LISTAS_IGUALES;
}
