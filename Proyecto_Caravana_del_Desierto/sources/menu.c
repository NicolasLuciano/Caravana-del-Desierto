#include "../headers/menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/jugador.h"

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
    }
    while(NULL == strchr(opciones, clave));
    return clave;
}
void identificarUsuario(tUsuario *usuario)
{
    char nombreUsuario[NOMBRE_DE_USUARIO_TAM];

    printf("Ingrese nombre de usuario: ");
    scanf("%s", nombreUsuario);

}
//void identificarUsuario(tUsuario* usuario)
//{
//    char nombreUsuario[NOMBRE_DE_USUARIO_TAM];
//
//    printf("Ingrese nombre de usuario: ");
//    scanf("%s", nombreUsuario);
//
//    buscarIndice(arbol, "luciano");
//    //devuelve numRegistro de luciano
//
//    if(existe)
//    {
//        pf = fopen("usuarios.dat","rb");
//        fseek(pf,numRegistro * sizeof(tUsuario),SEEK_SET);
//
//        printf("Usuario encontrado:\n");
//        printf("%s %s\n", usuario->nombre, usuario->apellido);
//
//        printf("Es usted? (S/N): ");
//    }
//    else
//    {
//        printf("Usuario inexistente.\n");
//        printf("Ingrese nombre: ");
//        printf("Ingrese apellido: ");
//
//        fseek(pf,0,SEEK_END);
//        fwrite(&nuevo,sizeof(tUsuario),1,pf);
//        nroRegistro = ftell(pf)/sizeof(tUsuario)-1;
//
//    }
//}

