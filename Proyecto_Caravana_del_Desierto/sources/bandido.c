#include "../headers/bandido.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"
#include "../headers/tablero.h"
tBandido* crearBandidos(unsigned cantBandidos)
{
    tBandido * vecBandidos;
    vecBandidos=malloc(sizeof(tBandido)*cantBandidos);
    if(vecBandidos==NULL)
        return NULL;

    for(int i=0; i<cantBandidos; i++)
    {
        (vecBandidos+i)->vivo=VIVO;
        (vecBandidos+i)->posicion=NULL;
        (vecBandidos+i)->direccion=ADELANTE;
    }

    return vecBandidos;
}

/*void moverBandidos(tLista *tablero, tBandido *vBandidos,tCola *colaMovimientos,unsigned cantBandidos, unsigned cantCasillas)
{
    unsigned dadoBandido;
    tCasilla casilla;
    int posActual,j, flagBandidos=VIVO;

    posActual=0;
    while(posActual<cantCasillas && VIVO==flagBandidos)
    {
        flagBandidos=MUERTO;
        for(j=0;j<cantBandidos;j++)
        {
            if(VIVO==(vBandidos+j)->vivo)
            {
                flagBandidos=VIVO;
                if(TODO_OK==compararNodos(tablero,(vBandidos+j)->pos,posActual))
                {
                    dadoBandido=tirar_dado(DADO_BANDIDO);

                    recuperarDatoLista()
                }
            }
        }
    }
}*/
