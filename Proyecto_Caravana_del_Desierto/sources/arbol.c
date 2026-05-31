#include "../headers/arbol.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define ARBOL_BIEN 1
#define ERROR_MEM -5
#define ERROR_DUPLICADO -6
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
            return ERROR_MEM;
        nodoAux->dato = malloc(tam);
        if(!nodoAux->dato)
        {
            free(nodoAux);
            return ERROR_MEM;
        }
        memcpy(nodoAux->dato,dato,tam);
        nodoAux->tam=tam;
        nodoAux->nodoIzq=NULL;
        nodoAux->nodoDer=NULL;
        *arbol = nodoAux;
        return ARBOL_BIEN;
    }
    if(cmp(dato,(*arbol)->dato)<0)
        return insertarArbol(&(*arbol)->nodoIzq,dato,tam,cmp);
    if(cmp(dato,(*arbol)->dato)>0)
        return insertarArbol(&(*arbol)->nodoDer,dato,tam,cmp);
    return ERROR_DUPLICADO;
}
