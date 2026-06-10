#include "../headers/lista.h"
#include "../headers/archivos.h"
#include "../headers/tablero.h"
#include "../headers/bandido.h"
#include "../headers/jugador.h"
#include "../headers/constantesymacros.h"

int inicializarJuego()
{
    tLista tablero;
    tBandido* bandidos;
    tConfig configuracion;
    tJugador jugador;

    crearLista(&tablero);
    cargarConfig(NOMARCH, &configuracion);

    bandidos = crearBandidos(configuracion.cantBandidos);
    if(bandidos == NULL)
    {
        printf("No hay memoria suficiente para iniciar la partida\n");
        return SIN_MEM;
    }

    if(generarTablero(&tablero, configuracion, bandidos) == SIN_MEM)
    {
        printf("No hay memoria suficiente para iniciar la partida\n");
        free(bandidos);
        return SIN_MEM;
    }

    inicializarJugador(&jugador, obtenerPrimero(&tablero), configuracion.vidasIniciales);

    mostrarTablero(&tablero,configuracion.cantCasillas);

    return TODO_OK;
}
