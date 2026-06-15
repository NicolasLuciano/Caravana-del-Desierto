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
int cargarVectorInOrden(tArbol *arbol,void **vec,unsigned *pos, unsigned tam, unsigned *capacidad);

#endif // ARBOL_H_INCLUDED
