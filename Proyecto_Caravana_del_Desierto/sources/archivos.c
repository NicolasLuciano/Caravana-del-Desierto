#include "../headers/archivos.h"
#include "../headers/lista.h"
#include "../headers/constantesymacros.h"
#include "../headers/indices.h"

int cargarConfig(const char* nombreArchivo, tConfig* configuracion)
{
    FILE *pf;
    pf=fopen(nombreArchivo, "rt");
    if(!pf)
    {
        perror(nombreArchivo);
        return ARCH_ERROR;
    }

    fscanf(pf, "cantidad_posiciones: %d\n", &configuracion->cantCasillas);
    fscanf(pf, "vidas_inicio: %d\n", &configuracion->vidasIniciales);
    fscanf(pf, "maximo_bandidos: %d\n", &configuracion->cantBandidos);
    fscanf(pf, "maximo_premios: %d\n", &configuracion->cantPremios);
    fscanf(pf, "maximo_vidas_extra: %d\n", &configuracion->cantVidasExtra);
    fscanf(pf, "maximo_oasis: %d\n", &configuracion->cantOasis);
    fscanf(pf, "maximo_tormentas: %d", &configuracion->cantTormentas);


    fclose(pf);
    return TODO_OK;
}

int guardarPartida(tPartida partida, const char * nombreArchivo)
{
    FILE * pf;

    pf=fopen(nombreArchivo,"ab");
    if(!pf)
    {
        perror(nombreArchivo);
        return ARCH_ERROR;
    }

    fwrite(&partida, sizeof(tPartida), 1, pf);
    fclose(pf);

    return TODO_OK;
}

int guardarTablero(const tLista* tablero, const char* nombreArchivo)
{
    FILE* pf = fopen(nombreArchivo, "wt");
    if(!pf)
    {
        perror(nombreArchivo);
        return ARCH_ERROR;
    }
    recorrerListaArchivo(tablero, pf, escribirCasilla);
    fclose(pf);

    return TODO_OK;
}

void escribirCasilla(FILE* fp, const void* dato)
{
    tCasilla casilla = *(tCasilla*)dato;
    char linea[10];

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
            fprintf(fp,"%02d: [%s]\n", casilla.numCasilla, linea);
        else
            fprintf(fp,"%02d: %s\n", casilla.numCasilla, linea);
    }
    else
        fprintf(fp,"%02d: %c\n", casilla.numCasilla, casilla.tipo);
}

int cargarIndices(tArbol *arbol,char *nombreArchivo)
{
    FILE *fp;
    tIndice indice;
    fp = fopen(nombreArchivo,"rb");
    if(!fp)
    {
        perror(nombreArchivo);
        return ARCH_ERROR;
    }
    while(fread(&indice,sizeof(indice),1,fp)==1)
        insertarArbol(arbol,&indice,sizeof(indice),compararUsuarios);
    fclose(fp);
    return TODO_OK;
}


int cargarRanking(tRanking ** vecRanking, char * nombreArchivo,unsigned capacidad, unsigned * cantJugadores, tArbol * arbol)
{
    FILE * pfPartida,*pfJugadores;
    tRanking * vecAux;
    tPartida partida;
    tUsuario usuario;
    int pos;



    (*cantJugadores)=0;
    cargarVectorInOrden(arbol,**vecRanking,sizeof(tRanking),capacidad);


    pfPartida=fopen(nombreArchivo_Par,"rb");
    if(!pfPartida)
    {
        perror(nombreArchivo);
        return ARCH_ERROR;
    }

    while(fread(&partida,sizeof(tPartida),1,pf)==1)
    {
        pos=buscarJugador(partida.nombreDeUsuario,*vecRanking,*cantJugadores);
        if(pos!=NO_ENCONTRADO)
            ((*vecRanking)+pos)->puntos+=partida.puntos;
        else
        {
            if((*cantJugadores)==capacidad)
            {
                capacidad *=2;
                vecAux=realloc((*vecRanking), sizeof(tRanking)*capacidad);
                if(vecAux == NULL)
                {
                    fclose(pf);
                    return SIN_MEM;
                }
                (*vecRanking)=vecAux;
            }

            strcpy(((*vecRanking)+(*cantJugadores))->nombreDeUsuario,partida.nombreDeUsuario);
            ((*vecRanking)+ (*cantJugadores))->puntos=partida.puntos;
            (*cantJugadores)++;
        }
    }
    fclose(pf);
    return TODO_OK;
}





