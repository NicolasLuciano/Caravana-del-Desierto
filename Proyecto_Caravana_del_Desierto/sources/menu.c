#include "../headers/menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char menu(const char* msj, const char* opciones)
{
    char clave;
    do
    {
        system("cls");
        printf("%s", msj);
        scanf("%c", &clave);
        fflush(stdin);
        clave = toupper(clave);
        if(NULL == strchr(opciones, clave))
            printf("Opcion incorrecta, vuelva a intentar\n");
    } while(NULL == strchr(opciones, clave));
    return clave;
}
