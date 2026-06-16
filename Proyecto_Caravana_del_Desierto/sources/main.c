#include "../headers/constantesymacros.h"
#include "../headers/menu.h"
#include "../headers/juego.h"
#include "../headers/indices.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    tUsuario usuarioActual;
    char opcion;
    tArbol arbol;
    crearArbol(&arbol);
    identificarUsuario(&usuarioActual, &arbol);

    do
    {
        switch(opcion = menu(MENSAJE_MENU, OPCIONES_MENU))
        {
        case 'R':
            if(verRanking() != TODO_OK)
                printf("---No se pudo cargar el ranking. Volviendo al menu...---\n");
            system("pause");
            break;

        case 'P':
            if(inicializarJuego(usuarioActual.nombreDeUsuario) != TODO_OK)
                printf("---No se pudo iniciar la partida. Volviendo al menu...---\n");
            system("pause");
            break;

        case 'Q':
            printf("Saliendo...\n");
            break;
        }
    }
    while(opcion != 'Q');

    return TODO_OK;
}
