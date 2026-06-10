#ifndef INDICES_H_INCLUDED
#define INDICES_H_INCLUDED

#include "constantesymacros.h"

typedef struct
{
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
} tClave;

typedef struct
{
    unsigned indice;
    tClave clave;
} tIndice;

int compararPorNombreDeUsuario(void* a, void* b);
void cargarArchivoEnIndice(const char* nombreArchivo, tArbol* arbol);
#endif // INDICES_H_INCLUDED
