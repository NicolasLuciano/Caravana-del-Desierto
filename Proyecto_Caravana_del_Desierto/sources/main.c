#include "../headers/constantesymacros.h"
#include "../headers/menu.h"
#include "../headers/juego.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char opcion;
    do
    {
        switch(opcion = menu(MENSAJE_MENU, OPCIONES_MENU))
        {
        case 'R':
            printf("Cargando Ranking...\n");
            break;
        case 'P':
            inicializarJuego();
            break;
        case 'Q':
            printf("Saliendo...\n");
            break;
        }
    }
    while('Q' != opcion );
    return TODO_OK;
}
