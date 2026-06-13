#include "../headers/lista.h"
#include "../headers/constantesymacros.h"

void crearLista(tLista * lista)
{
    *lista=NULL;
}

int insertarFinLista(tLista * lista, const void * dato, unsigned tam)
{
    tNodoLista * nuevoNodo, * nodoActual;

    nuevoNodo=malloc(sizeof(tNodoLista));
    if(nuevoNodo==NULL)
        return SIN_MEM;

    nuevoNodo->dato=malloc(tam);
    if(nuevoNodo->dato==NULL)
    {
        free(nuevoNodo);
        return SIN_MEM;
    }

    memcpy(nuevoNodo->dato,dato,tam);
    nuevoNodo->tam=tam;

    if(*lista==NULL)
    {
        nuevoNodo->nodoSig=nuevoNodo;
        nuevoNodo->nodoAnt=nuevoNodo;
        *lista=nuevoNodo;
        return TODO_OK;
    }

    nodoActual=*lista;

    while(nodoActual->nodoSig!=*lista)
        nodoActual=nodoActual->nodoSig;


    nodoActual->nodoSig=nuevoNodo;
    nuevoNodo->nodoAnt=nodoActual;
    nuevoNodo->nodoSig=*lista;
    (*lista)->nodoAnt=nuevoNodo;


    return TODO_OK;
}

void moverEnLista(tLista *pos, char direccion)
{
    if( ADELANTE == direccion)
        *pos = (*pos)->nodoSig;
    else if( ATRAS == direccion)
        *pos = (*pos)->nodoAnt;
}

void recorrerListaArchivo(const tLista* lista,FILE* fp,void (*accion)(FILE* fp, const void* dato))
{
    tNodoLista* act;

    if(*lista == NULL)
        return;

    act = *lista;

    do
    {
        accion(fp, act->dato);
        act = act->nodoSig;
    }
    while(act != *lista);
}

int recuperarDatoLista(const tLista *lista,unsigned pos,void * dato, unsigned tam)
{
    tNodoLista *auxNodo = *lista;
    unsigned i=0;
    while(i<pos && auxNodo->nodoSig != *lista)
    {
        auxNodo=auxNodo->nodoSig;
        i++;
    }
    if(i==pos)
    {
        memcpy(dato,auxNodo->dato,MIN(tam,auxNodo->tam));
        return TODO_OK;
    }
    return LISTA_ERROR;
}

int modificarEnPosLista(const tLista *lista,unsigned pos, void *dato, unsigned tam)
{
    tNodoLista *actual = *lista;
    unsigned i=0;
    while(i<pos && actual->nodoSig!=*lista)
    {
        actual=actual->nodoSig;
        i++;
    }
    if(i==pos)
    {
        memcpy(actual->dato,dato,MIN(tam,actual->tam));
        return TODO_OK;
    }
    return LISTA_ERROR;
}

int compararLista(const tLista *lista1, const tLista *lista2)
{
    return *lista1==*lista2;
}

void vaciarLista(tLista *lista)
{
    tNodoLista *elim;

    if(*lista == NULL)
        return;

    while((*lista)->nodoSig != *lista)
    {
        elim = (*lista)->nodoSig;
        (*lista)->nodoSig = elim->nodoSig;
        elim->nodoSig->nodoAnt = *lista;

        free(elim->dato);
        free(elim);
    }

    free((*lista)->dato);
    free(*lista);
    *lista = NULL;
}

void copiarPosicionLista(tLista *destino, tLista origen)
{
    *destino = origen;
}

