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

void empezarPartida(tLista * tablero, tJugador * jugador, tBandido *bandidos, unsigned cantCasillas);

#endif // PARTIDA_H_INCLUDED
