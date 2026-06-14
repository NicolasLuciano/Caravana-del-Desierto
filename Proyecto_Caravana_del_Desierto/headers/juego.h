#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "../headers/constantesymacros.h"

typedef struct{
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
    unsigned puntos;
}tRanking;

int inicializarJuego();
int verRanking();
int buscarJugador(char * clave, tRanking * vecJugador, unsigned cantJugadores);
int compararRanking(const void* a,const void* b);
void mostrarVec(tRanking * vecJugador, unsigned cantJugadores);
#endif // JUEGO_H_INCLUDED
