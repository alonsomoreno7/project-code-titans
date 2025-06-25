#ifndef HILO_GAME_H                 // Inicio del include guard para evitar inclusiones múltiples
#define HILO_GAME_H                 // Macro para indicar que este archivo ya fue incluido

#include <iostream>                 // Para entrada/salida estándar (cout, cin)
#include <string>                   // Para manejar cadenas de texto
#include <algorithm>                // Para funciones útiles como std::transform
#include <ctime>                    // Para funciones relacionadas con tiempo (semilla aleatoria)
#include <cstdlib>                  // Para funciones rand(), system()
#include <fstream>                  // Para manejo de archivos (ifstream, ofstream)
#include <limits>                   // Para numeric_limits (limpiar buffer de entrada)
#include "jugador.h"                // Incluyo estructura Jugador
#include "utils.h"                  // Para funciones como toLower, limpiarConsola, esperarMs
#include "playerData.h"             // Para funciones registrarJuego, guardarSaldo

using namespace std;                // Evita escribir std:: en todo momento

// Funciones auxiliares del juego Hi-Lo

// Genero un número aleatorio entre 1 y 13 que representa el valor de una carta
inline int RandomCard() {
    return rand() % 13 + 1;         // Valor entre 1 (As) y 13 (Rey)
}

// Genero un palo aleatorio de entre cuatro palos posibles
inline string RandomSuit() {
    string suit[] = {"♠", "♥", "♦", "♣"};  // Palos comunes en cartas
    return suit[rand() % 4];         // Selección aleatoria
}

// Cambio el valor numérico de la carta a su representación en texto (A, J, Q, K)
inline string CardValue(int value) {
    if (value == 1) return "A";     // As
    if (value == 11) return "J";    // Jack / sota
    if (value == 12) return "Q";    // Queen / reina
    if (value == 13) return "K";    // King / rey
    return to_string(value);         // Para cartas del 2 al 10, convierto a string directo
}

// Dibujo la(s) carta(s) en ASCII para mostrar al jugador de forma visual
inline void AsciiHiloCards(int value[], string suit[], int count) {
    string line[7];                  // 7 líneas para la carta ASCII
    for (int i = 0; i < count; i++) {
        string value2 = CardValue(value[i]);              // Obtengo el valor textual
        string izq = value2.length() == 1 ? value2 + " " : value2;   // Formateo para izquierda
        string der = value2.length() == 1 ? " " + value2 : value2;   // Formateo para derecha

        // Dibujo cada línea de la carta y la voy acumulando
        line[0] += "┌─────────┐ ";
        line[1] += "│" + izq + "       │ ";
        line[2] += "│         │ ";
        line[3] += "│    " + suit[i] + "    │ ";
        line[4] += "│         │ ";
        line[5] += "│       " + der + "│ ";
        line[6] += "└─────────┘ ";
    }

    // Imprimo todas las líneas acumuladas para todas las cartas
    for (int i = 0; i < 7; i++) {
        cout << line[i] << endl;
    }
}

// Lógica principal de una ronda del juego Hi-Lo
inline void hilo(Jugador& jugador, int& bet) {  // Recibe referencia a jugador y apuesta (por referencia para modificar)
    int card = RandomCard();                     // Genero la primera carta aleatoria
    char guess, going;                           // Variables para almacenar elección y continuar juego
    bool keep = true;                            // Controla si la ronda sigue o termina
    string suit1 = RandomSuit();                 // Genero el palo de la carta inicial

    // Muestro la primera carta al jugador
    cout << "La primera carta es: \n";
    int values1[] = {card};
    string suits1[] = {suit1};
    AsciiHiloCards(values1, suits1, 1);          // Dibujo la carta
    cout << "\n";

    while (keep == true) {                        // Mientras el jugador decida continuar
        // Genero la siguiente carta aleatoria
        int card2 = RandomCard();
        string suit2 = RandomSuit();

        // Pido al jugador que adivine si la siguiente carta será mayor o menor
        while (true) {
            cout << "La siguiente carta será Mayor (M) o Menor (m): ";
            cin >> guess;
            if (guess == 'M' || guess == 'm' || guess == 'L' || guess == 'l') break;  // Acepto M/m y L/l (mayor/menor)
            cout << "Opción inválida, por favor selecciona 'M' o 'm'\n";
        }

        // Muestro la carta siguiente
        cout << "---------------------------------------------------\n";
        cout << "La siguiente carta es: \n";
        int values2[] = {card2};
        string suits2[] = {suit2};
        AsciiHiloCards(values2, suits2, 1);
        cout << endl;

        // Verifico si el jugador acertó
        if (((guess == 'M' || guess == 'm') && card < card2) ||       // Adivinó mayor y es mayor
            ((guess == 'L' || guess == 'l') && card > card2)) {       // Adivinó menor y es menor
            card = card2;                                              // Actualizo la carta actual
            bet = bet * 2;                                             // Doblo la apuesta
            cout << "¡Felicidades, ganaste esta ronda!\n";

            // Pregunto si quiere seguir jugando
            while (true) {
                cout << "¿Quieres seguir jugando? (S/N): ";
                cin >> going;
                if (going == 'S' || going == 's' || going == 'N' || going == 'n') break;
                cout << "Opción inválida, por favor selecciona 'S' o 'N'\n";
            }

            // Si no quiere seguir, termina y paga las ganancias
            if (going == 'N' || going == 'n') {
                jugador.dinero += bet;                                 // Sumo las ganancias al saldo
                cout << "Gracias por jugar. Tu ganancia es: $" << bet << endl;
                jugador.partidasGanadas++;                             // Actualizo estadísticas
                registrarJuego("Hi-Lo", jugador.nombre, bet, jugador.dinero); // Registro juego
                keep = false;                                          // Termino la ronda
            }

        } else if (card == card2) {                                    // Empate: las cartas son iguales
            cout << "¡Fue un empate!\n";
            cout << "Nadie pierde, nadie gana.\n";

            // Pregunto si quiere seguir jugando en empate
            while (true) {
                cout << "¿Quieres seguir jugando? (S/N): ";
                cin >> going;
                if (going == 'S' || going == 's' || going == 'N' || going == 'n') break;
                cout << "Opción inválida, por favor selecciona 'S' o 'N'\n";
            }

            // Si no quiere seguir, devuelvo la apuesta
            if (going == 'N' || going == 'n') {
                jugador.dinero += bet;                                 // Devuelvo la apuesta
                cout << "Gracias por jugar. Tu apuesta devuelta es: $" << bet << endl;
                jugador.partidasEmpatadas++;                           // Actualizo estadísticas
                registrarJuego("Hi-Lo", jugador.nombre, 0, jugador.dinero); // Registro juego con 0 ganancia
                keep = false;                                          // Termino la ronda
            }
        }
        // Si adivinó mal, pierde la apuesta y termina la ronda
        else {
            cout << "¡Incorrecto! Perdiste tu apuesta.\n";
            jugador.dinero -= bet;                                     // Resto la apuesta al saldo
            jugador.partidasPerdidas++;                                // Actualizo estadísticas
            registrarJuego("Hi-Lo", jugador.nombre, -bet, jugador.dinero); // Registro juego con pérdida
            bet = 0;                                                  // La apuesta queda en 0 (perdida)
            keep = false;                                             // Termino la ronda
        }
        // Después de cada ronda guardo el saldo y actualizo estadísticas
        guardarSaldo(jugador.nombre, jugador.dinero);
        jugador.actualizarEstadisticas();
    }
}

// Función que confirma si la apuesta es válida y lanza el juego
inline void BetConfirm(Jugador& jugador, int& bet) {
    cout << "Tu dinero actual es $" << jugador.dinero << ". Ingresa tu apuesta (mínimo $10, máximo $500): $";

    while (true) {
        cin >> bet;
        // Verifico que la apuesta sea válida, que no sea mayor que saldo ni menor que 10 o mayor que 500
        if (cin.fail() || bet < 10 || bet > 500 || bet > jugador.dinero) {
            cin.clear();                                           // Limpio error de entrada
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpio buffer
            cout << "Apuesta inválida. Debe ser entre $10 y $500 y no puede exceder tu saldo actual.\n";
            cout << "Tu dinero actual es $" << jugador.dinero << ". Ingresa tu apuesta: $";
            continue;                                             // Pido otra vez la apuesta
        }
        break;                                                    // Salgo del bucle si está bien
    }
    jugador.partidasJugadas++;                                  // Aumento partidas jugadas
    hilo(jugador, bet);                                         // Inicio la partida con apuesta validada
}

// Menú principal del juego Hi-Lo
inline void jugarHilo(Jugador& jugador) {
    if (jugador.dinero <= 0) {                                  // Verifico que tenga saldo
        cout << "No tienes saldo suficiente. Deposita para jugar.\n";
        return;                                                 // Salgo si no tiene saldo
    }

    int bet = 0;                                                // Inicializo apuesta
    int option;                                                 // Opción de menú

    do {
        // Muestro menú de opciones
        cout << "\n---- ¡Bienvenido al juego HI-LO! ----\n";
        cout << "1. Explicación del juego \n";
        cout << "2. Jugar \n";
        cout << "3. Consultar tu saldo \n";
        cout << "4. Salir \n";
        cout << "Elige una opción: ";
        cin >> option;

        if (cin.fail()) {                                       // Manejo entrada inválida
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opción inválida. Por favor, ingresa un número.\n";
            continue;
        }

        // Ejecuto acción según la opción
        switch (option) {
            case 1:
                // Explicación clara del juego
                cout << "\n¡Bienvenido al juego HI-LO!\n\n";
                cout << "¡Este es súper fácil de jugar!\n\n";
                cout << "1. Primero, haz tu apuesta.\n";
                cout << "2. El crupier te muestra una carta.\n";
                cout << "3. Ahora es tu turno de adivinar -> ¿la siguiente carta será mayor o menor?\n\n";
                cout << "Si adivinas correctamente:\n";
                cout << "- Recuperas tu apuesta duplicada.\n";
                cout << "- Puedes seguir jugando para intentar ganar aún más, o retirar y llevarte tu recompensa.\n\n";
                cout << "Si adivinas incorrectamente:\n";
                cout << "- Pierdes tu apuesta.\n\n";
                break;
            case 2:
                // Inicio la lógica del juego con la apuesta validada
                BetConfirm(jugador, bet);
                break;
            case 3:
                // Muestro saldo actual
                cout << "Tu saldo es: $" << jugador.dinero << endl;
                break;
            case 4:
                cout << "Volviendo al menú principal... \n";
                break;
            default:
                cout << "Opción inválida \n";
                break;
        }
    } while (option != 4);                                       // Se repite hasta que elija salir
}

#endif // HILO_GAME_H
