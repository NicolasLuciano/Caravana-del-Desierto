#include "../headers/menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char menu (const char* msj,const char* opciones)
{
    char clave;
    system("cls");
    do
    {
        printf("%s",msj);
        scanf("%c",&clave);
        fflush(stdin);
        clave = toupper(clave);
        if(NULL == strchr(opciones,clave)){
            system("cls");
            printf("Opcion incorrecta, vuelva a intentar\n");
        }
    }while(NULL == strchr(opciones,clave));

    return clave;
}
