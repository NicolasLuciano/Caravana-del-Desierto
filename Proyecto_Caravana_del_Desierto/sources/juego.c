#include "../headers/lista.h"
#include "../headers/archivos.h"
#include "../headers/tablero.h"
#include "../headers/bandido.h"
#include "../headers/jugador.h"
#include "../headers/partida.h"
#include "../headers/juego.h"

int inicializarJuego()
{
    tLista tablero;
    tBandido* bandidos;
    tConfig configuracion;
    tJugador jugador;

    crearLista(&tablero);
    cargarConfig(NOMARCH, &configuracion);

    if(validarTablero(configuracion)==TABLERO_INVALIDO)
    {
        printf("El tablero a generar es invalido\n");
        return TABLERO_INVALIDO;
    }

    bandidos = crearBandidos(configuracion.cantBandidos);
    if(NULL == bandidos)
    {
        printf("No hay memoria suficiente para iniciar la partida\n");
        return SIN_MEM;
    }

    if(SIN_MEM == generarTablero(&tablero, configuracion, bandidos))
    {
        printf("No hay memoria suficiente para iniciar la partida\n");
        free(bandidos);
        return SIN_MEM;
    }

    if(guardarTablero(&tablero,NOMARCH2)==ARCH_ERROR)
        printf("No fue posible abrir el archivo %s", NOMARCH2);

    inicializarJugador(&jugador, configuracion.vidasIniciales);

    empezarPartida(&tablero,&jugador,bandidos, configuracion.cantCasillas,configuracion.cantBandidos);
    system("pause");
    system("cls");

    free(bandidos);
    vaciarLista(&tablero);
    return TODO_OK;
}

void verRanking()
{
    FILE * pf;
    tPartida partida;
    tRanking * jugador;

    pf=fopen(NOMARCH3,"rb");
    if(pf==NULL)
    {
        printf("No fue posible abrir el archivo %s", NOMARCH3);
        return;
    }


    fread(&partida,sizeof(tPartida),1,pf);
    while(!feof(pf))
    {

        fread(&partida,sizeof(tPartida),1,pf);
    }

    fclose(pf);
}

