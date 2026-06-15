#include "../headers/ranking.h"
#include <string.h>

int compararRanking(const void* a,const void* b)
{
    const tRanking* ranking_1=a;
    const tRanking* ranking_2=b;

    return ranking_2->puntos - ranking_1->puntos;
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

