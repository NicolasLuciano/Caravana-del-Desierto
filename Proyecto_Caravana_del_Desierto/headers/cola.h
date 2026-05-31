#ifndef COLA_H_INCLUDED
#define COLA_H_INCLUDED

typedef struct sNodo
{
    void *dato;
    unsigned tamDato;
    struct sNodo *sig;
}tNodo;

typedef struct
{
    tNodo *pri, *ult;
}tCola;

void crearCola(tCola* pc);
int ponerEnCola(tCola* pc, const void* dato, unsigned tam);
int sacarDeCola(tCola* pc, void* dato, unsigned tam);
int colaVacia(const tCola* pc);
void vaciarCola(tCola* pc);

#endif // COLA_H_INCLUDED
