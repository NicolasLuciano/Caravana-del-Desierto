#include "../headers/bandido.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"
#include "../headers/tablero.h"
#include "../headers/partida.h"
tBandido* crearBandidos(unsigned cantBandidos)
{
    tBandido * vecBandidos;
    unsigned direccion;
    vecBandidos=malloc(sizeof(tBandido)*cantBandidos);
    if(vecBandidos==NULL)
        return NULL;

    for(int i=0; i<cantBandidos; i++)
    {
        if(i%2==0)
            direccion=ADELANTE;
        else
            direccion=ATRAS;
        ((vecBandidos+i)->vivo=VIVO);
        ((vecBandidos+i)->posicion=NULL);
        ((vecBandidos+i)->direccion=direccion);
    }

    return vecBandidos;
}
void encolarBandidos(tBandido *vBandidos,tCola *colaMovimientos,unsigned cantBandidos, unsigned cantCasillas)
{
    tMovimiento movimiento;
    unsigned i;
    i=0;

    while(i<cantBandidos)
    {
        if(VIVO==(vBandidos+i)->vivo)
        {
            movimiento.casillas = tirar_dado(DADO_BANDIDO);
            movimiento.direccion = (vBandidos+i)->direccion;

            ponerEnCola(colaMovimientos,&movimiento,sizeof(movimiento));

            if(ADELANTE==(vBandidos+i)->direccion)
                (vBandidos+i)->direccion = ATRAS;
            else
                (vBandidos+i)->direccion = ADELANTE;
        }
        i++;
    }
}


