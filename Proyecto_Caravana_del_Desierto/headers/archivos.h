#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "partida.h"
#include "config.h"
#include "tablero.h"

int cargarConfig(const char* nombreArch, tConfig* configuracion);
void generaraArchivoTablero();
int guardarTablero(const tLista* tablero, const char* nombreArchivo);
void escribirCasilla(FILE* fp, const void* dato);
int guardarPartida(tPartida partida, const char * nombreArchivo);

#endif // ARCHIVOS_H_INCLUDED
