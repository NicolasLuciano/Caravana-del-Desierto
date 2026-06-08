#include "../headers/lista.h"
#include "../headers/archivos.h"
#include "../headers/tablero.h"
#include "../headers/constantesymacros.h"
#include "../headers/bandido.h"
#include "../headers/menu.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main()
{
    tLista tablero;
    tBandido * bandidos;
    tConfig configuracion;
    char opcion;

    crearLista(&tablero);
    cargarConfig(NOMARCH,&configuracion);
    bandidos=crearBandidos(configuracion.cantBandidos);
    if( bandidos== NULL)
        perror("No hay memoria suficiente para crear bandidos");
    generarTablero(&tablero,configuracion,bandidos); //PARA MI NO HACE FALTA MANDARLO COMO PUNTERO
    printf("Generando tablero...\n");
    mostrarTablero(&tablero,bandidos,configuracion.cantBandidos);
    printf("Pulsa cualquier tecla para borrar el tablero\n");
    system("pause");

    switch(opcion=menu(MENSAJE_MENU,OPCIONES_MENU))
    {
        case 'R':
            printf("Cargando Ranking...\n");
            break;
        case 'P':
            printf("Creando una nueva partida...\n");
            break;
        case 'Q':
            printf("Saliendo...\n");
            break;
    }

    return TODO_OK;
}
