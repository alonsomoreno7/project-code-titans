#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>

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
const string fondo blanco = "\033[47m";
const string reset = "\033[0m";

