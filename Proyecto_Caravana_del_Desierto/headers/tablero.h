#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include "lista.h"
#include "archivos.h"

typedef struct{
    int inicio;
    int salida;
    int premio;
    int vidaExtra;
    int oasis;
    int tormenta;
}tCasilla;

int generarTablero(tLista *tablero,const tConfig *configuracion);
void mezclarPosiciones(int * vecPosiciones,int cantCasillas);
void distribuirPremios(tLista* tablero,int cantPremios, int ** vecPosiciones);
void distribuirVidasExtra(tLista* tablero, int cantCasillas, int cantVidas);
void distribuirOasis(tLista* tablero, int cantCasillas, int cantOasis);
void distribuirTormentas(tLista* tablero, int cantCasillas, int cantTormentas);
int generarCaravana(const char* nombreArch,const tLista *tablero);
#endif // TABLERO_H_INCLUDED
