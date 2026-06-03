#include "../headers/archivos.h"
#include "../headers/lista.h"
#include "../headers/constantesymacros.h"

int cargarConfig(const char* nombreArch, tConfig* configuracion)
{
    FILE *fp;
    fp=fopen(nombreArch, "rt");
    if(!fp)
        return ARCH_ERROR;

    fscanf(fp, "cantidad_posiciones: %d\n", &configuracion->cantCasillas);
    fscanf(fp, "vidas_inicio: %d\n", &configuracion->vidasIniciales);
    fscanf(fp, "maximo_bandidos: %d\n", &configuracion->cantBandidos);
    fscanf(fp, "maximo_premios: %d\n", &configuracion->cantPremios);
    fscanf(fp, "maximo_vidas_extra: %d\n", &configuracion->cantVidasMax);
    fscanf(fp, "maximo_oasis: %d\n", &configuracion->cantOasis);
    fscanf(fp, "maximo_tormentas: %d", &configuracion->cantTormentas);


    fclose(fp);
    return TODO_OK;
}

int generarCaravana(const char* nombreArch,const tLista *tablero)
{
    FILE* fp;
    fp= fopen(nombreArch, "wt");
    if(!fp)
        return ARCH_ERROR;


    fclose(fp);
    return TODO_OK;
}
