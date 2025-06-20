#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// se define el numero total de casillas que tendra la ruleta
const int NUMEROS = 37;

//  Coloca los numero que tendra la ruleta dentro de un arreglo
const int numeros[NUMEROS] = {
    0, 32, 15, 19, 4, 21, 2, 25, 17,
    34, 6, 27, 13, 36, 11, 30, 8, 
    23, 10, 5, 24, 16, 33, 1, 20, 14, 31,
    9, 22, 18, 29, 7, 28, 12, 35, 3, 26

};

//colores que corresponderian a cada numero dentro de la ruleta
const char colores[NUMEROS]={
'G','N','R','N','R','N','R','N','R','N','R',
    'N','R','N','R','N','R','N','R','N','R',
    'N','R','N','R','N','R','N','R','N','R',
    'N','R','N','R','N','R'
//el numero 0 es de color verde
};    

// codigos de escape ANSI para darle color
const string rojo = "\033[31m";
const string negro = "\033[30m";
const string verde = "\033[32m";
const string fondo_blanco = "\033[47m";
const string reset = "\033[0m";

//Funciones para limpiar consola y pausar
#ifdef _WIN32
void esperarMs (int ms) { Sleep (ms);}
void limpiarConsola(){ system ("cls");}
#else
void esperarMs(int ms){ usleep(ms * 1000);}
void limpiarConsola(){ cout << "\033[2J\033[H"; }
#endif

// esructura que representa la posicion (X y Y) de cada numero 
struct Posicion{int x, y; };

//Definir dimensiones y centro de la canvas para dibujar la ruleta

const int WIDTH = 90;
const int HEIGHT = 30;
const int RADIO = 13;
const int CENTRO_X = WIDTH / 2;
const int CENTRO_Y = HEIGHT / 2;

//arreglo para guardar posiciones calculadas
Posicion posiciones[NUMEROS];


//Calcular las posiciones den circulo para dibujar la ruleta 
void calcularPosiciones() {
    for (int i = 0; i < NUMEROS; i++) {
        double angulo = (2 * M_PI * i / NUMEROS) - M_PI / 2;
        posiciones[i].x = CENTRO_X + int(RADIO * cos(angulo) * 1.9); 
        posiciones[i].y = CENTRO_Y + int(RADIO * sin(angulo));
    }
}

