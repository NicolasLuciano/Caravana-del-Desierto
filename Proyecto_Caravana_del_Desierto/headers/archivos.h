#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "partida.h"
#include "config.h"
#include "tablero.h"

typedef struct
{
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
    int numRegistro;
}tIndice;

typedef struct{
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
    unsigned puntos;
}tRanking;

int cargarConfig(const char* nombreArch, tConfig* configuracion);
void generaraArchivoTablero();
int guardarTablero(const tLista* tablero, const char* nombreArchivo);
void escribirCasilla(FILE* fp, const void* dato);
int guardarPartida(tPartida partida, const char * nombreArchivo);
int compararUsuarios(const void *a, const void *b);
int cargarRanking(tRanking ** vecRanking, char * nombreArchivo,unsigned capacidad, unsigned * cantJugadores);
int buscarJugador(char * clave, tRanking * vecJugador, unsigned cantJugadores);
int compararRanking(const void* a,const void* b);
#endif // ARCHIVOS_H_INCLUDED
