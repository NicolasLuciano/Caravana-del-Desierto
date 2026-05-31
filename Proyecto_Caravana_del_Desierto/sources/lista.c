#include "../headers/lista.h"
#include <string.h>

#define LISTA_OK 0
#define LISTA_ERROR -1
#define SIN_MEM -2;

#define MIN(x,y)(x>y?y:x)

void crearLista(tLista * lista)
{
    *lista=NULL;
}

int insertarFinLis(tLista * lista, const void * dato, unsigned tam)
{
    tNodo * nuevoNodo, * nodoActual;

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

tNodo * moverAdelante(tNodo * pos,  unsigned pasos)
{
    int i;
    for(i=0;i<pasos;i++)
        pos=pos->nodoSig;

    return pos;
}

tNodo * moverAtras(tNodo * pos,  unsigned pasos)
{
    int i;
    for(i=0;i<pasos;i++)
        pos=pos->nodoAnt;

    return pos;
}

int eliminarPorClave(tLista * lista,const void * clave,  unsigned tam, int (*cmp)(const void *a,const void *b));
{

}
