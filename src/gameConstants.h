#ifndef GAME_CONSTANTS_H                // Inicio del include guard para evitar inclusiones múltiples
#define GAME_CONSTANTS_H                // Defino macro que indica que el archivo ya fue incluido

#include <string>                      // Incluyo string para manejar texto
#include <cmath>                       // Incluyo cmath para usar constantes matemáticas como M_PI

using namespace std;                  // Para no escribir std:: antes de string o cout

// Defino el máximo de registros que se almacenarán en el historial de un jugador
const int MAX_REGISTROS = 100;

// Defino los niveles de dificultad para el juego Blackjack con número de cartas iniciales
const int NORMAL = 2;                 // Nivel Normal empieza con 2 cartas
const int MEDIO = 3;                  // Nivel Medio empieza con 3 cartas
const int DIFICIL = 4;                // Nivel Difícil empieza con 4 cartas

// Constantes relacionadas con la Ruleta
const int NUMEROS = 37;               // La ruleta tiene 37 números (0-36)

// Arreglo con los números de la ruleta, en el orden que aparecen en la rueda
const int numeros[NUMEROS] = {
    0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6,
    27, 13, 36, 11, 30, 8, 23, 10, 5, 24,
    16, 33, 1, 20, 14, 31, 9, 22, 18, 29,
    7, 28, 12, 35, 3, 26
};

// Arreglo con los colores correspondientes a cada número de la ruleta
// 'G' = Verde (para el 0), 'R' = Rojo, 'N' = Negro
const char colores[NUMEROS] = {
    'G', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'N', 'R', 'N', 'R', 'N', 'R'
};

// Códigos ANSI para colores en consola
// Estos códigos permiten cambiar el color del texto en terminales compatibles
const string rojo = "\033[31m";          // Código para texto rojo
const string negro = "\033[30m";         // Código para texto negro
const string verde = "\033[32m";         // Código para texto verde
const string fondo_blanco = "\033[47m";  // Código para fondo blanco
const string reset = "\033[0m";           // Código para resetear colores a los valores por defecto

// Constantes para la visualización de la ruleta en la consola (gráfico de la rueda)
struct Posicion { int x, y; };              // Estructura para almacenar coordenadas (x,y)
const int WIDTH = 90;                       // Ancho total del área visual
const int HEIGHT = 30;                      // Alto total del área visual
const int RADIO = 13;                       // Radio de la ruleta (tamaño)
const int CENTRO_X = WIDTH / 2;             // Coordenada X del centro de la ruleta
const int CENTRO_Y = HEIGHT / 2;            // Coordenada Y del centro de la ruleta

extern Posicion posiciones[NUMEROS];        // Declaración externa de las posiciones de cada número en la ruleta
                                            // Se define en otro archivo (por ejemplo jugador.h)

// Defino estructura para registrar una descripción del historial de acciones del jugador
struct Registro {
    string descripcion;                      // Texto que describe la acción o evento
};

#endif // GAME_CONSTANTS_H                // Fin del include guard
