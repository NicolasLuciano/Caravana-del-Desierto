#include "../headers/arbol.h"
#include "../headers/constantesymacros.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void crearArbol(tArbol *arbol)
{
    *arbol = NULL;
}

//void recorrerInOrden(tArbol *arbol, void(*accion)(void*,unsigned))
//{
//    if(!*arbol)
//        return;
//    recorrerInOrden(&(*arbol)->nodoIzq, accion);
//    accion((*arbol)->dato,(*arbol)->tam);
//    recorrerInOrden(&(*arbol)->nodoDer, accion);
//
//}

int buscarEnArbol(tArbol *arbol,void *dato,unsigned tam, int(*cmp)(const void*,const void*))
{
    int comp;
    if(!*arbol)
        return NO_ENCONTRADO;
    comp =cmp(dato,(*arbol)->dato);
    if(0==comp)
    {
        memcpy(dato,(*arbol)->dato,MIN(tam,(*arbol)->tam));
        return TODO_OK;
    }
    if(comp<0)
        return buscarEnArbol(&(*arbol)->nodoIzq,dato,tam,cmp);

    return buscarEnArbol(&(*arbol)->nodoDer,dato,tam,cmp);
}

int insertarArbol(tArbol *arbol,void *dato,unsigned tam, int(*cmp)(const void*,const void*))
{
    if(!*arbol)
    {
        tNodoArbol *nodoAux;
        nodoAux = malloc(sizeof(tNodoArbol));
        if(!nodoAux)
            return SIN_MEM;
        nodoAux->dato = malloc(tam);
        if(!nodoAux->dato)
        {
            free(nodoAux);
            return SIN_MEM;
        }
        memcpy(nodoAux->dato,dato,tam);
        nodoAux->tam=tam;
        nodoAux->nodoIzq=NULL;
        nodoAux->nodoDer=NULL;
        *arbol = nodoAux;
        return TODO_OK;
    }
    if(cmp(dato,(*arbol)->dato)<0)
        return insertarArbol(&(*arbol)->nodoIzq,dato,tam,cmp);
    if(cmp(dato,(*arbol)->dato)>0)
        return insertarArbol(&(*arbol)->nodoDer,dato,tam,cmp);
    return DUPLICADO_ERROR;
}
