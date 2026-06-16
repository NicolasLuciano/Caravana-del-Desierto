#ifndef INDICES_H_INCLUDED
#define INDICES_H_INCLUDED

#include "constantesymacros.h"
#include "arbol.h"
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

void identificarUsuario(tUsuario *usuario, tArbol *arbol);

int compararUsuarios(const void *a, const void *b);
int validarUsuario(const char* usuario);
int validarNombreApellido(const char* texto);
int leerCadena(char * cadena, int(*validarCad)(const char *));
void cargarArchivoOrdenadoEnIndiceBalanceadoEnvoltorio(tArbol *pa, FILE *fp);
void cargarArchivoOrdenadoEnIndiceBalanceado(tArbol *pa, FILE *fp, int, int);
void guardarIndice(void* dato,unsigned tam, void * ctx);
void actualizarArchivoIndice(tArbol* arbol);
void mostrarIndice(void* dato, unsigned tam, void *ctx);
#endif // INDICES_H_INCLUDED
