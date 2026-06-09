#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    unsigned cantCasillas;
    unsigned vidasIniciales;
    unsigned cantPremios;
    unsigned cantOasis;
    unsigned cantTormentas;
    unsigned cantBandidos;
    unsigned cantVidasExtra;
}tConfig;

int cargarConfig(const char* nombreArch, tConfig* configuracion);
void generaraArchivoTablero();

#endif // ARCHIVOS_H_INCLUDED
