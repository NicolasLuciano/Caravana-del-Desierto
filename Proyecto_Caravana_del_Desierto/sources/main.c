#include "../headers/constantesymacros.h"
#include "../headers/menu.h"
#include "../headers/juego.h"
#include "../headers/jugador.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    tUsuario usuarioActual;
    char opcion;

    //identificarUsuario(&usuarioActual);
    printf("Ingrese nombre de usuario\n");
    scanf("%s", usuarioActual.nombreDeUsuario);
    do
    {
        switch(opcion = menu(MENSAJE_MENU, OPCIONES_MENU))
        {
        case 'R':
            printf("Cargando Ranking...\n");
            verRanking();
            break;

        case 'P':
            if(inicializarJuego(usuarioActual.nombreDeUsuario) != TODO_OK)
                printf("No se pudo iniciar la partida. Volviendo al menu...\n");
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
