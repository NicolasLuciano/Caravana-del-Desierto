#include "../headers/bandido.h"
#include "../headers/constantesymacros.h"

tBandido * crearBandidos( unsigned cantBandidos)
{
    tBandido * vecBandidos;
    vecBandidos=malloc(sizeof(tBandido)*cantBandidos);
    if(vecBandidos==NULL)
        return NULL;

    return vecBandidos;
}
