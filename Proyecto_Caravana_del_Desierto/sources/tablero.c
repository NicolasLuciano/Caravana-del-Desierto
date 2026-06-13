#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include <time.h>
#include <string.h>

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

    casilla.bandido=MUERTO;
    casilla.jugador=HAY_JUGADOR;
    casilla.tipo = INICIO;
    casilla.numCasilla=1;
    insertarFinLista(tablero, &casilla, sizeof(tCasilla));

    mezclarPosiciones(vecPosiciones,configuracion.cantCasillas);
    distribuirCasillas(vecPosiciones,cadPosiciones,configuracion, &posBandidos);

    casilla.jugador=SIN_JUGADOR;

    for(i=0; i<configuracion.cantCasillas-2; i++)
    {
        casilla.tipo= (char)(*(cadPosiciones+i));
        casilla.numCasilla++;
        insertarFinLista(tablero, &casilla, sizeof(tCasilla));
    }

    casilla.tipo = SALIDA;
    casilla.numCasilla=configuracion.cantCasillas;
    insertarFinLista(tablero, &casilla, sizeof(tCasilla));

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

    for(i=0; i<config.cantCasillas; i++)
        *(cadPos+i)=VACIA;

    auxVec= vecPos;
    for(i=0; i<config.cantOasis; i++)
    {
        *(cadPos + *auxVec)= OASIS;
        auxVec++;
    }
    for(i=0; i<config.cantPremios; i++)
    {
        *(cadPos + *auxVec)= PREMIO;
        auxVec++;
    }
    for(i=0; i<config.cantTormentas; i++)
    {
        *(cadPos + *auxVec)= TORMENTA;
        auxVec++;
    }
    for(i=0; i<config.cantVidasExtra; i++)
    {
        *(cadPos + *auxVec)= VIDAEXTRA;
        auxVec++;
    }
    for(i=0; i<config.cantBandidos; i++)
    {
        *(*(posBandidos)+i)=*auxVec;
        auxVec++;
    }
}

void mostrarTablero(const tLista tablero, unsigned cantCasillas)
{
    int i;
    tCasilla casilla;
    char linea[10];
    for(i=0; i<cantCasillas; i++)
    {
        recuperarDatoLista(&tablero,i,&casilla,sizeof(tCasilla));
        linea[0] = '\0';

        if(casilla.tipo != VACIA)
            sprintf(linea, "%c ", casilla.tipo);

        if(casilla.jugador == HAY_JUGADOR)
            sprintf(linea + strlen(linea), "%c ", JUGADOR);

        if(casilla.bandido == HAY_BANDIDO)
            sprintf(linea + strlen(linea), "%c ", BANDIDO);

        if(strlen(linea) > 0)
        {
            linea[strlen(linea)-1] = '\0';

            if(strlen(linea) > 1)
                printf("%02d: [%s]\n", casilla.numCasilla, linea);
            else
                printf("%02d: %s\n", casilla.numCasilla, linea);
        }
        else
            printf("%02d: %c\n", casilla.numCasilla, casilla.tipo);
    }
}

void distribuirBandidos(const tLista *tablero, tBandido *vBandidos, unsigned cantBandidos, int *posBandidos)
{

    unsigned i, mov;
    tCasilla casilla;
    for(i=0; i<cantBandidos; i++)
    {
        copiarPosicionLista(&((vBandidos+i)->posicion),*tablero);
        for(mov=0;mov< *(posBandidos+i)+1;mov++)
            moverEnLista(&((vBandidos+i)->posicion),ADELANTE);
        recuperarDatoLista(&((vBandidos+i)->posicion),0,&casilla,sizeof(casilla));
        casilla.bandido=HAY_BANDIDO;
        modificarEnPosLista(&((vBandidos+i)->posicion),0,&casilla,sizeof(casilla));
    }
}

int validarTablero(tConfig config)
{
    int totalElementos;

    if(config.cantBandidos < 1 || config.cantPremios < 1 ||
       config.cantOasis < 1 || config.cantTormentas < 1 ||
       config.cantVidasExtra < 1)
        return  TABLERO_INVALIDO;

    totalElementos = config.cantBandidos + config.cantPremios + config.cantOasis
                        + config.cantTormentas + config.cantVidasExtra;

    if(totalElementos < (int)(config.cantCasillas * MIN_OCUPACION))
        return  TABLERO_INVALIDO;

    if(totalElementos > (int)(config.cantCasillas * MAX_OCUPACION))
        return  TABLERO_INVALIDO;

    return TODO_OK;
}

