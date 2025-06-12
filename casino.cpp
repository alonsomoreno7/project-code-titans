#include <iostream> 
#include <string>
#include "jugador.h"  // Aquí incluyo la definición de la clase Jugador y funciones que usaré

using namespace std;

// Esta función solo muestra el menú con las opciones para que el jugador elija qué hacer
void mostrarMenu() {
    cout << "\nMenu Principal - Casino Virtual\n";
    cout << "=============================================\n";
    cout << "1) Depositar dinero\n";
    cout << "2) Retirar dinero\n";
    cout << "3) Ruleta\n";
    cout << "4) Blackjack\n";
    cout << "5) Tragamonedas\n";
    cout << "6) Craps (Dados)\n";
    cout << "7) Salir del casino\n";
    cout << "=============================================\n";
}

int main() {
    Jugador jugador;  // Creo un jugador, que tendrá nombre y dinero
    jugador.dinero = 0;  // Empiezo con saldo cero para obligar a depositar primero

    // Pido el nombre del jugador, verificando que solo tenga letras y espacios
    do {
        cout << "Ingresa tu nombre para comenzar: ";
        getline(cin, jugador.nombre);
        // Si el nombre tiene caracteres inválidos, aviso y pido de nuevo
        if (!nombreValido(jugador.nombre)) {
            cout << "Nombre inválido. Solo se permiten letras y espacios. Intenta de nuevo.\n";
        }
    } while (!nombreValido(jugador.nombre));

    // Saludo inicial con el saldo (que es cero, recordatorio para depositar)
    cout << "¡Hola, " << jugador.nombre << "! Tu saldo inicial es de $" << jugador.dinero << ". Deposita dinero para empezar a jugar.\n";

    bool jugando = true;  // Esta variable controla si seguimos en el programa o salimos
    int opcion;  // Aquí guardaré la opción que el usuario elija en el menú

    // Empiezo el ciclo principal donde el jugador elige qué hacer
    while (jugando) {
        mostrarMenu();  // Muestro el menú para que el jugador vea las opciones
        cout << "Dinero actual: $" << jugador.dinero << endl;
        cout << "Elige una opción (1-7): ";
        cin >> opcion;

        // Esto es para evitar que el programa crashee si el usuario mete letras u otra cosa rara
        if (cin.fail()) {
            cin.clear();  // Limpio el error
            cin.ignore(1000, '\n');  // Ignoro la entrada inválida que quedó en el buffer
            cout << "Entrada inválida. Ingresa un número del 1 al 7.\n";
            continue;  // Vuelvo a pedir la opción sin hacer nada más
        }

        // Aquí manejo cada opción del menú según lo que el jugador haya elegido
        switch (opcion) {
            case 1: {  // Opción para depositar dinero
                int cantidad;
                cout << "¿Cuánto dinero deseas depositar? $";
                cin >> cantidad;
                if (cantidad > 0) {
                    jugador.depositar(cantidad);  // Llamo el método que suma el dinero y guarda el registro
                } else {
                    cout << "Cantidad inválida para depositar.\n";  // Si la cantidad es cero o negativa, aviso
                }
                break;
            }
            case 2: {  // Opción para retirar dinero
                int cantidad;
                cout << "¿Cuánto dinero deseas retirar? $";
                cin >> cantidad;
                if (cantidad > 0) {
                    if (!jugador.retirar(cantidad)) {  // Intento retirar; si no es posible, aviso
                        cout << "No se pudo realizar el retiro.\n";
                    }
                    // No llamo guardarRegistro aquí porque retiro() ya lo hace internamente
                } else {
                    cout << "Cantidad inválida para retirar.\n";  // Si la cantidad es 0 o negativa, aviso
                }
                break;
            }
            case 3:  // Ruleta (aquí solo muestro un mensaje, falta la lógica del juego)
                if (jugador.dinero <= 0) {
                    cout << "No tienes saldo suficiente. Deposita dinero para jugar.\n";
                    break;
                }
                cout << "Juego en proceso...\n";
                // Aquí debería ir la lógica para jugar ruleta y modificar el saldo
                break;
            case 4:  // Blackjack 
                if (jugador.dinero <= 0) {
                    cout << "No tienes saldo suficiente. Deposita dinero para jugar.\n";
                    break;
                }
                cout << "Juego en proceso...\n";
                // Aquí iría la lógica para el blackjack
                break;
            case 5:  // Tragamonedas
                if (jugador.dinero <= 0) {
                    cout << "No tienes saldo suficiente. Deposita dinero para jugar.\n";
                    break;
                }
                cout << "Juego en proceso...\n";
                // Falta lógica para tragamonedas
                break;
            case 6:  // Craps (Dados)
                if (jugador.dinero <= 0) {
                    cout << "No tienes saldo suficiente. Deposita dinero para jugar.\n";
                    break;
                }
                cout << "Juego en proceso...\n";
                // Falta lógica para craps
                break;
            case 7:  // Salir del casino
                cout << "Gracias por jugar. ¡Hasta luego!\n";
                jugando = false;  // Cambio la variable para terminar el ciclo y salir del programa
                break;
            default:  // Si el usuario mete un número fuera del rango 1-7
                cout << "Opción no válida. Intenta otra vez.\n";
        }

        cin.ignore();  // Limpio el buffer para evitar que getline falle en próximas entradas
        cout << endl;  // Solo para que se vea bonito y ordenado en la consola
    }

    return 0;  // Termina el programa
}
