#ifndef CONSTANTESYMACROS_H_INCLUDED
#define CONSTANTESYMACROS_H_INCLUDED
///CONSTANTES DE PRIMITIVAS
#define TODO_OK 1
#define LISTA_ERROR -1
#define SIN_MEM -2
#define DUPLICADO_ERROR -3
#define COLA_ERROR -4
#define LIMITE_INVALIDO -6
///CONSTANTES DE JUEGO
#define DADO_BANDIDO 4
#define VIVO 1
#define MUERTO 0
#define SALIDA 'S'
#define ADELANTE 1
#define ATRAS -1
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
#define VACIA '.'
///CONSTANTES DE ARCHIVOS
#define ARCH_ERROR -5
#define NOMARCH "config.txt"
///MACROS
#define MIN(x,y)(x>y?y:x)

#endif // CONSTANTESYMACROS_H_INCLUDED
