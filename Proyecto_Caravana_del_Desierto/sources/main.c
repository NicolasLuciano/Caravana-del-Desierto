#include "../headers/lista.h"
#include "../headers/archivos.h"
#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include "../headers/bandido.h"
#define NOMARCH "config.txt"

int main()
{
    tLista tablero;
    tBandido * bandidos;
    tConfig configuracion;

    crearLista(&tablero);
    cargarConfig(NOMARCH,&configuracion);
    bandidos=crearBandidos(configuracion.cantBandidos);
    if( bandidos== NULL)
        perror("No hay memoria suficiente para crear bandidos");
    generarTablero(&tablero,configuracion,bandidos); //PARA MI NO HACE FALTA MANDARLO COMO PUNTERO
    mostrarLista(&tablero,mostrarCasilla);

    return 0;
}
