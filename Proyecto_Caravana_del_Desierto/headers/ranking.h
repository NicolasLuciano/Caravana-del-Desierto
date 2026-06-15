#ifndef RANKING_H_INCLUDED
#define RANKING_H_INCLUDED

#include "constantesymacros.h"

typedef struct{
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
    unsigned puntos;
}tRanking;

int compararRanking(const void* a,const void* b);
int buscarJugador(char * clave, tRanking * vecJugador, unsigned cantJugadores);

#endif // RANKING_H_INCLUDED
