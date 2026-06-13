#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#include "partida.h"
#include "config.h"

int cargarConfig(const char* nombreArch, tConfig* configuracion);
void generaraArchivoTablero();
int guardarPartida(tPartida partida, char * NOMARCH3);

#endif // ARCHIVOS_H_INCLUDED
