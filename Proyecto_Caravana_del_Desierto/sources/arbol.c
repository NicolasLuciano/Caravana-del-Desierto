#include "../headers/arbol.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/constantesymacros.h"

void crearArbol(tArbol *arbol)
{
    *arbol = NULL;
}

void recorrerInOrden(tArbol *arbol, void(*accion)(void*,unsigned))
{
    if(!*arbol)
        return;
    recorrerInOrden(&(*arbol)->nodoIzq, accion);
    accion((*arbol)->dato,(*arbol)->tam);
    recorrerInOrden(&(*arbol)->nodoDer, accion);

}

int insertarArbol(tArbol *arbol,void *dato,unsigned tam, int(*cmp)(void*,void*))
{
    if(!*arbol)
    {
        tNodo *nodoAux;
        nodoAux = malloc(sizeof(tNodo));
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
    return ERROR_DUPLICADO;
}
