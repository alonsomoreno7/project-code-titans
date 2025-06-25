#ifndef SLOT_MACHINE_GAME_H
#define SLOT_MACHINE_GAME_H

#include <iostream>
#include <string>
#include <algorithm> // Para std::transform, porque a veces necesitamos transformar cosas, como nuestras vidas.
#include <cstdlib>   // Para rand(), porque la suerte no se genera sola.
#include <ctime>     // Para time(), porque necesitamos saber qué hora es mientras perdemos dinero.
#include <limits>    // Para numeric_limits, porque a veces los números son más grandes que nuestras esperanzas.
#include "jugador.h" // Para la estructura Jugador, porque necesitamos saber quién está perdiendo.
#include "utils.h"   // Para setColor, resetColor, limpiarConsola, esperarMs, porque la vida es más colorida con colores.
#include "playerData.h" // Para registrarJuego, guardarSaldo, porque necesitamos llevar un registro de nuestras desgracias.

using namespace std;

// --- Funciones Generales de la Tragamonedas ---

// Función para cambiar el texto de color, porque a veces necesitamos un poco de color en nuestra vida.
inline void setColor(int colorCode) {
    cout << "\033[" << colorCode << "m"; // ¡Mágico! Cambiamos el color como si tuviéramos superpoderes!
}

// Función para volver al color blanco, porque a veces hay que volver a la realidad.
inline void resetColor() {
    cout << "\033[0m"; // ¡Y vuelta a empezar! El color blanco es el nuevo negro.
}

// Función para mostrar las instrucciones del juego, porque nadie quiere perderse en la confusión.
inline void showSlot() {
    limpiarConsola(); // Limpiar al mostrar instrucciones, porque el desorden no ayuda a nadie.
    cout << endl;
    cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                   -PLAY SLOT MACHINE-                    . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*    A slot machine is a game where a series of random     . " << endl;
    cout << "|    symbols are displayed on each spin. If all the        . " << endl;
    cout << ".    symbols on a line match, you win.                     | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".                                                          | " << endl;
    cout << ".    MENU (M)                                 PLAY (P)     * " << endl;
    cout << ".                                                          | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
}

// Función para mostrar el menú de dificultades del juego tragamonedas
inline void showSlotmenu() {
    limpiarConsola(); // Limpiar al mostrar menú de dificultad, porque la claridad es clave.
    cout << endl;
    cout << "* - * - * - * - * - * - * - * -*. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                      -SLOT MACHINE-                      . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                  Choose the difficulty:                  . " << endl;
    cout << "|                                                          . " << endl;
    cout << ".   (E) EASY:      3 lines (Apuesta: $100, Gana: $300)     | " << endl;
    cout << ".   (M) MEDIUM:    4 lines (Apuesta: $200, Gana: $800)     * " << endl;
    cout << ".   (H) HARD:      5 lines (Apuesta: $300, Gana: $1500)    | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".     BACK (B)                                             | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
}

// Función para mostrar una frase motivadora aleatoria cuando el jugador pierda
inline void losePhrases() {
    string lSentence_0 = "The next move could change everything…"; // ¡Sí, claro! Como si eso fuera a pasar.
    string lSentence_1 = "The reels don't move by themselves! Dare!"; // ¡Vamos, no seas gallina!
    string lSentence_2 = "The reels are heating up… don’t give up!"; // ¡Casi, casi! Como cuando intentas abrir un frasco.
    string LSentence_3 = "Almost there! The next turn could be the winner."; // ¡La esperanza es lo último que se pierde!
    int randomLphase = rand() % 4; // Elegimos una frase al azar, porque la vida es una ruleta.

    switch (randomLphase) {
        case 0:
            cout << endl;
            cout << lSentence_0 << endl;
            break;
        case 1:
            cout << endl;
            cout << lSentence_1 << endl;
            break;
        case 2:
            cout << endl;
            cout << lSentence_2 << endl;
            break;
        case 3:
            cout << endl;
            cout << LSentence_3 << endl;
            break;
        default:
            cout << endl;
            cout << "Luck turns around… and yours is about to return." << endl; // ¡O eso espero!
            break;
    }
}

// --- Funciones para el Modo Fácil (EASY MODE) ---

inline void emptySlotsE() {
     limpiarConsola(); // Limpiar al mostrar menú de dificultad, porque la claridad es clave.
    cout << endl;
    cout << "* - * - * - * - * - *. . . . . . . " << endl;
    cout << "|                                ." << endl;
    cout << "*          Try your luck!        ." << endl;
    cout << "|                                ." << endl;
    cout << "*    -----------------------     ." << endl;
    cout << ".   |       |       |       |    | " << endl;
    cout << ".   |   -   |   -   |   -   |    *" << endl;
    cout << ".   |       |       |       |    | " << endl;
    cout << ".    -----------------------     *" << endl;
    cout << ".   | Pull the lever (!)|        | " << endl;
    cout << ". . . . . . .* - * - * - * - * - *" << endl;
    cout << endl;
}

inline char randomSymbolE() {
    char symbol[] = {'@', '$', '7'}; // Símbolos clásicos, porque la originalidad no siempre es necesaria.
    return symbol[rand() % 3]; // Elegimos un símbolo al azar, como en la vida.
}

inline void symbolColorE(char slots[3]) {
    for (int i = 0; i < 3; i++) {
        switch (slots[i]) {
            case '$':
                setColor(34); // Azul, porque el dinero debería ser azul, ¿no?
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
            case '7':
                setColor(33); // Amarillo, como el oro... o el plátano.
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
            case '@':
                setColor(35); // Magenta, porque a veces hay que ser un poco extravagante.
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
            default:
                setColor(36); // Cian, porque es un color que no se usa mucho.
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
        }
    }
}

inline void finalSlotsE(char slots[3]) {
    cout << "---------------------------------" << endl; // Línea de separación, porque necesitamos un poco de drama.
    cout << "* - * - * - * - * - *. . . . . . . " << endl;
    cout << "|                                ." << endl;
    cout << "*            RESULTS!            ." << endl;
    cout << "|                                ." << endl;
    cout << "*    -----------------------     ." << endl;
    cout << ".   |       |       |       |    * " << endl;
    cout << ".   |   ";
    symbolColorE(slots); // Mostramos los símbolos en color, porque la vida es más divertida con color.
    cout << " |" << endl;
    cout << ".   |       |       |       |    * " << endl;
    cout << ".    -----------------------     | " << endl;
    cout << ". . . . . . .* - * - * - * - * - *" << endl;
    cout << endl;
}

inline bool jackpotE(char slots[3]) {
    return (slots[0] == slots[1] && slots[1] == slots[2]); // ¡Jackpot! O como me gusta llamarlo, "la suerte de los principiantes".
}

// Main game easy
inline void easyMode(Jugador& jugador) {
    const int APUESTA = 100; // Apuesta mínima, porque no quiero arruinarme en la primera ronda.
    const int GANANCIA = 300; // Ganancia, porque soñar es gratis.
    char symbols[3];
    bool ganoJackpot = false;
    string anotherRound;

    if (jugador.dinero < APUESTA) {
        
        cout << "No tienes suficiente dinero para jugar en modo Fácil. Necesitas $" << APUESTA << ".\n";
        return; // Salimos, porque no hay nada más triste que un jugador sin dinero.
    }

    while (true) {
        
        ganoJackpot = false; // Resetear para cada nueva ronda, como si no hubiera pasado nada.
        jugador.partidasJugadas++; // Contar la partida jugada, porque hay que llevar la cuenta de nuestras desgracias.

        cout << "\nHas apostado $" << APUESTA << " para esta ronda en modo Fácil.\n";
    limpiarConsola(); // Limpiar al mostrar instrucciones, porque el desorden no ayuda a nadie.
        int oportunidades = 4; // Cuatro oportunidades, porque no quiero ser demasiado generoso.
        for (int i = oportunidades; i > 0; i--) {
            while (true) {
                
                string nextSpin;
                cout << endl;
                cout << "Te quedan " << i << " oportunidades!" << endl;
                cout << "(P) para continuar..." << endl;
                getline(cin, nextSpin);
                if (nextSpin == "P" || nextSpin == "p") {
                    break; // ¡Vamos a girar esos carretes!
                } else {
                
                    cout << endl;
                    setColor(31);
                    cout << "Por favor, ingresa una opción válida (P), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
                    resetColor();
                }
            }

            while (true) {
                string pull;
                emptySlotsE(); // Esta función ya limpia la consola, porque la vida es un ciclo.
                getline(cin, pull);

                if (pull == "!") {
                    for (int j = 0; j < 3; j++) {
                        symbols[j] = randomSymbolE(); // Generamos símbolos aleatorios, porque la vida es una caja de sorpresas.
                    }
                    finalSlotsE(symbols); // Esta función ya limpia la consola, porque la sorpresa es mejor sin desorden.

                    if (jackpotE(symbols)) {
                        setColor(32);
                        cout << "            * ¡¡JACKPOT!! *   " << endl; // ¡Felicidades! Has ganado el premio gordo.
                        resetColor();
                        cout << endl;
                        cout << " ¡Felicidades! Has ganado: $" << GANANCIA << endl; // ¡Dinero, dinero, dinero!
                        cout << endl;
                        jugador.dinero += GANANCIA; // Sumar la ganancia, porque eso es lo que queremos.
                        jugador.partidasGanadas++; // Contar la victoria, porque hay que celebrar.
                        registrarJuego("Tragamonedas (Fácil)", jugador.nombre, GANANCIA, jugador.dinero); // Guardamos el registro, porque la historia debe ser contada.
                        ganoJackpot = true; // Marcamos que ganamos, porque no hay nada como un buen jackpot.
                        i = 0; // Terminar las oportunidades, porque ya ganamos.
                        break;
                    } else {
                        setColor(36);
                        cout << "            SIGUE INTENTANDO " << endl; // ¡No te rindas! La suerte puede cambiar.
                        resetColor();
                        losePhrases(); // Frases motivadoras, porque todos necesitamos un empujón.
                        break;
                    }
                } else {
                    
                    cout << endl;
                    setColor(31);
                    cout << "Por favor, ingresa una opción válida (!), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
                    resetColor();
                }
            }
            if (ganoJackpot) break; // Si ya ganó, salir del bucle de oportunidades, porque ya es suficiente emoción por hoy.
        }

        if (!ganoJackpot) {
            cout << endl;
            cout << "   Tendrás más suerte la próxima vez." << endl; // ¡La próxima vez será mejor!
            cout << "-$" << APUESTA << endl; // Restamos la apuesta, porque la vida no siempre es justa.
            cout << endl;
            jugador.dinero -= APUESTA; // Restar la apuesta si no ganó, porque hay que aprender a perder.
            jugador.partidasPerdidas++; // Contar la derrota, porque hay que ser realista.
            registrarJuego("Tragamonedas (Fácil)", jugador.nombre, -APUESTA, jugador.dinero); // Guardamos el registro, porque la historia debe ser contada.
        }

        // Guardar saldo y estadísticas después de cada partida
        guardarSaldo(jugador.nombre, jugador.dinero); // Guardamos el saldo, porque no queremos perderlo todo.
        jugador.actualizarEstadisticas(); // Actualizamos estadísticas, porque hay que llevar la cuenta.

        if (jugador.dinero < APUESTA) {
            cout << "No tienes suficiente dinero para otra ronda en modo Fácil. Necesitas $" << APUESTA << ".\n"; // Mensaje de despedida, porque a veces hay que saber cuándo parar.
            break; // Salir si no hay dinero para otra apuesta, porque no hay que ser terco.
        }

        while (true) {
            cout << "\n¿Quieres jugar otra ronda?" << endl;
            cout << "     SÍ (S).        NO(N)" << endl;
            getline(cin, anotherRound);

            if (anotherRound == "S" || anotherRound == "s") {
                cout << endl;
                setColor(32);
                cout << "¡¡BUENA SUERTE!!" << endl; // ¡Que la suerte te acompañe!
                resetColor();
                break;
            } else if (anotherRound == "N" || anotherRound == "n") {
                cout << endl;
                cout << "Volviendo al menú..." << endl; // ¡Hasta la próxima!
                break;
            } else {
                
                cout << endl;
                setColor(31);
                cout << "Por favor, ingresa una opción válida (S) o (N), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
                resetColor();
            }
        }

        if (anotherRound == "N" || anotherRound == "n") {
            break; // Salimos del bucle si el jugador no quiere seguir, porque hay que respetar las decisiones.
        }
    }
}

// --- Funciones para el Modo Medio (MEDIUM MODE) ---

inline void emptySlotsM() {
     limpiarConsola(); // Limpiar al mostrar menú de dificultad, porque la claridad es clave.
    cout << endl;
    cout << "* - * - * - * - * - . . . . . . . . . . . " << endl;
    cout << "|                                       ." << endl;
    cout << "*             Try your luck!            ." << endl;
    cout << "|                                       ." << endl;
    cout << "*    -------------------------------    ." << endl;
    cout << ".   |       |       |       |       |   . " << endl;
    cout << ".   |   -   |   -   |   -   |   -   |   *" << endl;
    cout << ".   |       |       |       |       |   | " << endl;
    cout << "*    -------------------------------    *" << endl;
    cout << ".    | Pull the lever (!)|              | " << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - * " << endl;
    cout << endl;
}

inline char randomSymbolM() {
    char symbol[] = {'$', '7', '@'}; // Símbolos clásicos, porque la originalidad no siempre es necesaria.
    return symbol[rand() % 3]; // Elegimos un símbolo al azar, como en la vida.
}

inline void symbolColorM(char slots[4]) {
    for (int i = 0; i < 4; i++) {
        switch (slots[i]) {
            case '$':
                setColor(34); // Azul, porque el dinero debería ser azul, ¿no?
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
            case '7':
                setColor(33); // Amarillo, como el oro... o el plátano.
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
            case '@':
                setColor(35); // Magenta, porque a veces hay que ser un poco extravagante.
                cout << slots [i];
                resetColor();
                cout << "   | " << "  ";
                break;
            default:
                setColor(36); // Cian, porque es un color que no se usa mucho.
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
        }
    }
}

inline void finalSlotsM(char slots[4]) {
    cout << "---------------------------------" << endl; // Línea de separación, porque necesitamos un poco de drama.
    cout << "* - * - * - * - * - . . . . . . . . . . . " << endl;
    cout << "|                                       ." << endl;
    cout << "*                RESULTS!               ." << endl;
    cout << "|                                       ." << endl;
    cout << "*    -------------------------------    ." << endl;
    cout << ".   |       |       |       |       |   . " << endl;
    cout << ".   |   ";
    symbolColorM(slots); // Mostramos los símbolos en color, porque la vida es más divertida con color.
    cout << "*" << endl;
    cout << ".   |       |       |       |       |   | " << endl;
    cout << "*    -------------------------------    *" << endl;
    cout << ".    | Pull the lever (!)|              | " << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - * " << endl;
    cout << endl;
}

inline bool jackpotM(char slots[4]) {
    return (slots[0] == slots[1] && slots[1] == slots[2] && slots[2] == slots[3]); // ¡Jackpot! O como me gusta llamarlo, "la suerte de los principiantes".
}

inline void mediumMode(Jugador& jugador) {
    const int APUESTA = 200; // Apuesta mínima, porque no quiero arruinarme en la primera ronda.
    const int GANANCIA = 800; // Ganancia, porque soñar es gratis.
    char symbols[4];
    bool ganoJackpot = false;
    string anotherRound;

    if (jugador.dinero < APUESTA) {
       
        cout << "No tienes suficiente dinero para jugar en modo Medio. Necesitas $" << APUESTA << ".\n";
        return; // Salimos, porque no hay nada más triste que un jugador sin dinero.
    }

    while (true) {
       
        ganoJackpot = false; // Resetear para cada nueva ronda, como si no hubiera pasado nada.
        jugador.partidasJugadas++; // Contar la partida jugada, porque hay que llevar la cuenta de nuestras desgracias.

        cout << "\nHas apostado $" << APUESTA << " para esta ronda en modo Medio.\n";

        int oportunidades = 8; // Ocho oportunidades, porque no quiero ser demasiado generoso.
        for (int i = oportunidades; i > 0; i--) {
            while (true) {
                
                string nextSpin;
                cout << endl;
                cout << "Te quedan " << i << " oportunidades!" << endl;
                cout << "(P) para continuar..." << endl;
                getline(cin, nextSpin);
                if (nextSpin == "P" || nextSpin == "p") {
                    break; // ¡Vamos a girar esos carretes!
                } else {
                    
                    cout << endl;
                    setColor(31);
                    cout << "Por favor, ingresa una opción válida (P), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
                    resetColor();
                }
            }

            while (true) {
                string pull;
                emptySlotsM(); // Esta función ya limpia la consola, porque la vida es un ciclo.
                getline(cin, pull);

                if (pull == "!") {
                    for (int j = 0; j < 4; j++) {
                        symbols[j] = randomSymbolM(); // Generamos símbolos aleatorios, porque la vida es una caja de sorpresas.
                    }
                    finalSlotsM(symbols); // Esta función ya limpia la consola, porque la sorpresa es mejor sin desorden.

                    if (jackpotM(symbols)) {
                        setColor(32);
                        cout << "               * ¡¡JACKPOT!! *   " << endl; // ¡Felicidades! Has ganado el premio gordo.
                        resetColor();
                        cout << endl;
                        cout << " ¡Felicidades! Has ganado: $" << GANANCIA << endl; // ¡Dinero, dinero, dinero!
                        cout << endl;
                        jugador.dinero += GANANCIA; // Sumar la ganancia, porque eso es lo que queremos.
                        jugador.partidasGanadas++; // Contar la victoria, porque hay que celebrar.
                        registrarJuego("Tragamonedas (Medio)", jugador.nombre, GANANCIA, jugador.dinero); // Guardamos el registro, porque la historia debe ser contada.
                        ganoJackpot = true; // Marcamos que ganamos, porque no hay nada como un buen jackpot.
                        i = 0; // Terminar las oportunidades, porque ya ganamos.
                        break;
                    } else {
                        setColor(36);
                        cout << "               SIGUE INTENTANDO " << endl; // ¡No te rindas! La suerte puede cambiar.
                        resetColor();
                        losePhrases(); // Frases motivadoras, porque todos necesitamos un empujón.
                        break;
                    }
                } else {
                    
                    cout << endl;
                    setColor(31);
                    cout << "Por favor, ingresa una opción válida (!), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
                    resetColor();
                }
            }
            if (ganoJackpot) break; // Si ya ganó, salir del bucle de oportunidades, porque ya es suficiente emoción por hoy.
        }

        if (!ganoJackpot) {
            cout << endl;
            cout << "   Tendrás más suerte la próxima vez." << endl; // ¡La próxima vez será mejor!
            cout << "-$" << APUESTA << endl; // Restamos la apuesta, porque la vida no siempre es justa.
            cout << endl;
            jugador.dinero -= APUESTA; // Restar la apuesta si no ganó, porque hay que aprender a perder.
            jugador.partidasPerdidas++; // Contar la derrota, porque hay que ser realista.
            registrarJuego("Tragamonedas (Medio)", jugador.nombre, -APUESTA, jugador.dinero); // Guardamos el registro, porque la historia debe ser contada.
        }

        guardarSaldo(jugador.nombre, jugador.dinero); // Guardamos el saldo, porque no queremos perderlo todo.
        jugador.actualizarEstadisticas(); // Actualizamos estadísticas, porque hay que llevar la cuenta.

        if (jugador.dinero < APUESTA) {
            cout << "No tienes suficiente dinero para otra ronda en modo Medio. Necesitas $" << APUESTA << ".\n"; // Mensaje de despedida, porque a veces hay que saber cuándo parar.
            break; // Salir si no hay dinero para otra apuesta, porque no hay que ser terco.
        }

        while (true) {
            cout << "\n¿Quieres jugar otra ronda?" << endl;
            cout << "     SÍ (S).        NO(N)" << endl;
            getline(cin, anotherRound);

            if (anotherRound == "S" || anotherRound == "s") {
                cout << endl;
                setColor(32);
                cout << "¡¡BUENA SUERTE!!" << endl; // ¡Que la suerte te acompañe!
                resetColor();
                break;
            } else if (anotherRound == "N" || anotherRound == "n") {
                cout << endl;
                cout << "Volviendo al menú..." << endl; // ¡Hasta la próxima!
                break;
            } else {
               
                cout << endl;
                setColor(31);
                cout << "Por favor, ingresa una opción válida (S) o (N), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
                resetColor();
            }
        }

        if (anotherRound == "N" || anotherRound == "n") {
            break; // Salimos del bucle si el jugador no quiere seguir, porque hay que respetar las decisiones.
        }
    }
}

// --- Funciones para el Modo Difícil (HARD MODE) ---

inline void emptySlotsH() {
     limpiarConsola(); // Limpiar al mostrar menú de dificultad, porque la claridad es clave.
    cout << endl;
    cout << "* - * - * - * - * - * - * . . . . . . . . . . . . " << endl;
    cout << "|                                               ." << endl;
    cout << "*                 Try your luck!                ." << endl;
    cout << "|                                               ." << endl;
    cout << "*    ---------------------------------------    ." << endl;
    cout << ".   |       |       |       |       |       |   . " << endl;
    cout << ".   |   -   |   -   |   -   |   -   |   -   |   *" << endl;
    cout << ".   |       |       |       |       |       |   | " << endl;
    cout << ".    ---------------------------------------    *" << endl;
    cout << ".    | Pull the lever (!)|                      | " << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - * - * - * " << endl;
    cout << endl;
}

inline char randomSymbolH() {
    char symbol[] = {'$', '7', '@'}; // Símbolos clásicos, porque la originalidad no siempre es necesaria.
    return symbol[rand() % 3]; // Elegimos un símbolo al azar, como en la vida.
}

inline void symbolColorH(char slots[5]) {
    for (int i = 0; i < 5; i++) {
        switch (slots[i]) {
            case '$':
                setColor(34); // Azul, porque el dinero debería ser azul, ¿no?
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
            case '7':
                setColor(33); // Amarillo, como el oro... o el plátano.
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
            case '@':
                setColor(35); // Magenta, porque a veces hay que ser un poco extravagante.
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
            default:
                setColor(36); // Cian, porque es un color que no se usa mucho.
                cout << slots[i];
                resetColor();
                cout << "   | " << "  ";
                break;
        }
    }
}

inline void finalSlotsH(char slots[5]) {
    
    cout << "---------------------------------" << endl; // Línea de separación, porque necesitamos un poco de drama.
    cout << "* - * - * - * - * - * - * . . . . . . . . . . . . " << endl;
    cout << "|                                               ." << endl;
    cout << "*                    RESULTS!                   ." << endl;
    cout << "|                                               ." << endl;
    cout << "*    ---------------------------------------    ." << endl;
    cout << ".   |       |       |       |       |       |   . " << endl;
    cout << ".   |   ";
    symbolColorH(slots); // Mostramos los símbolos en color, porque la vida es más divertida con color.
    cout << "." << endl;
    cout << ".   |       |       |       |       |       |   | " << endl;
    cout << ".    ---------------------------------------    *" << endl;
    cout << ".    | Pull the lever (!)|                      | " << endl;
    cout << ". . . . . . . . . . . . * - * - * - * - * - * - * " << endl;
    cout << endl;
}

inline bool jackpotH(char slots[5]) {
    return (slots[0] == slots[1] && slots[1] == slots[2] && slots[2] == slots[3] && slots[3] == slots[4]); // ¡Jackpot! O como me gusta llamarlo, "la suerte de los principiantes".
}

inline void hardMode(Jugador& jugador) {
    const int APUESTA = 300; // Apuesta mínima, porque no quiero arruinarme en la primera ronda.
    const int GANANCIA = 1500; // Ganancia, porque soñar es gratis.
    char symbols[5];
    bool ganoJackpot = false;
    string anotherRound;

    if (jugador.dinero < APUESTA) {
       
        cout << "No tienes suficiente dinero para jugar en modo Difícil. Necesitas $" << APUESTA << ".\n";
        return; // Salimos, porque no hay nada más triste que un jugador sin dinero.
    }

    while (true) {
       
        ganoJackpot = false; // Resetear para cada nueva ronda, como si no hubiera pasado nada.
        jugador.partidasJugadas++; // Contar la partida jugada, porque hay que llevar la cuenta de nuestras desgracias.

        cout << "\nHas apostado $" << APUESTA << " para esta ronda en modo Difícil.\n";

        int oportunidades = 15; // Quince oportunidades, porque la vida es corta y hay que aprovechar.
        for (int i = oportunidades; i > 0; i--) {
            while (true) {
                
                string nextSpin;
                cout << endl;
                cout << "Te quedan " << i << " oportunidades!" << endl;
                cout << "(P) para continuar..." << endl;
                getline(cin, nextSpin);
                if (nextSpin == "P" || nextSpin == "p") {
                    break; // ¡Vamos a girar esos carretes!
                } else {
                    
                    cout << endl;
                    setColor(31);
                    cout << "Por favor, ingresa una opción válida (P), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
                    resetColor();
                }
            }

            while (true) {
                string pull;
                emptySlotsH(); // Esta función ya limpia la consola, porque la vida es un ciclo.
                getline(cin, pull);

                if (pull == "!") {
                    for (int j = 0; j < 5; j++) {
                        symbols[j] = randomSymbolH(); // Generamos símbolos aleatorios, porque la vida es una caja de sorpresas.
                    }
                    finalSlotsH(symbols); // Esta función ya limpia la consola, porque la sorpresa es mejor sin desorden.

                    if (jackpotH(symbols)) {
                        setColor(32);
                        cout << "                   * ¡¡JACKPOT!! *   " << endl; // ¡Felicidades! Has ganado el premio gordo.
                        resetColor();
                        cout << endl;
                        cout << " ¡Felicidades! Has ganado: $" << GANANCIA << endl; // ¡Dinero, dinero, dinero!
                        cout << endl;
                        jugador.dinero += GANANCIA; // Sumar la ganancia, porque eso es lo que queremos.
                        jugador.partidasGanadas++; // Contar la victoria, porque hay que celebrar.
                        registrarJuego("Tragamonedas (Difícil)", jugador.nombre, GANANCIA, jugador.dinero); // Guardamos el registro, porque la historia debe ser contada.
                        ganoJackpot = true; // Marcamos que ganamos, porque no hay nada como un buen jackpot.
                        i = 0; // Terminar las oportunidades, porque ya ganamos.
                        break;
                    } else {
                        setColor(36);
                        cout << "                   SIGUE INTENTANDO " << endl; // ¡No te rindas! La suerte puede cambiar.
                        resetColor();
                        losePhrases(); // Frases motivadoras, porque todos necesitamos un empujón.
                        break;
                    }
                } else {
                    
                    cout << endl;
                    setColor(31);
                    cout << "Por favor, ingresa una opción válida (!), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
                    resetColor();
                }
            }
            if (ganoJackpot) break; // Si ya ganó, salir del bucle de oportunidades, porque ya es suficiente emoción por hoy.
        }

        if (!ganoJackpot) {
            cout << endl;
            cout << "   Tendrás más suerte la próxima vez." << endl; // ¡La próxima vez será mejor!
            cout << "-$" << APUESTA << endl; // Restamos la apuesta, porque la vida no siempre es justa.
            cout << endl;
            jugador.dinero -= APUESTA; // Restar la apuesta si no ganó, porque hay que aprender a perder.
            jugador.partidasPerdidas++; // Contar la derrota, porque hay que ser realista.
            registrarJuego("Tragamonedas (Difícil)", jugador.nombre, -APUESTA, jugador.dinero); // Guardamos el registro, porque la historia debe ser contada.
        }

        guardarSaldo(jugador.nombre, jugador.dinero); // Guardamos el saldo, porque no queremos perderlo todo.
        jugador.actualizarEstadisticas(); // Actualizamos estadísticas, porque hay que llevar la cuenta.

        if (jugador.dinero < APUESTA) {
            cout << "No tienes suficiente dinero para otra ronda en modo Difí cil. Necesitas $" << APUESTA << ".\n"; // Mensaje de despedida, porque a veces hay que saber cuándo parar.
            break; // Salir si no hay dinero para otra apuesta, porque no hay que ser terco.
        }

        while (true) {
            cout << "\n¿Quieres jugar otra ronda?" << endl;
            cout << "     SÍ (S).        NO(N)" << endl;
            getline(cin, anotherRound);

            if (anotherRound == "S" || anotherRound == "s") {
                cout << endl;
                setColor(32);
                cout << "¡¡BUENA SUERTE!!" << endl; // ¡Que la suerte te acompañe!
                resetColor();
                break;
            } else if (anotherRound == "N" || anotherRound == "n") {
                cout << endl;
                cout << "Volviendo al menú..." << endl; // ¡Hasta la próxima!
                break;
            } else {
                
                cout << endl;
                setColor(31);
                cout << "Por favor, ingresa una opción válida (S) o (N), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
                resetColor();
            }
        }

        if (anotherRound == "N" || anotherRound == "n") {
            break; // Salimos del bucle si el jugador no quiere seguir, porque hay que respetar las decisiones.
        }
    }
}

// --- Función Principal del Juego de Tragamonedas ---

inline void jugarTragamonedas(Jugador& jugador) {
    if (jugador.dinero <= 0) {
        
        cout << "No tienes saldo suficiente. Deposita para jugar.\n"; // Mensaje de "no hay dinero, no hay juego".
        return; // Salimos, porque no hay nada más triste que un jugador sin dinero.
    }

    while (true) {
        showSlot(); // Esta función ya limpia la consola, porque la frescura es clave.
        string option;
        getline(cin, option); // Usuario ingresa opción

        // Verificación de opción ingresada
        if (option == "M" || option == "m") {
            
            cout << "Volviendo al menú principal..." << endl; // Mensaje de "hasta luego".
            break;
        } else if (option == "P" || option == "p") {
            while (true) {
                showSlotmenu(); // Esta función ya limpia la consola, porque la frescura es clave.
                string difficultyOption;
                getline(cin, difficultyOption); // Usuario ingresa su opción

                if (difficultyOption == "B" || difficultyOption == "b") {
                   
                    break;
                } else if (difficultyOption == "E" || difficultyOption == "e") {
                    easyMode(jugador); // Las funciones de modo ya manejan su limpieza, porque la frescura es clave.
                } else if (difficultyOption == "M" || difficultyOption == "m") {
                    mediumMode(jugador); // Las funciones de modo ya manejan su limpieza, porque la frescura es clave.
                } else if (difficultyOption == "H" || difficultyOption == "h") {
                    hardMode(jugador); // Las funciones de modo ya manejan su limpieza, porque la frescura es clave.
                } else {
                    
                    setColor(31);
                    cout << "Por favor, ingresa una opción válida (E), (M), (H) o (B), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
                    resetColor();
                }
            }
        } else {
           
            setColor(31);
            cout << "Por favor, ingresa una opción válida (M) o (P), intenta de nuevo." << endl; // Mensaje de error, porque todos lo necesitamos.
            resetColor();
        }
    }
}

#endif // SLOT_MACHINE_GAME_H