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
void recorrerListaArchivo(const tLista* lista,FILE*fp,void (*accion)(FILE* fp,const void* dato));
void moverEnLista(tLista *pos, char direccion);
int recuperarDatoLista(const tLista *lista,unsigned pos,void * dato, unsigned tam);
int modificarEnPosLista(const tLista *lista,unsigned pos, void *dato, unsigned tam);
int compararLista(const tLista *lista1, const tLista *lista2);
void vaciarLista(tLista* lista);
void copiarPosicionLista(tLista *destino, tLista origen);
#endif // LISTA_H_INCLUDED
