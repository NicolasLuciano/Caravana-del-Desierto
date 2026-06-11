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

void moverEnLista(tLista *pos, int direccion)
{
    if( ADELANTE == direccion)
        *pos = (*pos)->nodoSig;
    else if( ATRAS == direccion)
        *pos = (*pos)->nodoAnt;
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

int compararNodos(const tLista *lista, tNodoLista *nodo, unsigned pos)
{
    tNodoLista *aux = *lista;
    int i=0;
    while(i<pos && aux->nodoSig!=*lista)
    {
        aux=aux->nodoSig;
        i++;
    }

    if(i==pos)
        return TODO_OK;
    return LISTA_ERROR;
}

/*int buscarNodoLista(const tLista *lista, tNodoLista *nodo)
{
    tNodoLista *aux = *lista;
    int pos=NO_ENCONTRADO;
    while(aux!=nodo && aux->nodoSig!=*lista)
    {
        aux=aux->nodoSig;
        i++;
    }
    if(aux==nodo)
        pos=i;
    return pos;
}*/

tNodoLista* obtenerPrimero(const tLista* lista)
{
    return *lista;
}

void vaciarLista(tLista* lista)
{
    tNodoLista * nodoElim;
    while(NULL != lista){
        nodoElim = *lista;
        lista = &(*lista)->nodoSig;
        free(nodoElim->dato);
        free(nodoElim);
    }
}

void copiarPosicionLista(tLista *destino, tLista origen)
{
    *destino = origen;
}
