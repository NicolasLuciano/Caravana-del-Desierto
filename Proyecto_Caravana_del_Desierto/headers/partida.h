#ifndef PARTIDA_H_INCLUDED
#define PARTIDA_H_INCLUDED

typedef struct
{
    int idPartida;
    char nombreDeUsuario[NOMBRE_DE_USUARIO_TAM];
    unsigned puntos;
    unsigned movimientos;
    char resultado;
} tPartida;

#endif // PARTIDA_H_INCLUDED
