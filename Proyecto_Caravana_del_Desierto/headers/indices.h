#ifndef INDICES_H_INCLUDED
#define INDICES_H_INCLUDED

#include "constantesymacros.h"

typedef struct
{
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
} tClave;

typedef struct
{
    unsigned indice;
    tClave clave;
} tIndice;

#endif // INDICES_H_INCLUDED


void juego(tListaD* jugadorEnTablero, ...)
{
    void* ini = tablero;
    moveratras(tablero);
    void* fin = tablero;
    moveradelante(tablero);

    while(vidas > 0)
    {
        for(i=0; i<dato; i++)
        {
            moverHaciaAdelnta(tablero);
            if(fin == tablero)
                for(j=i; j<dado; j++)
                {
                    moveratras(tablero);
                }
        }
        i=j;
    }
}
