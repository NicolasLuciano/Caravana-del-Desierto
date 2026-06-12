#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sNodoL
{
    void * dato;
    unsigned tam;
    struct sNodoL * nodoSig;
    struct sNodoL * nodoAnt;
} tNodoLista;

typedef tNodoLista * tLista;

void crearLista(tLista * lista);

int insertarFinLista(tLista * lista, const void * dato, unsigned tam);

void* obtenerDatoPos(const tLista* lista, unsigned pos);

void recorrerListaArchivo(const tLista* lista,FILE*fp,void (*accion)(FILE* fp,const void* dato));

void moverEnLista(tLista *pos, char direccion);

int recuperarDatoLista(const tLista *lista,unsigned pos,void * dato, unsigned tam);

void posicionarEnLista(const tLista *lista,tNodoLista **pos, unsigned pasos);

int modificarEnPosLista(const tLista *lista,unsigned pos, void *dato, unsigned tam);

int compararLista(const tLista *lista1, const tLista *lista2);

tNodoLista* obtenerPrimero(const tLista* lista);

void vaciarLista(tLista* lista);

void copiarPosicionLista(tLista *destino, tLista origen);
#endif // LISTA_H_INCLUDED
