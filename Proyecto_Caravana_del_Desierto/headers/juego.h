#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "../headers/constantesymacros.h"

typedef struct{
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
    unsigned puntos;
    unsigned movimientos;
}tRanking;

int inicializarJuego();
void verRanking();
#endif // JUEGO_H_INCLUDED
