#ifndef ARCHIVOS_H_INCLUDED
#define ARCHIVOS_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

#define ERR_ARCH 1
#define TODO_OK 0
typedef struct
{
    int cantCasillas;
    int vidasIniciales;
    int cantPremios;
    int cantOasis;
    int cantTormentas;
    int cantBandidos;
    int cantVidasMax;
}tConfig;

int cargarConfig(const char* nombreArch, tConfig* configuracion);
void generaraArchivoTablero();

#endif // ARCHIVOS_H_INCLUDED
