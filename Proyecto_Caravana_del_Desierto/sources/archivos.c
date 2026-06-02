#include "../headers/archivos.h"

int cargarConfig(const char* nombreArch, tConfig* configuracion)
{
    FILE *fp;
    fp=fopen(nombreArch, "rt");
    if(!fp)
        return ERR_ARCH;

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