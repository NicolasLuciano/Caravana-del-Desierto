#include "../headers/menu.h"

char menu (const char* msj,const char* opciones)
{
    char clave;
    printf("%s",msj);
    fflush(stdin);
    scanf("%c",&clave);
    clave = toupper (clave);
    while(NULL == strchr(opciones,clave))
    {
        printf("%s",msj);
        fflush(stdin);
        scanf("%c",&clave);
        clave = toupper (clave);
    }
    return clave;
}
