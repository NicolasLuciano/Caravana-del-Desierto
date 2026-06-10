#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../headers/dado.h"
#include "../headers/constantesymacros.h"



int tirar_dado(int limite)
{
    if (limite < 1) return LIMITE_INVALIDO;
    return rand() % limite + 1;
}
