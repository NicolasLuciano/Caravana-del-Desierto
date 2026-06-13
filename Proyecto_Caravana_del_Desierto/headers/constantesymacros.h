#ifndef CONSTANTESYMACROS_H_INCLUDED
#define CONSTANTESYMACROS_H_INCLUDED
///CONSTANTES DE PRIMITIVAS
#define TODO_OK 1
#define LISTA_ERROR -1
#define SIN_MEM -2
#define DUPLICADO_ERROR -3
#define COLA_ERROR -4
#define LIMITE_INVALIDO -5
#define NO_ENCONTRADO -6
#define LISTAS_IGUALES 1
///CONSTANTES DE JUEGO
#define DADO_BANDIDO 4
#define DADO_JUGADOR 6
#define VIVO 1
#define MUERTO 0
#define HAY_BANDIDO 2
#define SIN_BANDIDO -9
#define HAY_JUGADOR 3
#define SIN_JUGADOR -10
#define ADELANTE 'F'
#define ATRAS 'B'
#define HAY_COLISION 4
#define SIN_COLISION -11
#define PROTEGIDO 5
#define NO_PROTEGIDO -12
#define PIERDE_TURNO 6
#define NO_PIERDE_TURNO -13
#define MILISEGUNDOS 1000
///CONSTANTES DE MENU
#define MENSAJE_MENU "R - Ver el ranking de jugadores\nP - Jugar una nueva partida\nQ - Salir del juego\n-> "
#define OPCIONES_MENU "RPQ"
///CONSTANTES DE TABLERO
#define OASIS 'O'
#define VIDAEXTRA 'V'
#define TORMENTA 'T'
#define PREMIO 'P'
#define INICIO 'I'
#define SALIDA 'S'
#define BANDIDO 'B'
#define JUGADOR 'J'
#define VACIA '.'
#define MAX_OCUPACION 0.7
#define MIN_OCUPACION 0.2
#define TABLERO_INVALIDO -7
///CONSTANTES DE ARCHIVOS
#define ARCH_ERROR -8
#define NOMARCH "config.txt"
#define NOMBRE_DE_USUARIO_TAM 30
#define NOMBRE_TAM 30
#define APELLIDO_TAM 30
#define NOMARCH2 "caravana.txt"
#define NOMARCH3 "partidas.bin"

///MACROS
#define MIN(x,y)(x>y?y:x)

#endif // CONSTANTESYMACROS_H_INCLUDED
