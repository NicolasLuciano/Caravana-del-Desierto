#include "../headers/lista.h"
#include "../headers/constantesymacros.h"




void crearLista(tLista * lista)
{
    *lista=NULL;
}

int insertarFinLis(tLista * lista, const void * dato, unsigned tam)
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

void moverEnLista(const tLista *lista,tNodoLista **pos, unsigned pasos, int direccion)
{
    int i;

    if(direccion == ADELANTE)
    {
        for(i = 0; i < pasos; i++)
            *pos = (*pos)->nodoSig;
    }
    else
    {
        for(i = 0; i < pasos; i++)
            *pos = (*pos)->nodoAnt;
    }
}

void posicionarEnLista(const tLista *lista,tNodoLista **pos, unsigned pasos)
{
    int i;
    *pos=*lista;
    for(i = 0; i < pasos; i++)
        *pos = (*pos)->nodoSig;
}
void* obtenerDatoPos(const tLista* lista, unsigned pos)
{
    tNodoLista* act;

    if(*lista == NULL)
        return NULL;

    act = *lista;

    while(pos--)
        act = act->nodoSig;

    return act->dato;
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

int recuperarDatoLista(tLista *lista,unsigned pos,void * dato, unsigned tam)
{
    tNodoLista *auxNodo = *lista;
    unsigned i=0;
    while(i<pos && auxNodo->nodoSig != *lista)
    {
        auxNodo=&(*(auxNodo)->nodoSig);
        i++;
    }
    if(i==pos)
    {
        memcpy(dato,auxNodo->dato,MIN(tam,auxNodo->tam));
        return TODO_OK;
    }
    return LISTA_ERROR;
}

int eliminarListaPos(tLista *lista,unsigned pos,void * dato, unsigned tam)
{
    tNodoLista *elim,*listaMov = *lista;

    unsigned i=0;

    while(i<pos && auxNodo->nodoSig != *lista)
    {
        auxNodo=&(*(auxNodo)->nodoSig);
        i++;
    }
    if(i==pos)
    {
        memcpy(dato,auxNodo->dato,MIN(tam,auxNodo->tam));

        return TODO_OK;
    }
    return LISTA_ERROR;
}

