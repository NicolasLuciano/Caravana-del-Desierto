#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "../headers/bandido.h"
#include <stdio.h>
#include "archivos.h"

//typedef struct{
//    int inicio;
//    int salida;
//    int premio;
//    int vidaExtra;
//    int oasis;
//    int tormenta;
//}tCasilla;

int generarTablero(tLista *tablero,const tConfig configuracion, tBandido * bandidos);
void mezclarPosiciones(int * vecPosiciones,int cantCasillas);
void distribuirPremios(tLista* tablero,int cantPremios, int ** vecPosiciones);
void distribuirVidasExtra(tLista* tablero, int cantVidasExtra, int ** vecPosiciones);
void distribuirOasis(tLista* tablero, int cantOasis, int ** vecPosiciones);
void distribuirTormentas(tLista* tablero, int cantTormentas, int ** vecPosiciones);
int generarCaravana(const char* nombreArch,const tLista *tablero);
void mostrarCasilla(const void* dato);

#endif // TABLERO_H_INCLUDED
