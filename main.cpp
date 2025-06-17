// Incluyo el archivo jugador.h donde está toda la lógica 
#include "./src/jugador.h"


int main() {
    SetConsoleOutputCP(CP_UTF8);
    // Esta es la única función que llamo desde el main, porque en jugador.h ya controlo todo el flujo del casino.
    menuInicio();
    return 0;
}

