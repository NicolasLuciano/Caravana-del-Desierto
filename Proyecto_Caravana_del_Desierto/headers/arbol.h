#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

typedef struct sNodoA
{
    void *dato;
    unsigned tam;
    struct sNodoA *nodoIzq;
    struct sNodoA *nodoDer;
}tNodoArbol;

typedef tNodoArbol * tArbol;

void crearArbol(tArbol *arbol);
//void recorrerInOrden(tArbol *arbol, void(*accion)(void*,unsigned));
int insertarArbol(tArbol *arbol,void *dato,unsigned tam, int(*cmp)(const void*,const void*));
int buscarEnArbol(tArbol *arbol,void *dato,unsigned tam, int(*cmp)(const void*,const void*));

void recorrerInOrden(tArbol *arbol,void(*accion)(void*,unsigned));

#endif // ARBOL_H_INCLUDED
