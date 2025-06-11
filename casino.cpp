#include <iostream>
#include <string>
#include "jugador.h"  // Incluimos el header donde definimos al jugador y funciones útiles

using namespace std;

// Función que muestra el menú principal con las opciones disponibles
void mostrarMenu() {
    cout << "\nMenu Principal \n";
    cout << "=============================================\n";
    cout << "1) Ruleta\n";
    cout << "2) Blackjack\n";
    cout << "3) Tragamonedas\n";
    cout << "4) Craps (Dados)\n";
    cout << "5) Salir del casino\n";
    cout << "=============================================\n";
}

int main() {
    Jugador jugador;              // Creamos una variable de tipo Jugador para almacenar datos del usuario
    jugador.dinero = 1000;        // Inicializamos el dinero con una cantidad fija para empezar a jugar

    // Pedimos al usuario que ingrese su nombre y validamos que sea correcto
    do {
        cout << "Ingresa tu nombre para comenzar: ";
        getline(cin, jugador.nombre);  // Usamos getline para permitir nombres con espacios
        if (!nombreValido(jugador.nombre)) {  // Validamos que el nombre solo tenga letras y espacios
            cout << "Nombre inválido. Solo se permiten letras y espacios. Intenta de nuevo.\n";
        }
    } while (!nombreValido(jugador.nombre));  // Repetimos hasta que el nombre sea válido

    // Mensaje de bienvenida personalizado con el nombre y el dinero inicial
    cout << "¡Bienvenido, " << jugador.nombre << "! Tienes $" << jugador.dinero << " para jugar.\n";

    bool jugando = true;   // Variable para controlar el ciclo principal del menú
    int opcion;            // Variable donde almacenaremos la opción que elija el usuario

    // Ciclo principal del programa, se repite mientras el usuario no decida salir
    while (jugando) {
        mostrarMenu();  // Mostramos el menú de opciones
        cout << "Dinero actual: $" << jugador.dinero << endl;  // Mostramos cuánto dinero tiene el jugador
        cout << "Elige una opción (1-5): ";
        cin >> opcion;   // Leemos la opción elegida

        // Comprobamos si la entrada es válida (es un número)
        if (cin.fail()) {
            cin.clear();               // Limpiamos el error de entrada
            cin.ignore(1000, '\n');    // Ignoramos el resto del input
            cout << "Entrada inválida. Ingresa un número del 1 al 5.\n";
            continue;                  // Volvemos al inicio del ciclo para pedir otra opción
        }

        // Procesamos la opción seleccionada con un switch
        switch (opcion) {
            case 1:
                cout << "Ruleta - En proceso...\n";  // Mensaje provisional para la opción 1
                break;
            case 2:
                cout << "Blackjack - En proceso...\n";  // Mensaje provisional para la opción 2
                break;
            case 3:
                cout << "Tragamonedas - En proceso...\n";  // Mensaje provisional para la opción 3
                break;
            case 4:
                cout << "Craps (Dados) - En proceso...\n";  // Mensaje provisional para la opción 4
                break;
            case 5:
                cout << "Gracias por jugar. ¡Hasta luego!\n";  // Mensaje al salir
                jugando = false;  // Cambiamos la variable para terminar el ciclo y salir del programa
                break;
            default:
                // Si la opción no está entre 1 y 5, avisamos al usuario
                cout << "Opción no válida. Intenta otra vez.\n";
        }

        cin.ignore();  // Limpiamos el buffer para evitar problemas con getline en próximas entradas
        cout << endl;  // Línea en blanco para que la salida se vea más limpia y ordenada
    }

    return 0;  // Fin del programa
}
