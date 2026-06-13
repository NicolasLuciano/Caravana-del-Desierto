#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "bandido.h"
#include <stdio.h>
#include "archivos.h"

typedef struct
{
    char tipo;
    int bandido;
    int jugador;
    unsigned numCasilla;
} tCasilla;

int generarTablero(tLista *tablero,const tConfig configuracion, tBandido * bandidos);
void mezclarPosiciones(int * vecPosiciones,int cantCasillas);
void distribuirCasillas(int *vecPos,char *cadPos, tConfig config, int **posBandidos);
void mostrarTablero(const tLista tablero, unsigned cantCasillas);
void distribuirBandidos(const tLista *tablero, tBandido *vBandidos, unsigned cantBandidos, int *posBandidos);
void escribirCasilla(FILE* fp, const void* dato);
void guardarTablero(const tLista* tablero, const char* nombreArchivo);
int validarTablero(tConfig config);
#endif // TABLERO_H_INCLUDED
