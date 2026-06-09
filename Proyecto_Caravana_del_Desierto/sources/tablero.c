#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include <time.h>

int generarTablero(tLista *tablero,const tConfig configuracion, tBandido * bandidos)
{
    int * vecPosiciones,i, *posBandidos;
    tCasilla casilla;
    char *cadPosiciones;
    srand(time(NULL));

    vecPosiciones=malloc(sizeof(int)*configuracion.cantCasillas);
    if(NULL==vecPosiciones)
        return SIN_MEM;

    posBandidos=malloc(sizeof(int)*configuracion.cantBandidos);
    if(NULL==posBandidos)
    {
        free(vecPosiciones);
        return SIN_MEM;
    }
    cadPosiciones = malloc(configuracion.cantCasillas);
    if(NULL==cadPosiciones)
    {
        free(vecPosiciones);
        free(posBandidos);
        return SIN_MEM;
    }

    casilla.bandido=0;
    casilla.tipo = INICIO;
    casilla.numCasilla=1;
    insertarFinLis(tablero, &casilla, sizeof(tCasilla));

    mezclarPosiciones(vecPosiciones,configuracion.cantCasillas);
    distribuirCasillas(vecPosiciones,cadPosiciones,configuracion, &posBandidos);

    for(i=0;i<configuracion.cantCasillas-2;i++)
    {
        casilla.tipo= (char)(*(cadPosiciones+i));
        casilla.numCasilla++;
        insertarFinLis(tablero, &casilla, sizeof(tCasilla));
    }

    casilla.tipo = SALIDA;
    casilla.numCasilla=configuracion.cantCasillas;
    insertarFinLis(tablero, &casilla, sizeof(tCasilla));

    distribuirBandidos(tablero,bandidos,configuracion.cantBandidos,posBandidos);

    free(vecPosiciones);
    free(cadPosiciones);
    free(posBandidos);
    return 0;
}

void mezclarPosiciones(int *vecPosiciones, int cantCasillas)
{
    int i, j, aux;

    for(i = 0; i < cantCasillas-2; i++)
        vecPosiciones[i] = i;

    for(i = cantCasillas - 3; i > 0; i--)
    {
        j = rand() % (i + 1);

        aux = vecPosiciones[i];
        vecPosiciones[i] = vecPosiciones[j];
        vecPosiciones[j] = aux;
    }
}
//FALTA DISTRIBUIR BANDIDOS
void distribuirCasillas(int *vecPos,char *cadPos, tConfig config, int **posBandidos)
{
    int i, *auxVec;

    for(i=0;i<config.cantCasillas;i++)
        *(cadPos+i)=VACIA;

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
    for(i=0;i<config.cantBandidos;i++)
    {
        *(*(posBandidos)+i)=*auxVec;
        auxVec++;
    }
}

void mostrarTablero(const tLista* tablero, unsigned cantCasillas)
{
    int i;
    tCasilla casilla;
    for(i=0; i<cantCasillas; i++)
    {
        recuperarDatoLista(tablero,i,&casilla,sizeof(tCasilla));
        printf("%d: ", i+1);
        if(VIVO==casilla.bandido)
        {
            if(VACIA==casilla.tipo)
                printf("%c\n",BANDIDO);
            else
                printf("[%c %c]\n",BANDIDO, casilla.tipo);
        }
        else
        printf("%c\n",casilla.tipo);
    }
}

void distribuirBandidos(const tLista *tablero, tBandido *vBandidos, unsigned cantBandidos, int *posBandidos)
{
    int i;
    tCasilla casilla;
    for(i=0;i<cantBandidos;i++)
    {
        recuperarDatoLista(tablero,*(posBandidos+i)+1,&casilla,sizeof(casilla));
        posicionarEnLista(tablero,&((vBandidos+i)->posicion),*(posBandidos+i)+1);
        casilla.bandido=VIVO;
        modificarEnPosLista(tablero,*(posBandidos+i)+1,&casilla,sizeof(casilla));
    }
}
