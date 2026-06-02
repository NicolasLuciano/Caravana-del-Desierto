#include "../headers/tablero.h"

int casillaLibre(const tCasilla* c);

int generarTablero(tLista *tablero,const tConfig *configuracion)
{
    tCasilla c;
    c.premio=0;
    c.vidaExtra=0;
    c.oasis=0;
    c.tormenta=0;
    crearLista(tablero);

    for(int i =0; i< configuracion->cantCasillas;i++)
    {
        c.inicio=0;
        c.salida=0;
        if(i==0)
            c.inicio=1;
        if(i==configuracion->cantCasillas-1)
            c.salida=1;
        if(insertarFinLis(tablero, &c, sizeof(tCasilla)) != 0)
            return 1;
    }
    distribuirPremios(tablero,configuracion->cantCasillas,configuracion->cantPremios);
    distribuirOasis(tablero,configuracion->cantCasillas,configuracion->cantOasis);
    distribuirTormentas(tablero,configuracion->cantCasillas,configuracion->cantTormentas);
    distribuirVidasExtra(tablero,configuracion->cantCasillas,configuracion->cantVidasMax);
    return 0;
}

tCasilla* obtenerCasillaLibreAleatoria(tLista* tablero,int cantCasillas)
{
    int pos;
    tCasilla* c;

    do
    {
        pos = rand() % cantCasillas;

        c = (tCasilla*)obtenerDatoPos(tablero, pos);

    } while(!casillaLibre(c));

    return c;
}


void mostrarCasilla(const void* dato)
{
    const tCasilla *c = (const tCasilla*)dato;

     printf("[");

    if(c->inicio)
        printf("I");

    if(c->salida)
        printf("S");

    if(c->premio)
        printf("P");

    if(c->vidaExtra)
        printf("V");

    if(c->oasis)
        printf("O");

    if(c->tormenta)
        printf("T");

    printf("] ");
}


int casillaLibre(const tCasilla* c)
{
    return (c->inicio==0 && c->salida==0 && c->premio==0 && c->vidaExtra==0 && c->oasis==0 && c->tormenta==0);
}

void distribuirPremios(tLista* tablero,int cantCasillas,int cantPremios)
{
    tCasilla* c;
    int i;
    for(i = 0; i < cantPremios; i++)
    {
        c = obtenerCasillaLibreAleatoria(tablero,cantCasillas);
        c->premio = 1;
    }
}

void distribuirOasis(tLista* tablero,int cantCasillas,int cantOasis)
{
    tCasilla* c;
    int i;
    for(i = 0; i < cantOasis; i++)
    {
        c = obtenerCasillaLibreAleatoria(tablero,cantCasillas);
        c->oasis = 1;
    }
}

void distribuirVidasExtra(tLista* tablero,int cantCasillas,int cantVidasExtra)
{
    tCasilla* c;
    int i;
    for(i = 0; i < cantVidasExtra; i++)
    {
        c = obtenerCasillaLibreAleatoria(tablero,cantCasillas);
        c->vidaExtra = 1;
    }
}

void distribuirTormentas(tLista* tablero, int cantCasillas, int cantTormentas)
{
    tCasilla* c;
    int i;
    for(i = 0; i < cantTormentas; i++)
    {
        c = obtenerCasillaLibreAleatoria(tablero,cantCasillas);
        c->tormenta = 1;
    }
}


void grabarCasilla(FILE* fp, const void* dato)
{
    const tCasilla* c = (const tCasilla*)dato;

    if(c->inicio)
        fprintf(fp, "I\n");
    else 
        if(c->salida)
            fprintf(fp, "S\n");
        else 
            if(c->premio)
                fprintf(fp, "P\n");
            else 
                if(c->vidaExtra)
                    fprintf(fp, "V\n");
                else 
                    if(c->oasis)
                        fprintf(fp, "O\n");
                    else 
                        if(c->tormenta)
                            fprintf(fp, "T\n");
                        else
                            fprintf(fp, ".\n");
}


int generarCaravana(const char* nombreArch,const tLista *tablero)
{
    FILE* fp;
    int pos=1;
    fp= fopen(nombreArch, "wt");
    if(!fp)
        return ERR_ARCH;

    recorrerListaArchivo(tablero, fp, grabarCasilla);

    fclose(fp);
    return TODO_OK;
}