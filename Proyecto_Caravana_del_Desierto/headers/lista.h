#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef struct sNodo{
    void * dato;
    unsigned tam;
    struct sNodo * nodoSig;
    struct sNodo * nodoAnt;
}tNodo;

typedef tNodo * tLista;

void crearLista(tLista * lista);
int insertarFinLis(tLista * lista, const void * dato, unsigned tam);
tNodo * moverAdelante(tNodo * pos, const unsigned pasos);
tNodo * moverAtras(tNodo * pos, unsigned pasos);
int eliminarPorClave(tLista * lista,const void * clave,  unsigned tam, int (*cmp)(const void *a,const void *b));
void mostrarLista(tLista * lista);

#endif // LISTA_H_INCLUDED
