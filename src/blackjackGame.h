#ifndef BLACKJACK_GAME_H         
#define BLACKJACK_GAME_H          

#include <string>                 // Uso strings para manejar texto en el juego
#include <iostream>               // Uso para imprimir y leer datos por consola (cout, cin)
#include <cstdlib>                // Uso para generar números aleatorios con rand()
#include <cctype>                 // Uso para funciones de caracteres como tolower()
#include <limits>                 // Uso para manejar límites y limpiar buffer en entradas
#include "gameConstants.h"        // Uso constantes como NORMAL, MEDIO y DIFICIL para dificultad
#include "utils.h"                // Uso funciones auxiliares como limpiarConsola()
#include "playerData.h"           // Uso funciones para registrar juego y guardar saldo
#include "jugador.h"              // Uso la estructura Jugador con sus atributos y métodos

using namespace std;             // Para no tener que escribir std:: en cada uso

// Función para generar una carta aleatoria según reglas de Blackjack
inline int generarCarta() {
    int carta = rand() % 13 + 1;  // Genero un número entre 1 y 13 (las cartas)
    if (carta > 10) return 10;    // Las cartas J, Q, K valen 10
    if (carta == 1) return 11;    // El As vale 11 inicialmente
    return carta;                 // Las demás cartas valen su número
}

// Función para obtener un palo aleatorio para la carta (♠ ♥ ♦ ♣)
inline string obtenerPaloAleatorio() {
    string palos[] = {"♠", "♥", "♦", "♣"};  // Defino los palos
    return palos[rand() % 4];                // Retorno uno al azar
}

// Función para convertir el valor numérico de la carta a su representación textual
inline string ajustarValor(int valor) {
    if (valor == 11) return "A";  // As
    if (valor == 10) return "10"; // Diez
    if (valor == 9) return "9";
    if (valor == 8) return "8";
    if (valor == 7) return "7";
    if (valor == 6) return "6";
    if (valor == 5) return "5";
    if (valor == 4) return "4";
    if (valor == 3) return "3";
    if (valor == 2) return "2";
    return "?";                   // Caso inesperado
}

// Función para mostrar cartas en formato ASCII en varias líneas, de forma visual
inline void mostrarCartasASCII(int valores[], string palos[], int cantidad) {
    string lineas[7];             // Siete líneas para mostrar la "carta"
    for (int i = 0; i < cantidad; i++) {  // Para cada carta
        string valor = ajustarValor(valores[i]);  // Obtengo texto del valor
        string izq = valor.length() == 1 ? valor + " " : valor;  // Ajusto alineación izquierda
        string der = valor.length() == 1 ? " " + valor : valor;  // Ajusto alineación derecha

        lineas[0] += "┌─────────┐ ";                      // Borde superior
        lineas[1] += "│" + izq + "       │ ";           // Valor izquierda
        lineas[2] += "│         │ ";                     // Espacio vacío
        lineas[3] += "│    " + palos[i] + "    │ ";      // Palo centrado
        lineas[4] += "│         │ ";                     // Espacio vacío
        lineas[5] += "│       " + der + "│ ";           // Valor derecha
        lineas[6] += "└─────────┘ ";                     // Borde inferior
    }

    for (int i = 0; i < 7; i++) {       // Imprimo las siete líneas formando las cartas
        cout << lineas[i] << endl;
    }
}

// Función para calcular el puntaje actual de un conjunto de cartas,
// considerando que los ases pueden valer 1 u 11 según convenga
inline int calcularPuntaje(int cartas[], int numCartas) {
    int suma = 0, ases = 0;        // Sumo cartas y cuento ases
    for (int i = 0; i < numCartas; i++) {
        suma += cartas[i];          // Sumo el valor de cada carta
        if (cartas[i] == 11) ases++;  // Cuento los ases que valen 11
    }
    while (suma > 21 && ases > 0) { // Si me paso de 21 y tengo ases
        suma -= 10;                 // Cambio un as de 11 a 1 (resto 10)
        ases--;                    // Cuento ese as como 1 ahora
    }
    return suma;                   // Retorno el puntaje ajustado
}

// Función para calcular el puntaje actual de un conjunto de cartas,
// considerando que los ases pueden valer 1 u 11 según convenga
inline void jugarBlackjack(Jugador& jugador) {
    char jugarDeNuevo;  // Variable para preguntar si el jugador quiere volver a jugar

    do {
            if (jugador.dinero <= 0) {  // Verifico que tenga dinero para apostar
        cout << "No tienes dinero para jugar Blackjack.\n";  // Mensaje si no tiene saldo
        return;                  // Salgo de la función porque no puede jugar
    }

    int apuesta;  // Variable para la apuesta del jugador
    cout << "Tu dinero actual es $" << jugador.dinero << ". Ingresa tu apuesta (mínimo $10, máximo $500): $";

    while (true) {  // Validación de la apuesta
        cin >> apuesta;  // Leo la apuesta del jugador
        if (cin.fail() || apuesta < 10 || apuesta > 500 || apuesta > jugador.dinero) {  // Verifico límites y errores
            cin.clear();  // Limpio el estado de error de cin
            cin.ignore(1000, '\n');  // Ignoro buffer de entrada
            cout << "Apuesta inválida. Debe ser entre $10 y $500 y no puede exceder tu saldo actual.\n";
            cout << "Tu dinero actual es $" << jugador.dinero << ". Ingresa tu apuesta: $";
            continue;  // Vuelvo a pedir apuesta
        }
        break;  // Salgo del bucle si la apuesta es válida
    }
    jugador.partidasJugadas++;  // Incremento contador de partidas jugadas

    int nivelDificultad;  // Variable para la dificultad que escogerá el jugador
    while (true) {  // Bucle para pedir y validar dificultad
         limpiarConsola();
        cout << "======================================\n";
        cout << "     Selecciona el nivel de dificultad\n";
        cout << "--------------------------------------\n";
        cout << "  1. Normal  (2 cartas)\n";
        cout << "  2. Medio   (3 cartas)\n";
        cout << "  3. Difícil (4 cartas)\n";
        cout << "======================================\n";
        cout << "Opción: ";

        cin >> nivelDificultad;  // Leo opción

        if (!cin.fail() && nivelDificultad >= 1 && nivelDificultad <= 3) {  // Si es válida
            limpiarConsola();  // Limpio pantalla para mejor presentación
            cout << "Has seleccionado el nivel ";
            if (nivelDificultad == 1) cout << "Normal.\n";
            else if (nivelDificultad == 2) cout << "Medio.\n";
            else cout << "Difícil.\n";
            break;  // Salgo del bucle
        }

        cin.clear();  // Limpio errores de entrada
        cin.ignore(1000, '\n');  // Ignoro buffer
        limpiarConsola();  // Limpio consola
        cout << "Entrada inválida. Por favor ingresa un número del 1 al 3.\n\n";  // Mensaje error
    }

    int cartasIniciales = NORMAL + (nivelDificultad - 1);  // Calculo cuántas cartas iniciales tocarán según dificultad

    int valoresJugador[10], valoresDealer[10];  // Arrays para guardar valores de cartas jugador y dealer
    string palosJugador[10], palosDealer[10];   // Arrays para guardar palos de cartas jugador y dealer
    int numJugador = 0, numDealer = 0;           // Contadores de cartas actuales de jugador y dealer

    // Reparto cartas iniciales tanto al jugador como al dealer
    for (int i = 0; i < cartasIniciales; i++) {
        valoresJugador[numJugador] = generarCarta();           // Genero carta para jugador
        palosJugador[numJugador++] = obtenerPaloAleatorio();   // Genero palo para jugador

        valoresDealer[numDealer] = generarCarta();             // Genero carta para dealer
        palosDealer[numDealer++] = obtenerPaloAleatorio();     // Genero palo para dealer
    }

    cout << "\nTus cartas:\n";  // Muestro las cartas del jugador
    mostrarCartasASCII(valoresJugador, palosJugador, numJugador);
    cout << "(Total: " << calcularPuntaje(valoresJugador, numJugador) << ")\n";  // Muestro puntaje

    cout << "\nCarta visible del dealer:\n";  // Muestro solo una carta del dealer (la visible)
    mostrarCartasASCII(valoresDealer, palosDealer, 1);

    char opcion;  // Variable para que el jugador decida si quiere carta extra
    while (true) {
        int puntaje = calcularPuntaje(valoresJugador, numJugador);  // Calculo puntaje actual del jugador
        if (puntaje > 21) {  // Si se pasa de 21, pierde inmediatamente
            cout << "\nTe pasaste de 21. Perdiste.\n";
            jugador.dinero -= apuesta;  // Resto la apuesta del saldo
            registrarJuego("Blackjack", jugador.nombre, -apuesta, jugador.dinero);  // Registro pérdida
            guardarSaldo(jugador.nombre, jugador.dinero);  // Guardo saldo actualizado
            jugador.partidasPerdidas++;  // Incremento partidas perdidas
            jugador.actualizarEstadisticas();  // Actualizo estadísticas del jugador
            return;  // Termino la función (partida finalizada)
        }

        cout << "\n¿Quieres otra carta? (s/n): ";  // Pregunto si quiere carta extra
        cin >> opcion;
        if (tolower(opcion) != 's') break;  // Si no es 's', salgo del bucle

        valoresJugador[numJugador] = generarCarta();           // Agrego carta extra
        palosJugador[numJugador++] = obtenerPaloAleatorio();

        cout << "\nTus cartas:\n";  // Muestro cartas actualizadas
        mostrarCartasASCII(valoresJugador, palosJugador, numJugador);
        cout << "(Total: " << calcularPuntaje(valoresJugador, numJugador) << ")\n";  // Muestro nuevo puntaje
    }

    cout << "\nTurno del dealer...\n";  // Ahora juega el dealer
    mostrarCartasASCII(valoresDealer, palosDealer, numDealer);
    cout << "(Total: " << calcularPuntaje(valoresDealer, numDealer) << ")\n";

    // Dealer debe tomar cartas hasta alcanzar al menos 17 puntos
    while (calcularPuntaje(valoresDealer, numDealer) < 17) {
        valoresDealer[numDealer] = generarCarta();          // Dealer toma carta
        palosDealer[numDealer++] = obtenerPaloAleatorio();

        cout << "\nDealer toma carta:\n";  // Muestro cartas del dealer actualizadas
        mostrarCartasASCII(valoresDealer, palosDealer, numDealer);
        cout << "(Total: " << calcularPuntaje(valoresDealer, numDealer) << ")\n";
    }

    int puntajeJugador = calcularPuntaje(valoresJugador, numJugador);  // Puntaje final jugador
    int puntajeDealer = calcularPuntaje(valoresDealer, numDealer);     // Puntaje final dealer

    // Determino resultado final comparando puntajes
    if (puntajeDealer > 21 || puntajeJugador > puntajeDealer) {  // Si dealer se pasa o jugador gana
        cout << "\n¡Ganaste!\n";
        jugador.dinero += apuesta;  // Aumento saldo con la apuesta ganada
        jugador.partidasGanadas++;  // Incremento partidas ganadas
        registrarJuego("Blackjack", jugador.nombre, apuesta, jugador.dinero);  // Registro victoria
    } else if (puntajeJugador == puntajeDealer) {  // Empate
        cout << "\nEmpate. No ganas ni pierdes.\n";
        registrarJuego("Blackjack", jugador.nombre, 0, jugador.dinero);  // Registro empate
        jugador.partidasEmpatadas++;  // Incremento contador de empates
    } else {  // Caso contrario, pierde jugador
        cout << "\nPerdiste.\n";
        jugador.dinero -= apuesta;  // Resto apuesta
        registrarJuego("Blackjack", jugador.nombre, -apuesta, jugador.dinero);  // Registro pérdida
        jugador.partidasPerdidas++;  // Incremento partidas perdidas
    }

    guardarSaldo(jugador.nombre, jugador.dinero);  // Guardo saldo actualizado al final
    jugador.actualizarEstadisticas();  // Actualizo estadísticas internas del jugador


        // Pregunto si quiere volver a jugar
        cout << "\n¿Quieres jugar otra vez al Blackjack? (s/n): ";
        cin >> jugarDeNuevo;
        limpiarConsola();

    } while (tolower(jugarDeNuevo) == 's');
}


#endif // BLACKJACK_GAME_H  

