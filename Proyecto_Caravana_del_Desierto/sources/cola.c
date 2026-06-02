#include "../headers/cola.h"
#include "../headers/constantesymacros.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
void crearCola(tCola* pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}
int ponerEnCola(tCola* pc, const void* dato, unsigned tam)
{
    tNodo *nue = malloc(sizeof(tNodo));
    if(NULL==nue)
        return SIN_MEM;
    nue->dato = malloc(tam);
    if(NULL == nue->dato)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->dato,dato,tam);
    nue->tamDato = tam;
    nue->sig = NULL;
    if(pc->ult)
        pc->ult->sig = nue;
    else
        pc->pri = nue;
    pc->ult = nue;
    return TODO_OK;
}
int sacarDeCola(tCola* pc, void* dato, unsigned tam)
{
    tNodo *auxPrimero=pc->pri;
    if(NULL==auxPrimero)
        return COLA_ERROR;
    pc->pri=auxPrimero->sig;
    memcpy(dato,auxPrimero->dato,MIN(tam,auxPrimero->tamDato));
    free(auxPrimero->dato);
    free(auxPrimero);
    if(NULL==pc->pri)
        pc->ult = NULL;
    return TODO_OK;
}
int colaVacia(const tCola* pc)
{
    return NULL == pc->pri;
}
void vaciarCola(tCola* pc)
{
    while(pc->pri)
    {
        tNodo *aux = pc->pri;
        pc->pri = aux->sig;
        free(aux->dato);
        free(aux);
    }
    pc->ult = NULL;
}
