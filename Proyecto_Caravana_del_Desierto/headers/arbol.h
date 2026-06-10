#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

typedef struct sNodoA
{
    void *dato;
    unsigned tam;
    struct sNodoA *nodoIzq;
    struct sNodoA *nodoDer;
} tNodo;

typedef tNodo * tArbol;

void crearArbol(tArbol *arbol);
void recorrerInOrden(tArbol *arbol, void(*accion)(void*,unsigned));
int insertarArbol(tArbol *arbol,void *dato,unsigned tam, int(*cmp)(void*,void*));

#endif // ARBOL_H_INCLUDED
