#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct sNodo{
    void * dato;
    unsigned tam;
    struct sNodo * nodoSig;
    struct sNodo * nodoAnt;
}tNodoLista;

typedef tNodoLista * tLista;

void crearLista(tLista * lista);
int insertarFinLis(tLista * lista, const void * dato, unsigned tam);
void moverEnLista(tNodoLista ** pos, unsigned pasos, int direccion);
void mostrarLista(tLista * lista);

#endif // LISTA_H_INCLUDED
