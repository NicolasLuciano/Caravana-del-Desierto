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
void moverBandidos(tLista *tablero, tBandido *vBandidos,tCola *colaMovimientos,unsigned cantBandidos, unsigned cantCasillas)
{
    tCasilla casilla;
    tMovimiento movimiento;
    unsigned i, j, dado;
    i=0;
    while(i<cantBandidos)
    {
        if(VIVO==(vBandidos+i)->vivo)
        {
            dado=tirar_dado(DADO_BANDIDO);

            recuperarDatoLista(&(vBandidos+i)->posicion,0,&casilla,sizeof(casilla));
            casilla.bandido = SIN_BANDIDO;
            modificarEnPosLista(&(vBandidos+i)->posicion,0,&casilla,sizeof(casilla));

            for(j=0;j<dado;j++)
            {
                moverEnLista(&(vBandidos+i)->posicion,(vBandidos+i)->direccion);
            }

            recuperarDatoLista(&(vBandidos+i)->posicion,0,&casilla,sizeof(casilla));
            casilla.bandido = HAY_BANDIDO;
            modificarEnPosLista(&(vBandidos+i)->posicion,0,&casilla,sizeof(casilla));
            if(ADELANTE==(vBandidos+i)->direccion)
                (vBandidos+i)->direccion=ATRAS;
            else
                (vBandidos+i)->direccion=ADELANTE;
        }
        i++;
    }
}
