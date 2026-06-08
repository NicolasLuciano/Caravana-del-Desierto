#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "../headers/bandido.h"
#include <stdio.h>
#include "archivos.h"

typedef struct{
    char tipo;
    unsigned numCasilla;
}tCasilla;

int generarTablero(tLista *tablero,const tConfig configuracion, tBandido * bandidos);
void mezclarPosiciones(int * vecPosiciones,int cantCasillas);
void distribuirCasillas(int *vecPos,char *cadPos, tConfig config);
int generarCaravana(const char* nombreArch,const tLista *tablero);
void mostrarTablero(const tLista* lista, const tBandido*bandidos, unsigned cantBandidos);

#endif // TABLERO_H_INCLUDED
