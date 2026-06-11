#include "../headers/bandido.h"
#include "../headers/constantesymacros.h"
#include "../headers/dado.h"
#include "../headers/tablero.h"
tBandido* crearBandidos(unsigned cantBandidos)
{
    tBandido * vecBandidos;
    unsigned direccion;
    vecBandidos=malloc(sizeof(tBandido)*cantBandidos);
    if(vecBandidos==NULL)
        return NULL;

    direccion = ADELANTE;
    for(int i=0; i<cantBandidos; i++)
    {
        ((vecBandidos+i)->vivo=VIVO);
        ((vecBandidos+i)->posicion=NULL);
        ((vecBandidos+i)->direccion=direccion);
        direccion = direccion * ATRAS;
    }

    return vecBandidos;
}
void moverBandidos(tLista *tablero, tBandido *vBandidos,tCola *colaMovimientos,unsigned cantBandidos, unsigned cantCasillas)
{
    tCasilla casilla;
    unsigned i, mov, dado;
    i=0;
    while(i<cantBandidos)
    {
        if(VIVO==(vBandidos+i)->vivo)
        {
            dado=tirar_dado(DADO_BANDIDO);

            recuperarDatoLista(&(vBandidos+i)->posicion,0,&casilla,sizeof(casilla));
            casilla.bandido = SIN_BANDIDO;
            modificarEnPosLista(&(vBandidos+i)->posicion,0,&casilla,sizeof(casilla));

            for(mov=0;mov<dado;mov++)
            {
                moverEnLista(&(vBandidos+i)->posicion,(vBandidos+i)->direccion);
            }

            recuperarDatoLista(&(vBandidos+i)->posicion,0,&casilla,sizeof(casilla));
            casilla.bandido = HAY_BANDIDO;
            modificarEnPosLista(&(vBandidos+i)->posicion,0,&casilla,sizeof(casilla));
        }
        i++;
    }
}
//void moverBandidos(tLista *tablero, tBandido *vBandidos,tCola *colaMovimientos,unsigned cantBandidos, unsigned cantCasillas)
//{
//    unsigned dadoBandido, nuevaPos;
//    int posActual,j, flagBandidos=VIVO;
//
//    posActual=0;
//    while(posActual<cantCasillas && VIVO==flagBandidos)
//    {
//        flagBandidos=MUERTO;
//        for(j=0; j<cantBandidos; j++)
//        {
//            if(VIVO==(vBandidos+j)->vivo)
//            {
//                flagBandidos=VIVO;
//                (vBandidos+j)->posCasilla.bandido=MUERTO;
//                modificarEnPosLista(tablero,(vBandidos+j)->posCasilla.numCasilla,(vBandidos+j)->posCasilla,sizeof((vBandidos+j)->posCasilla));
//                (vBandidos+j)->posCasilla.bandido=VIVO;
//
//                dadoBandido=tirar_dado(DADO_BANDIDO);
//                nuevaPos = (vBandidos+j)->direccion * dadoBandido
//            }
//        }
//    }
//}
