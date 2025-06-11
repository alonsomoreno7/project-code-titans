#include <iostream>
using namespace std;

// Función para mostrar el menú principal con las opciones de juego
void mostrarMenu() {
    cout << "\nMENU PRINCIPAL\n";
    cout << "=============================================\n";
    cout << "1) Ruleta\n";
    cout << "2) Blackjack\n";
    cout << "3) Tragamonedas\n";
    cout << "4) Craps (Dados)\n";
    cout << "5) Salir del casino\n";
    cout << "=============================================\n";
}

int main() {
    // Variable para almacenar la opción seleccionada por el usuario
    int opcion;          
    // Variable para controlar el ciclo del menú 
    bool jugando = true; 

    while (jugando) {
        // Mostrar el menú principal
        mostrarMenu();    
        cout << "Elige una opción (1-5): ";
        // Guardar la opción del usuario
        cin >> opcion;   

        // Evaluar la opción elegida por el usuario
        switch (opcion) {
            case 1:
                // Mensaje para la opción Ruleta
                cout << "Ruleta - En proceso...\n";
                break;
            case 2:
                // Mensaje para la opción Blackjack
                cout << "Blackjack - En proceso...\n";
                break;
            case 3:
                // Mensaje para la opción Tragamonedas
                cout << "Tragamonedas - En proceso...\n";
                break;
            case 4:
                // Mensaje para la opción Craps (Dados)
                cout << "Craps (Dados) - En proceso...\n";
                break;
            case 5:
                // Opción para salir del casino
                cout << "Gracias por jugar. ¡Hasta luego!\n";
                jugando = false;  // Terminar el ciclo y salir del programa
                break;
            default:
                // Mensaje en caso de opción inválida
                cout << "Opción no válida. Intenta otra vez.\n";
        }
        cout << endl; // Línea en blanco para separar interaciones del menú
    }

    return 0; 
}
