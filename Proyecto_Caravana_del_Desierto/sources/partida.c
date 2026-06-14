#include "../headers/archivos.h"
#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"
#include "../headers/partida.h"
#include "../headers/bandido.h"
#include <windows.h>
#include <ctype.h>

void empezarPartida(tLista * tablero, tJugador * jugador, tBandido *bandidos, unsigned cantCasillas, unsigned cantBandidos, tPartida *partida)
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
    partida->movimientos=0;

    recuperarDatoLista(&posJugador,0,&casillaAct,sizeof(tCasilla));

    while(jugador->vidas>0 && casillaAct.tipo!=SALIDA )
    {
        proteccion.proteccionActual = proteccion.proteccionSiguiente;
        proteccion.proteccionSiguiente = NO_PROTEGIDO;

        mostrarPantalla(*tablero,jugador,cantCasillas,proteccion);


        if(PIERDE_TURNO==pierdeTurno)
        {
            dado=0;
            pierdeTurno=NO_PIERDE_TURNO;
        }
        else
        {
            dado=resolverDadoJugador(&posJugador,&direccion,&casillaAct);
        }

        encolarJugador(&posJugador,casillaAct,&colaTurno,&colaRegistro,direccion,dado,cantCasillas, &(partida->movimientos));
        encolarBandidos(bandidos,&colaTurno,cantBandidos,cantCasillas);
        resolverMovimientos(*tablero,&posJugador,bandidos,&colaTurno,&casillaAct,jugador,cantBandidos,cantCasillas,&proteccion,&pierdeTurno);
        recuperarDatoLista(&posJugador,0,&casillaAct,sizeof(tCasilla));
    }

    partida->puntos = jugador->puntos;
    //strcpy(partida.nombreDeUsuario,jugador->usuario.nombreDeUsuario);
    if(jugador->vidas<=0)
    {
        printf("\n\nTE QUEDASTE SIN RECURSOS. LOS BANDIDOS SON IMPARABLES!\n\n");
        printf("\n\n--------GAME OVER--------\n\n");
        partida->resultado = DERROTA;
    }
    else
    {
        printf("\n\nFELICITACIONES. LLEGASTE SANO Y SALVO A LA CIUDAD REFUGIO\n\n");
        printf("\n\n--------VICTORIA--------\n\n");
        partida->resultado = VICTORIA;
    }
    system("pause");
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

    bandidoColision=-1;
    if(casillaAct->bandido==HAY_BANDIDO)
    {
        casillaAct->bandido=SIN_BANDIDO;
        bandidoColision=0;
        while(bandidoColision<cantBandidos && compararLista(posJugador,&(bandidos+bandidoColision)->posicion)==0)
            bandidoColision++;
        if(NO_PROTEGIDO==proteccion->proteccionActual)
        {
            mostrarPantalla(tablero,jugador,cantCasillas,*proteccion);
            printf("\nLOS BANDIDOS TE ATRAPARON! REGRESAS AL INICIO [-1 VIDA]\n");
            system("pause");
            recibirDmg(tablero,posJugador,casillaAct,jugador);
            colision=HAY_COLISION;
        }
        else
            proteccion->proteccionActual=NO_PROTEGIDO;

    }
    else
    {
        if(casillaAct->tipo!=VACIA && casillaAct->tipo!=SALIDA && casillaAct->tipo!=TORMENTA)
        {
            mostrarPantalla(tablero,jugador,cantCasillas,*proteccion);
            switch(casillaAct->tipo)
            {
            case VIDAEXTRA:
                jugador->vidas++;
                printf("ENCONTRASTE PROVISIONES [+1 VIDA]\n");
                system("pause");
                break;
            case PREMIO:
                jugador->puntos++;
                printf("ENCONTRASTE UN TESOSO [+1 PUNTO]\n");
                system("pause");
                break;
            case OASIS:
                proteccion->proteccionSiguiente = PROTEGIDO;
                printf("ENCUENTRAS UN OASIS MAS ADELANTE. OBTIENES UNA PROTECCION PARA EL SIGUIENTE TURNO\n");
                system("pause");
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
                mostrarPantalla(tablero,jugador,cantCasillas,*proteccion);
                (bandidos+contBandido)->vivo=MUERTO;
                casillaBandido.bandido=SIN_BANDIDO;
                modificarEnPosLista(&(bandidos+contBandido)->posicion,0,&casillaBandido,sizeof(tCasilla));
                if(NO_PROTEGIDO==proteccion->proteccionActual)
                {
                    if(colision==SIN_COLISION) //Si hubo colision, significa que el jugador esta en el inicio, asique si hay una segunda colision en el inicio, solo mato al bandido
                    {
                        printf("\nLOS BANDIDOS TE ATRAPARON! REGRESAS AL INICIO [-1 VIDA]\n");
                        recibirDmg(tablero,posJugador,casillaAct,jugador);
                        colision=HAY_COLISION;
                    }
                    else
                    {
                        printf("LOS BANDIDOS TE ENCONTRARON PERO TE REFUGIAS EN TU CAMPAMENTO - LOS BANDIDOS SE CANSAN Y SE VAN.\n\n");
                    }
                }
                else
                    printf("LOS BANDIDOS TE ENCONTRARON. \nEL OASIS TE REFRESCO Y TIENES FUERZAS PARA DEFENDERTE. DERROTAS A LOS BANDIDOS\n");
                system("pause");
            }

        }
        else
        {
            if(contBandido==bandidoColision)
                sacarDeCola(colaTurno, &mov, sizeof(tMovimiento));
        }
        contBandido++;
    }
    if(SIN_COLISION==colision)
    {
        recuperarDatoLista(posJugador,0,casillaAct,sizeof(tCasilla));
        if(casillaAct->tipo==TORMENTA)
        {
            mostrarPantalla(tablero,jugador,cantCasillas,*proteccion);
            if(PROTEGIDO==proteccion->proteccionActual)
            {
                printf("TE CRUZAS CON UNA TORMENTA DE ARENA PERO TOMAS UN ATAJO\n");
            }
            else
            {
                printf("UNA TORMENTA DE ARENA BLOQUEA TU CAMINO. PIERDES UN TURNO\n");
                *pierdeTurno=PIERDE_TURNO;
            }
            system("pause");
            casillaAct->tipo=VACIA;
            modificarEnPosLista(posJugador, 0, casillaAct, sizeof(tCasilla));
        }
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

unsigned resolverDadoJugador(tLista *posJugador,char *direccion, tCasilla *casillaAct)
{
    unsigned dado;
    dado=tirar_dado(DADO_JUGADOR);
    printf("\n\nLANZANDO DADO...\n");
    Sleep(MILISEGUNDOS);
    printf("[DADO]: %d\n",dado);
    printf("[MOVERSE]\n");
    printf("(%c) ADELANTE\n(%c) ATRAS\n",ADELANTE,ATRAS);

    do
    {
        scanf(" %c", direccion);
        *direccion=toupper(*direccion);
        if(*direccion!=ADELANTE && *direccion!=ATRAS)
            printf("INGRESE ENTRADA VALIDA.\n %c o %c\n",ADELANTE,ATRAS);
    }
    while(*direccion!=ADELANTE && *direccion!=ATRAS);

    if(*direccion==ATRAS && (int)casillaAct->numCasilla-dado<1)
    {
        printf("No es posible moverse hacia atras, sera movido hacia adelante\n");
        system("pause");
        *direccion=ADELANTE;
    }
    casillaAct->jugador = SIN_JUGADOR;
    modificarEnPosLista(posJugador, 0, &casillaAct, sizeof(tCasilla));
    return dado;
}

void mostrarPantalla(tLista tablero, tJugador *jugador, unsigned cantCasillas, tProteccion proteccion)
{
    system("cls");
    printf("====================================\n");
    printf("\tESTADISTICAS JUGADOR\n");
    printf("====================================\n");
    printf("VIDAS: %d\tPUNTOS: %d",jugador->vidas,jugador->puntos);
    if(PROTEGIDO==proteccion.proteccionActual)
        printf("\nEL OASIS TE PROTEGE. VIAJA SIN PREOCUPACIONES");
    printf("\n\n");
    mostrarTablero(tablero,cantCasillas);
}
