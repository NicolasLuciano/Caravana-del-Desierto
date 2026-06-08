#include "../headers/bandido.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"
tBandido * crearBandidos( unsigned cantBandidos)
{
    tBandido * vecBandidos;
    vecBandidos=malloc(sizeof(tBandido)*cantBandidos);
    if(vecBandidos==NULL)
        return NULL;

    for(int i=0; i<cantBandidos; i++)
    {
        (vecBandidos->vivo=MUERTO);
        (vecBandidos->posicion=NULL);
        (vecBandidos->direccion=ADELANTE);
    }

    return vecBandidos;
}

void moverBandidos(tLista *tablero, tBandido *vBandidos,tCola *colaMovimientos,unsigned cantBandidos)
{
    unsigned dadoBandido;
    int i;
    char casilla;
    for(i=0;i<cantBandidos;i++)
    {
        if(VIVO==(vBandidos+i)->vivo)
        {
            dadoBandido = tirar_dado(DADO_BANDIDO);
            moverEnLista(&(vBandidos+i)->posicion,dadoBandido,(vBandidos+i)->direccion);
        //falta la funcion de recuperar casilla
            recuperarDatoLista((vBandidos+i)->posicion,&casilla,sizeof(casilla));
            if(SALIDA==casilla)
                moverEnLista(&(vBandidos+i)->posicion,ADELANTE,(vBandidos+i)->direccion);

            (vBandidos+i)->direccion*=-1;
        }
    }
}
