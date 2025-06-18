#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <windows.h>

using namespace std;

struct Jugador {
    string nombre;
    int dinero;
};

int generarCarta() {
    int carta = rand() % 13 + 1;
    if (carta > 10) return 10;
    if (carta == 1) return 11; // As como 11
    return carta;
}

string obtenerPaloAleatorio() {
    string palos[] = {"♠", "♥", "♦", "♣"};
    return palos[rand() % 4];
}

string ajustarValor(int valor) {
    if (valor == 11) return "A";
    if (valor == 10) return "10";
    if (valor == 9) return "9";
    if (valor == 8) return "8";
    if (valor == 7) return "7";
    if (valor == 6) return "6";
    if (valor == 5) return "5";
    if (valor == 4) return "4";
    if (valor == 3) return "3";
    if (valor == 2) return "2";
    return "?";
}

void mostrarCartasASCII(int valores[], string palos[], int cantidad) {
    string lineas[7];
    for (int i = 0; i < cantidad; i++) {
        string valor = ajustarValor(valores[i]);
        string izq = valor.length() == 1 ? valor + " " : valor;
        string der = valor.length() == 1 ? " " + valor : valor;

        lineas[0] += "┌─────────┐ ";
        lineas[1] += "│" + izq + "       │ ";
        lineas[2] += "│         │ ";
        lineas[3] += "│    " + palos[i] + "    │ ";
        lineas[4] += "│         │ ";
        lineas[5] += "│       " + der + "│ ";
        lineas[6] += "└─────────┘ ";
    }

    for (int i = 0; i < 7; i++) {
        cout << lineas[i] << endl;
    }
}

int calcularPuntaje(int cartas[], int numCartas) {
    int suma = 0, ases = 0;
    for (int i = 0; i < numCartas; i++) {
        suma += cartas[i];
        if (cartas[i] == 11) ases++;
    }
    while (suma > 21 && ases > 0) {
        suma -= 10;
        ases--;
    }
    return suma;
}

void jugarBlackjack(Jugador &jugador) {
    if (jugador.dinero <= 0) {
        cout << "No tienes dinero para jugar Blackjack.\n";
        return;
    }

    int apuesta;
    cout << "Tu dinero actual es $" << jugador.dinero << ". Ingresa tu apuesta: $";
    cin >> apuesta;

    if (cin.fail() || apuesta <= 0 || apuesta > jugador.dinero) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Apuesta inválida.\n";
        return;
    }

    int valoresJugador[10], valoresDealer[10];
    string palosJugador[10], palosDealer[10];
    int numJugador = 0, numDealer = 0;

    // Repartir 2 cartas a jugador y dealer
    for (int i = 0; i < 2; i++) {
        valoresJugador[numJugador] = generarCarta();
        palosJugador[numJugador++] = obtenerPaloAleatorio();

        valoresDealer[numDealer] = generarCarta();
        palosDealer[numDealer++] = obtenerPaloAleatorio();
    }

    cout << "\nTus cartas:\n";
    mostrarCartasASCII(valoresJugador, palosJugador, numJugador);
    cout << "(Total: " << calcularPuntaje(valoresJugador, numJugador) << ")\n";

    cout << "\nCarta visible del dealer:\n";
    mostrarCartasASCII(valoresDealer, palosDealer, 1);

    char opcion;
    while (true) {
        int puntaje = calcularPuntaje(valoresJugador, numJugador);
        if (puntaje > 21) {
            cout << "\nTe pasaste de 21. Perdiste.\n";
            jugador.dinero -= apuesta;
            return;
        }

        cout << "\n¿Quieres otra carta? (s/n): ";
        cin >> opcion;
        if (tolower(opcion) != 's') break;

        valoresJugador[numJugador] = generarCarta();
        palosJugador[numJugador++] = obtenerPaloAleatorio();

        cout << "\nTus cartas:\n";
        mostrarCartasASCII(valoresJugador, palosJugador, numJugador);
        cout << "(Total: " << calcularPuntaje(valoresJugador, numJugador) << ")\n";
    }

    cout << "\nTurno del dealer...\n";
    mostrarCartasASCII(valoresDealer, palosDealer, numDealer);
    cout << "(Total: " << calcularPuntaje(valoresDealer, numDealer) << ")\n";

    while (calcularPuntaje(valoresDealer, numDealer) < 17) {
        valoresDealer[numDealer] = generarCarta();
        palosDealer[numDealer++] = obtenerPaloAleatorio();

        cout << "\nDealer toma carta:\n";
        mostrarCartasASCII(valoresDealer, palosDealer, numDealer);
        cout << "(Total: " << calcularPuntaje(valoresDealer, numDealer) << ")\n";
    }

    int puntajeJugador = calcularPuntaje(valoresJugador, numJugador);
    int puntajeDealer = calcularPuntaje(valoresDealer, numDealer);

    if (puntajeDealer > 21 || puntajeJugador > puntajeDealer) {
        cout << "\n¡Ganaste!\n";
        jugador.dinero += apuesta;
    } else if (puntajeJugador == puntajeDealer) {
        cout << "\nEmpate. No ganas ni pierdes.\n";
    } else {
        cout << "\nPerdiste.\n";
        jugador.dinero -= apuesta;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(0));
    Jugador jugador;
    cout << "Ingrese su nombre: ";
    getline(cin, jugador.nombre);
    jugador.dinero = 100;

    char seguir;
    do {
        jugarBlackjack(jugador);
        if (jugador.dinero <= 0) {
            cout << "\nTe has quedado sin dinero. Fin del juego.\n";
            break;
        }
        cout << "\n¿Quieres seguir jugando? (s/n): ";
        cin >> seguir;
    } while (tolower(seguir) == 's');

    cout << "\nGracias por jugar, " << jugador.nombre << ". Terminaste con $" << jugador.dinero << ".\n";
    return 0;
}