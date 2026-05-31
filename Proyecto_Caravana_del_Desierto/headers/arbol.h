#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

typedef struct sNodo{
    void *dato;
    unsigned tam;
    struct sNodo *nodoIzq;
    struct sNodo *nodoDer;
} tNodo;

typedef tNodo * tArbol;

void crearArbol(tArbol *arbol);
void recorrerInOrden(tArbol *arbol, void(*accion)(void*,unsigned));
int insertarArbol(tArbol *arbol,void *dato,unsigned tam, int(*cmp)(void*,void*));

#endif // ARBOL_H_INCLUDED
