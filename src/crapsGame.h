#ifndef CRAPS_GAME_H               // Evito múltiples inclusiones del mismo archivo
#define CRAPS_GAME_H               // Defino macro para indicar que ya fue incluido

#include <string>                  // Incluyo string para manejar texto
#include <iostream>                // Para entrada y salida por consola (cin, cout)
#include <cstdlib>                 // Para generar números aleatorios con rand()
#include <cctype>                  // Para funciones de caracteres (tolower)
#include <limits>                  // Para limpiar buffer de entrada y manejar límites
#ifdef _WIN32
#include <windows.h>               // En Windows, incluyo windows.h para Sleep()
#endif
#include "utils.h"                 // Uso funciones como limpiarConsola y esperarMs
#include "playerData.h"            // Uso para registrar juego y guardar saldo
#include "jugador.h"               // Uso estructura Jugador con datos y estadísticas

using namespace std;              // Para no usar std:: constantemente

// Función que muestra dos dados en ASCII, dado 1 y dado 2
inline void mostrarDadosASCII(int d1, int d2) {
    // Defino las caras de los dados como arreglos de cadenas (5 líneas por dado)
    const char* diceFaces[6][5] = {
        {"+-------+", "|       |", "|   o   |", "|       |", "+-------+"},   // 1
        {"+-------+", "| o     |", "|       |", "|     o |", "+-------+"},   // 2
        {"+-------+", "| o     |", "|   o   |", "|     o |", "+-------+"},   // 3
        {"+-------+", "| o   o |", "|       |", "| o   o |", "+-------+"},   // 4
        {"+-------+", "| o   o |", "|   o   |", "| o   o |", "+-------+"},   // 5
        {"+-------+", "| o   o |", "| o   o |", "| o   o |", "+-------+"}    // 6
    };

    // Imprimo línea por línea los dos dados lado a lado
    for (int i = 0; i < 5; ++i) {
        cout << diceFaces[d1 - 1][i] << "   " << diceFaces[d2 - 1][i] << "\n";
    }
    cout << endl;
}

// Función que lanza dados con animación, mostrando varios cambios rápidos
inline int lanzarDadosAnimado() {
    int d1 = 1, d2 = 1;  // Inicializo dados

    // Limpio la consola dependiendo del sistema operativo
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    // Bucle que simula dados girando (10 repeticiones)
    for (int i = 0; i < 10; ++i) {
        d1 = rand() % 6 + 1;  // Genero dado 1 aleatorio entre 1 y 6
        d2 = rand() % 6 + 1;  // Genero dado 2 aleatorio entre 1 y 6

        // Limpio consola para animar dados
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        cout << "Tirando dados...\n\n";  // Mensaje mientras se "tiran" los dados
        mostrarDadosASCII(d1, d2);       // Muestro los dados actuales
        esperarMs(100);                  // Espero 100 ms para efecto animado
    }

    cout << "Resultado final:\n\n";      // Mensaje con el resultado definitivo
    mostrarDadosASCII(d1, d2);           // Muestro los dados finales
    return d1 + d2;                      // Retorno la suma de los dados
}

// Función para validar la entrada del nivel de dificultad (1 a 3)
inline int validarEntradaCraps() {
    int choice = 0;  // Variable para guardar la selección del usuario
    cout << "Selecciona tu nivel de dificultad: ";
    cin >> choice;   // Leo entrada

    // Mientras la entrada sea inválida (no número, no en rango, o buffer no limpio)
    while (cin.fail() || cin.peek() != '\n' || choice < 1 || choice > 3) {
        cin.clear();                       // Limpio estado de error de entrada
        cin.ignore(1000, '\n');            // Ignoro lo que haya quedado en el buffer
        // Muestro mensaje en un cuadro decorativo indicando el error y cómo corregirlo
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                                            ♠ ♥ Mensaje ♥ ♣                                           ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║           Por favor, no ingreses letras o caracteres especiales, solo números entre 1 y 3            ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                     Selecciona tu nivel de dificultad:                                               ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        cin >> choice;  // Intento leer de nuevo
    }
    return choice;  // Retorno la opción válida
}

// Función que ejecuta la lógica del juego Craps según los intentos máximos permitidos y la apuesta
inline int ejecutarJuegoCraps(Jugador& jugador, int maxAttempts, int apuesta) {
    cout << "Iniciando tirada inicial...\n";  // Mensaje inicio ronda
    esperarMs(3000);                         // Espero 3 segundos

    int comeOutRoll = lanzarDadosAnimado(); // Realizo tirada inicial animada
    cout << "La tirada inicial es: " << comeOutRoll << "\n";  // Muestro resultado
    esperarMs(3000);                         // Espero 3 segundos

    // Evaluación inmediata de la tirada inicial según reglas Craps
    if (comeOutRoll == 2 || comeOutRoll == 3 || comeOutRoll == 12) {
        // Mensaje de derrota si sale Craps (2, 3 o 12)
        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                 ♠ ♥ Has Perdido ♥ ♣               ║\n";
        cout << "║                                                   ║\n";
        cout << "║           ¡Craps! Has perdido el juego.           ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";
        registrarJuego("Craps", jugador.nombre, -apuesta, jugador.dinero - apuesta);  // Registro pérdida
        jugador.partidasPerdidas++;   // Incremento partidas perdidas
        return -apuesta;              // Retorno pérdida
    }
    else if (comeOutRoll == 7 || comeOutRoll == 11) {
        // Mensaje de victoria instantánea si sale 7 u 11
        cout << "╔═══════════════════════════════════════════════╗\n";
        cout << "║                 ♠ ♥ Has Ganado ♥ ♣            ║\n";
        cout << "║                                               ║\n";
        cout << "║     ¡Felicidades, has ganado la ronda!        ║\n";
        cout << "║                                               ║\n";
        cout << "╚═══════════════════════════════════════════════╝\n";
        registrarJuego("Craps", jugador.nombre, apuesta, jugador.dinero + apuesta);  // Registro ganancia
        jugador.partidasGanadas++;  // Incremento partidas ganadas
        return apuesta;             // Retorno ganancia
    }
    else {
        // Si sale otro número se establece un punto para la siguiente ronda
        int point = comeOutRoll;
        cout << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                                            ♠ ♥ Mensaje ♥ ♣                                                  ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                              El punto está establecido, el tirador volverá a lanzar...                      ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                      Si la tirada es: " << comeOutRoll << ", el tirador gana; si es 7, el tirador pierde                      ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        esperarMs(3000);  // Espero 3 segundos para suspense

        int attempts = 0;  // Contador de intentos realizados
        while (maxAttempts == 0 || attempts < maxAttempts) {  // Bucle si intentos ilimitados o menor al máximo
            attempts++;  // Incremento intento
            comeOutRoll = lanzarDadosAnimado();  // Nueva tirada animada
            cout << "Intento #" << attempts << endl;
            cout << "La nueva tirada es: " << comeOutRoll << "\n";  // Muestro resultado
            esperarMs(3000);

            if (comeOutRoll == point) {  // Si sale el punto, gana el jugador
                cout << "╔═════════════════════════════════════════════════════╗\n";
                cout << "║                    ♠ ♥ Has Ganado ♥ ♣               ║\n";
                cout << "║                                                     ║\n";
                cout << "║                ¡Felicidades, has ganado!            ║\n";
                cout << "║                                                     ║\n";
                cout << "╚═════════════════════════════════════════════════════╝\n";
                registrarJuego("Craps", jugador.nombre, apuesta, jugador.dinero + apuesta);
                jugador.partidasGanadas++;
                return apuesta;
            }
            else if (comeOutRoll == 7) {  // Si sale 7, pierde el jugador
                cout << "╔═════════════════════════════════════════════════════╗\n";
                cout << "║                   ♠ ♥ Has Perdido ♥ ♣               ║\n";
                cout << "║                                                     ║\n";
                cout << "║               Lo siento, has perdido el juego.      ║\n";
                cout << "║                                                     ║\n";
                cout << "╚═════════════════════════════════════════════════════╝\n";
                registrarJuego("Craps", jugador.nombre, -apuesta, jugador.dinero - apuesta);
                jugador.partidasPerdidas++;
                return -apuesta;
            }
        }

        // Si se acaban los intentos sin ganar ni perder, el jugador pierde por límite de intentos
        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                  ♠ ♥ Mensaje ♥ ♣                  ║\n";
        cout << "║                                                   ║\n";
        cout << "║       Lo siento, te has quedado sin intentos.     ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";
        registrarJuego("Craps", jugador.nombre, -apuesta, jugador.dinero - apuesta);
        jugador.partidasPerdidas++;
        return -apuesta;
    }
}

// Función principal que controla la sesión de juego Craps para un jugador
inline void jugarCraps(Jugador& jugador) {
    if (jugador.dinero <= 0) {  // Verifico que tenga dinero para apostar
        cout << "No tienes saldo suficiente. Deposita para jugar.\n";  // Mensaje si no tiene saldo
        return;
    }

    char jugarOtraVez;  // Variable para controlar si juega otra ronda
    do {
         limpiarConsola();
        int apuesta;  // Variable para apuesta
        cout << "\nTu dinero actual es $" << jugador.dinero << ". Ingresa tu apuesta (mínimo $10, máximo $500): $";

        while (true) {  // Bucle para validar apuesta
            cin >> apuesta;
            if (apuesta == 0) {  // Si ingresa 0 cancela apuesta
                cout << "Apuesta cancelada.\n";
                return;
            }
            if (cin.fail() || apuesta < 10 || apuesta > 500) {  // Valido rango y entrada
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Apuesta inválida. Debe ser entre $10 y $500.\n";
                cout << "Ingresa tu apuesta: $";
                continue;
            }
            if (apuesta > jugador.dinero) {  // Valido saldo suficiente
                cout << "Saldo insuficiente. Tu saldo actual es $" << jugador.dinero << ".\n";
                cout << "Ingresa tu apuesta: $";
                continue;
            }
            break;  // Salgo del bucle si la apuesta es válida
        }

        // Muestro menú de bienvenida con niveles para seleccionar
        cout << "\n╔═══════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                       ♠ ♥ Bienvenido a Craps ♥ ♣                      ║\n";
        cout << "║                                                                       ║\n";
        cout << "║          Selecciona el nivel de dificultad para empezar:              ║\n";
        cout << "║                                                                       ║\n";
        cout << "║                  1. Fácil     ♣     2. Medio     ♦                    ║\n";
        cout << "║                            3. Difícil       ♠                         ║\n";
        cout << "║                                                                       ║\n";
        cout << "╚═══════════════════════════════════════════════════════════════════════╝\n";

        int selection = validarEntradaCraps();  // Pido y valido nivel dificultad

        jugador.partidasJugadas++;  // Incremento partidas jugadas

        int resultado = 0;          // Variable para resultado de la partida
        switch (selection) {        // Según nivel ejecuta con distinto número de intentos
            case 1:
                cout << "Has seleccionado el nivel fácil (intentos ilimitados)\n";
                resultado = ejecutarJuegoCraps(jugador, 0, apuesta);  // 0 = intentos ilimitados
                break;
            case 2:
                cout << "Has seleccionado el nivel medio (5 intentos)\n";
                resultado = ejecutarJuegoCraps(jugador, 5, apuesta);
                break;
            case 3:
                cout << "Has seleccionado el nivel difícil (3 intentos)\n";
                resultado = ejecutarJuegoCraps(jugador, 3, apuesta);
                break;
        }

        jugador.dinero += resultado;       // Actualizo dinero según resultado
        guardarSaldo(jugador.nombre, jugador.dinero);  // Guardo saldo en archivo
        jugador.actualizarEstadisticas();  // Actualizo estadísticas internas

        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                ¿Desea seguir jugando?             ║\n";
        cout << "║                                                   ║\n";
        cout << "║   Si (S)                               No (N)     ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";

        cin >> jugarOtraVez;
         limpiarConsola();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpio buffer para evitar errores

    } while (tolower(jugarOtraVez) == 's');  // Repite mientras conteste 's'
}

#endif // CRAPS_GAME_H  
