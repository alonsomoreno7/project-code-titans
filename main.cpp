#include <iostream>
#include <ctime>   // Para time()
#include <cstdlib> // Para srand()

#include "./src/mainMenu.h" // Para las funciones del menú principal

#ifdef _WIN32
#include <windows.h> // Para SetConsoleOutputCP en Windows
#endif

int main() {
    // Si estamos en Windows, configuramos la consola para UTF-8
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif

    // Inicializo el generador de números aleatorios con la semilla del tiempo actual
    srand(static_cast<unsigned int>(time(nullptr)));

    // Llamo al menú principal donde el usuario puede seleccionar el modo de juego
    menuModoJuego();

    return 0;
}
