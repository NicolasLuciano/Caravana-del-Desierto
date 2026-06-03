#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sNodoL{
    void * dato;
    unsigned tam;
    struct sNodoL * nodoSig;
    struct sNodoL * nodoAnt;
}tNodoLista;

typedef tNodoLista * tLista;

void crearLista(tLista * lista);
int insertarFinLis(tLista * lista, const void * dato, unsigned tam);
void mostrarLista(const tLista* lista,void (*mostrar)(const void* dato));
void* obtenerDatoPos(const tLista* lista, unsigned pos);
void recorrerListaArchivo(const tLista* lista,FILE*fp,void (*accion)(FILE* fp,const void* dato));
void moverEnLista(tNodoLista ** pos, unsigned pasos, int direccion);

#endif // LISTA_H_INCLUDED
