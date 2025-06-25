#ifndef MAIN_MENU_H  
#define MAIN_MENU_H  

#include <iostream>  // Incluyo esta librería para poder mostrar mensajes en pantalla
#include <string>    // Incluyo esta librería para trabajar con cadenas de texto
#include <limits>    // Incluyo esto para poder limpiar el buffer y validar entradas
#include <cstdlib>   // Incluyo esto para funciones como srand
#include <ctime>     // Incluyo esto para trabajar con time() al usar srand

#include "jugador.h"         // Aquí incluyo el archivo que contiene la estructura y métodos del jugador
#include "userManager.h"     // Aquí incluyo las funciones para manejo de usuarios: login, registro, etc.
#include "rouletteGame.h"    // Aquí incluyo el juego de la ruleta
#include "blackjackGame.h"   // Aquí incluyo el juego del blackjack
#include "crapsGame.h"       // Aquí incluyo el juego de craps (dados)
#include "hilo.h"            // Aquí incluyo el juego Hi-Lo
#include "multijugador.h"    // Aquí incluyo el modo multijugador
#include "slotMachineGame.h" // Aquí incluyo el juego de tragamonedas
#include "utils.h"           // Aquí incluyo el limpiarConsola

using namespace std; // Uso el espacio de nombres estándar para evitar escribir std:: a cada rato

// Esta función muestra las opciones disponibles en el menú principal del casino
inline void mostrarMenu() {
    limpiarConsola(); // Uso la función que ya tengo para limpiar pantalla antes de mostrar menú
    cout << "\n====================================";
    cout << "\nMenu Principal - Casino Virtual\n";
    cout << "1) Depositar dinero\n";
    cout << "2) Retirar dinero\n";
    cout << "3) Ruleta\n";
    cout << "4) Blackjack\n";
    cout << "5) Tragamonedas\n";
    cout << "6) Craps (Dados)\n";
    cout << "7) Hi-Lo\n";
    cout << "8) Mostrar historial\n";
    cout << "9) Mostrar estadísticas \n";
    cout << "10) Salir\n";
    cout << "====================================\n";
}

// Esta función arranca el juego una vez que el usuario ha iniciado sesión correctamente
inline void iniciar(const string& nombreUsuario) {
    Jugador jugador; // Creo un jugador
    jugador.nombre = nombreUsuario; // Le asigno el nombre recibido
    jugador.dinero = cargarSaldo(nombreUsuario); // Cargo el saldo del jugador desde archivo
    jugador.cargarEstadisticasJugador(); // Cargo las estadísticas guardadas del jugador

    cout << "Hola, " << jugador.nombre << "! Saldo actual: $" << jugador.dinero << "\n";

    int opcion; // Variable para almacenar la opción del menú
    bool jugando = true; // Bandera para mantener el bucle activo

    while (jugando) {
        mostrarMenu(); // Muestro el menú en pantalla
        cout << "Dinero actual: $" << jugador.dinero << "\n";
        cout << "Elige una opción: ";
        cin >> opcion; // Leo la opción del usuario

        if (cin.fail()) { // Verifico si hubo un error en la entrada
            cin.clear(); // Limpio el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpio el buffer
            cout << "Entrada inválida.\n";
            continue; // Regreso al inicio del bucle
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpio cualquier carácter sobrante

        switch (opcion) { // Evaluo la opción del usuario
            case 1: {
                int cantidad;
                cout << "¿Cuánto deseas depositar? $";
                cin >> cantidad;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                jugador.depositar(cantidad); // Llamo al método para depositar dinero
                break;
            }
            case 2: {
                int cantidad;
                cout << "¿Cuánto deseas retirar? $";
                cin >> cantidad;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                jugador.retirar(cantidad); // Llamo al método para retirar dinero
                break;
            }
            case 3:
                if (jugador.dinero <= 0)
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                else
                    jugarRuleta(jugador); // Juego de ruleta
                break;
            case 4:
                if (jugador.dinero <= 0) {
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                } else {
                    jugarBlackjack(jugador); // Juego de blackjack
                }
                break;
            case 5:
                if (jugador.dinero <= 0)
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                else
                    jugarTragamonedas(jugador); // Juego de tragamonedas
                break;
            case 6:
                if (jugador.dinero <= 0)
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                else
                    jugarCraps(jugador); // Juego de dados (Craps)
                break;
            case 7:
                if (jugador.dinero <= 0)
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                else
                    jugarHilo(jugador); // Juego de Hi-Lo
                break;
            case 8:
                jugador.mostrarHistorial(); // Muestro el historial de movimientos
                break;
            case 9:
                jugador.mostrarEstadisticas(); // Muestro estadísticas del jugador
                break;
            case 10:
                cout << "Gracias por jugar. ¡Hasta luego!\n";
                jugando = false; // Salgo del bucle y del juego
                break;
            default:
                cout << "Opción no válida.\n"; // Capturo cualquier opción inválida
        }
        cout << endl; // Hago un salto de línea después de cada ciclo
    }
}

// Esta función maneja el menú inicial donde el usuario elige si quiere iniciar sesión o registrarse
inline void menuInicio() {
    string nombre;
    bool sesion = false;

    while (!sesion) {
        limpiarConsola(); // Uso la función que ya tengo para limpiar pantalla antes de mostrar menú
        cout << "\n===== MENÚ DE INICIO =====\n";
        cout << "1) Iniciar sesión\n";
        cout << "2) Registrarse\n";
        cout << "3) Recuperar contraseña\n";
        cout << "4) Eliminar usuario\n";
        cout << "5) Salir\n";
        cout << "==========================\n";
        cout << "Opción: ";
        int opcion;
        cin >> opcion;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Por favor, ingresa un número.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                sesion = iniciarSesion(nombre); // Intento iniciar sesión
                break;
            case 2:
                registrarUsuario(); // Registro un nuevo usuario
                break;
            case 3:
                recuperarContrasena(); // Llamo a recuperación de contraseña
                break;
            case 4:
                eliminarUsuario(); // Elimino un usuario
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                return; // Salgo de la función
            default:
                cout << "Opción inválida. Intenta nuevamente.\n";
        }
    }

    iniciar(nombre); // Si logré iniciar sesión, empiezo el juego
}

// Esta función me permite elegir si quiero jugar solo o en modo multijugador local
inline void menuModoJuego() {
    int opcion;
    limpiarConsola(); // Uso la función que ya tengo para limpiar pantalla antes de mostrar menú
    while (true) {
        cout << "\n=========== MODO DE JUEGO ===========\n";
        cout << "1) Jugar solo\n";
        cout << "2) Multijugador local\n";
        cout << "3) Salir del juego\n";
        cout << "=====================================\n";
        cout << "Escoge una opción: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Ingresa un número del 1 al 3.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                menuInicio(); // Llamo al menú de inicio para un solo jugador
                return;
            case 2:
                modoMultijugador(); // Llamo al modo multijugador local
                return;
            case 3:
                cout << "¡Gracias por jugar! Hasta pronto.\n";
                return;
            default:
                cout << "Opción inválida. Intenta de nuevo.\n";
        }
    }
}

#endif // MAIN_MENU_H 