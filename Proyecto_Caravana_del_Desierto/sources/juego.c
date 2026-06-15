#include "../headers/lista.h"
#include "../headers/tablero.h"
#include "../headers/bandido.h"
#include "../headers/jugador.h"
#include "../headers/partida.h"
#include "../headers/juego.h"

int inicializarJuego(char * usuario)
{
    tLista tablero;
    tBandido* bandidos;
    tConfig configuracion;
    tJugador jugador;
    tPartida partida;

    crearLista(&tablero);
    cargarConfig(NOMARCH, &configuracion);
    strcpy(partida.nombreDeUsuario,usuario);

    if(validarTablero(configuracion)==TABLERO_INVALIDO)
    {
        fprintf(stderr,"El tablero a generar es invalido\n");
        return TABLERO_INVALIDO;
    }

    bandidos = crearBandidos(configuracion.cantBandidos);
    if(NULL == bandidos)
    {
        fprintf(stderr,"No hay memoria suficiente para iniciar la partida\n");
        return SIN_MEM;
    }

    if(SIN_MEM == generarTablero(&tablero, configuracion, bandidos))
    {
       fprintf(stderr,"No hay memoria suficiente para iniciar la partida\n");
        free(bandidos);
        return SIN_MEM;;
    }

    if(guardarTablero(&tablero,NOMARCH2)!=TODO_OK)
        return ARCH_ERROR;


    inicializarJugador(&jugador, configuracion.vidasIniciales);

    empezarPartida(&tablero,&jugador,bandidos, configuracion.cantCasillas,configuracion.cantBandidos,&partida);
    system("pause");
    system("cls");


    guardarPartida(partida,NOMARCH3);

    free(bandidos);
    vaciarLista(&tablero);
    return TODO_OK;
}

int verRanking()
{
    tRanking * vecRanking;
    unsigned capacidad,cantJugadores;
    int res;

    capacidad=JUGADORES_MAX;
    vecRanking=malloc(sizeof(tRanking)*capacidad);
    if(NULL==vecRanking)
    {
        fprintf(stderr,"Error: memoria insuficiente para crear el ranking\n");
        return SIN_MEM;
    }

    res=cargarRanking(&vecRanking,NOMARCH3,capacidad,&cantJugadores);
    if(res!=TODO_OK)
    {
        free(vecRanking);
        return res;
    }

    qsort(vecRanking,cantJugadores,sizeof(tRanking),compararRanking);
    printf("========================================\n");
    printf("              RANKING\n");
    printf("========================================\n\n");
    mostrarVec(vecRanking,cantJugadores);
    free(vecRanking);
    return TODO_OK;
}

void mostrarVec(tRanking *vecJugador, unsigned cantJugadores)
{
    unsigned i;

    printf("%-25s %-10s\n", "JUGADOR", "PUNTAJE");
    printf("%-25s %-10s\n", "-------------------------", "----------");

    for(i = 0; i < cantJugadores; i++)
        printf("%-25s %-10u\n",
               vecJugador[i].nombreDeUsuario,
               vecJugador[i].puntos);
}
