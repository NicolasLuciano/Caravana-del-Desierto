#include "../headers/cola.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define COLA_BIEN 1
#define ERROR_COLA -3
#define ERROR_MEMORIA -4
#define MIN(x,y)(x<y?x:y)
void crearCola(tCola* pc)
{
    pc->pri = NULL;
    pc->ult = NULL;
}
int ponerEnCola(tCola* pc, const void* dato, unsigned tam)
{
    tNodo *nue = malloc(sizeof(tNodo));
    if(NULL==nue)
        return ERROR_MEMORIA;
    nue->dato = malloc(tam);
    if(NULL == nue->dato)
    {
        free(nue);
        return ERROR_MEMORIA;
    }
    memcpy(nue->dato,dato,tam);
    nue->tamDato = tam;
    nue->sig = NULL;
    if(pc->ult)
        pc->ult->sig = nue;
    else
        pc->pri = nue;
    pc->ult = nue;
    return COLA_BIEN;
}
int sacarDeCola(tCola* pc, void* dato, unsigned tam)
{
    tNodo *auxPrimero=pc->pri;
    if(NULL==auxPrimero)
        return ERROR_COLA;
    pc->pri=auxPrimero->sig;
    memcpy(dato,auxPrimero->dato,MIN(tam,auxPrimero->tamDato));
    free(auxPrimero->dato);
    free(auxPrimero);
    if(NULL==pc->pri)
        pc->ult = NULL;
    return COLA_BIEN;
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
