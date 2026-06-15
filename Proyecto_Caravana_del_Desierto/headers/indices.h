#ifndef INDICES_H_INCLUDED
#define INDICES_H_INCLUDED

#include "constantesymacros.h"

typedef struct
{
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
    char nombre[NOMBRE_TAM];
    char apellido[APELLIDO_TAM];
} tUsuario;

typedef struct
{
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
    int numRegistro;
}tIndice;

void identificarUsuario(tUsuario *usuario);

int compararUsuarios(const void *a, const void *b);
int validarUsuario(const char* usuario);
int validarNombreApellido(const char* texto);
int leerCadena(char * cadena, int(*validarCad)(const char *));
#endif // INDICES_H_INCLUDED
