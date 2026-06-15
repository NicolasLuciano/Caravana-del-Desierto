#include "../headers/lista.h"
#include "../headers/archivos.h"
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
    FILE * pf;
    tPartida partida;
    tRanking * vecJugador,*vecAux;
    unsigned cantJugadores,capacidad;
    int pos;

    capacidad=JUGADORES_MAX;
    vecJugador=malloc(sizeof(tRanking)*capacidad);
    if(NULL==vecJugador)
    {
        printf("No fue posible acceder al ranking");
        return SIN_MEM;
    }
    pf=fopen(NOMARCH3,"rb");
    if(pf==NULL)
    {
        printf("No fue posible abrir el archivo %s", NOMARCH3);
        free(vecJugador);
        return ARCH_ERROR;
    }

    cantJugadores=0;
    while(fread(&partida,sizeof(tPartida),1,pf)==1)
    {
        pos=buscarJugador(partida.nombreDeUsuario,vecJugador,cantJugadores);
        printf("%d\n", pos);
        if(pos!=NO_ENCONTRADO)
            (vecJugador+pos)->puntos+=partida.puntos;
        else
        {
            if(cantJugadores==capacidad)
            {
                capacidad *=2;
                vecAux=realloc(vecJugador, sizeof(tRanking)*capacidad);
                if(vecAux == NULL)
                {
                    printf("No fue posible acceder al ranking");
                    fclose(pf);
                    free(vecJugador);
                    return SIN_MEM;
                }
                vecJugador=vecAux;
            }

            strcpy((vecJugador+cantJugadores)->nombreDeUsuario,partida.nombreDeUsuario);
            (vecJugador+cantJugadores)->puntos=partida.puntos;
            cantJugadores++;
        }
    }
    qsort(vecJugador,cantJugadores,sizeof(tRanking),compararRanking);
    printf("---RANKING---\n");
    mostrarVec(vecJugador,cantJugadores);

    fclose(pf);
    free(vecJugador);
    return TODO_OK;
}

int buscarJugador(char * clave, tRanking * vecJugador, unsigned cantJugadores)
{
    int pos;
    unsigned i;

    pos=NO_ENCONTRADO;
    i=0;
    while(pos==NO_ENCONTRADO && i<cantJugadores)
    {
        if(strcmp(clave,(vecJugador+i)->nombreDeUsuario)==0)
            pos=i;
        i++;
    }
    return pos;
}

int compararRanking(const void* a,const void* b)
{
    const tRanking* ranking_1=a;
    const tRanking* ranking_2=b;

    return ranking_2->puntos - ranking_1->puntos;
}

void mostrarVec(tRanking * vecJugador, unsigned cantJugadores)
{
    unsigned i;

    for(i=0;i<cantJugadores;i++)
        printf("Jugador: %s\tPuntaje: %d\n",(vecJugador+i)->nombreDeUsuario,(vecJugador+i)->puntos);

}
