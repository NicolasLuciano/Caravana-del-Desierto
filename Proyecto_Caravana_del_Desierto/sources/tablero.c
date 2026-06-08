#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include <time.h>

int generarTablero(tLista *tablero,const tConfig configuracion, tBandido * bandidos)
{
    int * vecPosiciones,i;
    tCasilla casilla;
    char *cadPosiciones;
    srand(time(NULL));


    vecPosiciones=malloc(sizeof(int)*configuracion.cantCasillas);
    if(NULL==vecPosiciones)
        return SIN_MEM;
    cadPosiciones = malloc(configuracion.cantCasillas);
    if(NULL==cadPosiciones)
        return SIN_MEM;

    casilla.tipo = INICIO;
    casilla.numCasilla=1;
    insertarFinLis(tablero, &casilla, sizeof(tCasilla));

    mezclarPosiciones(vecPosiciones,configuracion.cantCasillas);
    distribuirCasillas(vecPosiciones,cadPosiciones,configuracion);
    for(i = 0; i < configuracion.cantCasillas; i++)
    printf("%d -> %c\n", i, cadPosiciones[i]);

    for(i=0;i<configuracion.cantCasillas-2;i++)
    {
        casilla.tipo= (char)(*(cadPosiciones+i));
        casilla.numCasilla++;
        insertarFinLis(tablero, &casilla, sizeof(tCasilla));
    }
    casilla.tipo = SALIDA;
    casilla.numCasilla=configuracion.cantCasillas;
    insertarFinLis(tablero, &casilla, sizeof(tCasilla));


    free(vecPosiciones);
    free(cadPosiciones);
    return 0;
}

void mezclarPosiciones(int *vecPosiciones, int cantCasillas)
{
    int i, j, aux;

    for(i = 0; i < cantCasillas; i++)
        vecPosiciones[i] = i;

    for(i = cantCasillas - 2; i > 0; i--)
    {
        j = rand() % (i + 1);

        aux = vecPosiciones[i];
        vecPosiciones[i] = vecPosiciones[j];
        vecPosiciones[j] = aux;
    }
}
//FALTA DISTRIBUIR BANDIDOS
void distribuirCasillas(int *vecPos,char *cadPos, tConfig config)
{
    int i, *auxVec, casillasVacias = config.cantCasillas - (
                                                 config.cantOasis +
                                                 config.cantPremios +
                                                 config.cantTormentas +
                                                 config.cantVidasExtra);
    auxVec= vecPos;
    for(i=0;i<config.cantOasis;i++)
    {
        *(cadPos + *auxVec)= OASIS;
        auxVec++;
    }
    for(i=0;i<config.cantPremios;i++)
    {
        *(cadPos + *auxVec)= PREMIO;
        auxVec++;
    }
    for(i=0;i<config.cantTormentas;i++)
    {
        *(cadPos + *auxVec)= TORMENTA;
        auxVec++;
    }
    for(i=0;i<config.cantVidasExtra;i++)
    {
        *(cadPos + *auxVec)= VIDAEXTRA;
        auxVec++;
    }
    for(i=0;i<casillasVacias;i++)
    {
        *(cadPos + *auxVec)= VACIA;
        auxVec++;
    }
}
void mostrarTablero(const tLista* tablero, const tBandido*bandidos, unsigned cantBandidos)
{
    tNodoLista * tableroAux;
    tCasilla casilla;
    int i;

    tableroAux=*tablero;
    while(tableroAux->nodoSig != *tablero )
    {
        i=0;
        recuperarDatoLista(tableroAux,&casilla,sizeof(tCasilla));

        while(i<cantBandidos && tableroAux!=(bandidos+i)->posicion)
            i++;

        if(i<cantBandidos)
            printf("%02d:B\n",casilla.numCasilla);
        else
            printf("%02d:%c\n",casilla.numCasilla,casilla.tipo);

        tableroAux=tableroAux->nodoSig;
    }
    recuperarDatoLista(tableroAux,&casilla,sizeof(tCasilla));
    printf("%02d:%c\n",casilla.numCasilla,casilla.tipo);

}
