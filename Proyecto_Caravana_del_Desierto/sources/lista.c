#include "../headers/lista.h"
#include <string.h>

#define LISTA_OK 0
#define LISTA_ERROR -1
#define ADELANTE 1
#define SIN_MEM -2;

#define MIN(x,y)(x>y?y:x)

void crearLista(tLista * lista)
{
    *lista=NULL;
}

int insertarFinLis(tLista * lista, const void * dato, unsigned tam)
{
    tNodoLista * nuevoNodo, * nodoActual;

    nuevoNodo=malloc(sizeof(tNodo));
    if(nuevoNodo==NULL)
        return SIN_MEM;

    nuevoNodo->dato=malloc(tam);
    if(nuevoNodo->dato==NULL)
    {
        free(nuevoNodo);
        return SIN_MEM;
    }

    memcpy(nuevoNodo->dato,dato,tam);
    nuevoNodo->tam=tam;

    if(*lista==NULL)
    {
        nuevoNodo->nodoSig=nuevoNodo;
        nuevoNodo->nodoAnt=nuevoNodo;
        *lista=nuevoNodo;
        return LISTA_OK;
    }

    nodoActual=*lista;

    while(nodoActual->nodoSig!=*lista)
        nodoActual=nodoActual->nodoSig;


    nodoActual->nodoSig=nuevoNodo;
    nuevoNodo->nodoAnt=nodoActual;
    nuevoNodo->nodoSig=*lista;
    (*lista)->nodoAnt=nuevoNodo;


    return LISTA_OK;
}

tNodo * moverEnLista(tNodoLista * pos, unsigned pasos, int direccion)
{
    int i;
    if(direccion==ADELANTE)
    {
        for(i=0;i<pasos;i++)
            pos=pos->nodoSig;
    }
    else
        for(i=0;i<pasos;i++)
            pos=pos->nodoAnt;

    return pos;
}

