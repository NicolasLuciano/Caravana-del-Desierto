#include "../headers/lista.h"
#include "../headers/tablero.h"
#include "../headers/bandido.h"
#include "../headers/jugador.h"
#include "../headers/partida.h"
#include "../headers/juego.h"
#include "../headers/indices.h"

int inicializarJuego(char * usuario)
{
    tLista tablero;
    tBandido* bandidos;
    tConfig configuracion;
    tJugador jugador;
    tPartida partida;

    crearLista(&tablero);
    cargarConfig(NOMARCH_CONFIG, &configuracion);
    strcpy(partida.nombreDeUsuario,usuario);
    if(validarTablero(configuracion)==TABLERO_INVALIDO)
    {
        fprintf(stderr,"---El tablero a generar es invalido---\n");
        return TABLERO_INVALIDO;
    }

    bandidos = crearBandidos(configuracion.cantBandidos);
    if(NULL == bandidos)
    {
        fprintf(stderr,"---No hay memoria suficiente para iniciar la partida---\n");
        return SIN_MEM;
    }

    if(SIN_MEM == generarTablero(&tablero, configuracion, bandidos))
    {
        fprintf(stderr,"---No hay memoria suficiente para iniciar la partida---\n");
        free(bandidos);
        return SIN_MEM;;
    }

    if(guardarTablero(&tablero,NOMARCH_CARAVANA)!=TODO_OK)
        return ARCH_ERROR;


    inicializarJugador(&jugador, configuracion.vidasIniciales);

    empezarPartida(&tablero,&jugador,bandidos, configuracion.cantCasillas,configuracion.cantBandidos,&partida);
    system("cls");

    guardarPartida(partida,NOMARCH_PARTIDA);

    free(bandidos);
    vaciarLista(&tablero);
    return TODO_OK;
}

int verRanking()
{
    tRanking * vecRanking;
    unsigned cantActual,cantJugadores;
    int res;
    FILE * pfUsuario;

    pfUsuario=fopen(NOMARCH_USER,"rb");
    if(!pfUsuario)
    {
        perror(NOMARCH_USER);
        return ARCH_ERROR;
    }
    fseek(pfUsuario,0,SEEK_END);

    cantJugadores=ftell(pfUsuario)/sizeof(tUsuario);

    vecRanking=malloc(sizeof(tRanking)*cantJugadores);
    if(NULL==vecRanking)
    {
        fprintf(stderr,"Error: memoria insuficiente para crear el ranking\n");
        fclose(pfUsuario);
        return SIN_MEM;
    }
    cantActual=0;
    res=cargarRanking(vecRanking,NOMARCH_PARTIDA,&cantActual);
    if(res!=TODO_OK)
    {
        free(vecRanking);
        return res;
    }

    qsort(vecRanking,cantActual,sizeof(tRanking),compararRanking);
    printf("========================================\n");
    printf("              RANKING\n");
    printf("========================================\n\n");
    mostrarVec(vecRanking,cantActual);

    free(vecRanking);
    fclose(pfUsuario);
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
