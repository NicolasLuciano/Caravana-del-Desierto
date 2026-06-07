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
void distribuirPremios(tLista* tablero,int cantPremios, int ** vecPosiciones);
void distribuirVidasExtra(tLista* tablero, int cantVidasExtra, int ** vecPosiciones);
void distribuirOasis(tLista* tablero, int cantOasis, int ** vecPosiciones);
void distribuirTormentas(tLista* tablero, int cantTormentas, int ** vecPosiciones);
void distribuirBandidos(tLista * tablero, tBandido * bandidos, int cantBandidos, int ** vecPosiciones);
int generarCaravana(const char* nombreArch,const tLista *tablero);
void mostrarTablero(const tLista* lista, const tBandido*bandidos, unsigned cantBandidos);

#endif // TABLERO_H_INCLUDED
