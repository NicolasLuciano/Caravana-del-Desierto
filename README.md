# Caravana Del Desierto

Este proyecto consiste en la implementación en C del juego Caravana del Desierto, desarrollado para la materia Algoritmos y Estructuras de Datos.

La idea del juego es simple: el jugador tiene que atravesar una ruta desértica desde el punto inicial hasta la salida, gestionando sus movimientos y evitando perder todas sus vidas en el camino.

# ¿Cómo se juega?

Al iniciar el programa se solicita el nombre del jugador.
Si ya existe, se reutiliza.
Si no, se crea un nuevo registro.
En cada turno:
Se lanza un dado (valor entre 1 y 6).
El jugador decide si avanzar o retroceder esa cantidad de posiciones.
Se ejecuta el movimiento y se aplica el efecto del casillero donde cae.
Durante el recorrido pueden ocurrir distintas cosas:
Premios (P): suman puntos.
Vidas extra (V): aumentan la cantidad de vidas.
Oasis (O): otorgan protección para el siguiente turno.
Tormentas (T): hacen perder un turno.
Bandidos (B): si te interceptan, perdés una vida y volvés al inicio.
El tablero es circular, por lo que se puede avanzar o retroceder sin límites fijos.
La partida termina cuando:
El jugador llega a la salida, o
Se queda sin vidas.
# ¿Qué hace el código?

El programa no es solo el juego, sino que también aplica varias estructuras de datos vistas en la materia:

Lista doblemente enlazada circular
Se utiliza para representar el tablero. Cada nodo es una posición de la ruta.
Cola (FIFO)
Se usa para gestionar los movimientos del jugador y de los bandidos. Primero se encolan y luego se ejecutan.
Árbol binario de búsqueda (ABB)
Funciona como índice para acceder de forma eficiente a los jugadores guardados en archivo.
Archivos (texto y binario)
config.txt: define cómo se genera el tablero
caravana.txt: guarda el tablero generado
jugadores.dat y partidas.dat: almacenan la información persistente

# Funcionamiento general

Se leen los parámetros desde config.txt.
Se genera el tablero dinámicamente.
Se inicializa la partida.
Se ejecuta un loop de turnos:
jugador
bandidos
Se registran los movimientos realizados.
Al finalizar, se guarda la partida y se actualiza el ranking.

# Consideraciones

Cada partida genera un tablero nuevo.
El diseño busca separar lógica, estructuras y persistencia.
Las funciones están pensadas para ser lo más genéricas posible.
