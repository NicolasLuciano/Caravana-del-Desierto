#include "../headers/arbol.h"
#include "../headers/constantesymacros.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void crearArbol(tArbol *arbol)
{
    *arbol = NULL;
}

int cargarVectorInOrden(tArbol *arbol,void **vec,unsigned *pos, unsigned tam, unsigned *capacidad)
{
    if(!(*arbol))
        return TODO_OK;
    if(cargarVectorInOrden(&(*arbol)->nodoIzq,vec,pos,tam,capacidad)!=TODO_OK)
        return SIN_MEM;

    if(*pos>=*capacidad)
    {
        void *aux;
        *capacidad = *capacidad *2;
        aux = realloc(*vec, *capacidad * tam);
        if(!aux)
            return SIN_MEM;
        *vec = aux;
    }

    memcpy((char*)*vec + (*pos) * tam,(*arbol)->dato,tam);
    (*pos)++;

     if(cargarVectorInOrden(&(*arbol)->nodoDer,vec,pos,tam,capacidad)!=TODO_OK)
        return SIN_MEM;
    return TODO_OK;
}

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
