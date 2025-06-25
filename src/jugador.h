#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <iostream>
#include "gameConstants.h" // Uso constantes como MAX_REGISTROS y Registro
#include "playerData.h"    // Para funciones de guardar y cargar datos del jugador

using namespace std;

// Aquí defino el array de posiciones para la ruleta que usaré en el programa,
// solo lo defino una vez aquí para evitar múltiples definiciones
Posicion posiciones[NUMEROS];

// Defino la estructura Jugador con toda la información que necesito guardar sobre cada jugador
struct Jugador {
    string nombre;                // Nombre del jugador
    int dinero = 0;               // Dinero actual que tiene el jugador
    Registro historial[MAX_REGISTROS]; // Historial de movimientos y eventos
    int numRegistros = 0;         // Cuántos registros tiene el historial

    // Estadísticas del jugador para los juegos
    int partidasJugadas = 0;
    int partidasGanadas = 0;
    int partidasPerdidas = 0;
    int partidasEmpatadas = 0;

    // Actualizo las estadísticas del jugador guardándolas en disco o base
    inline void actualizarEstadisticas() {
        guardarEstadisticas(nombre, partidasJugadas, partidasGanadas, partidasPerdidas, partidasEmpatadas);
    }

    // Cargo las estadísticas del jugador desde archivo o base de datos
    inline void cargarEstadisticasJugador() {
        int j, g, p, e;
        if (cargarEstadisticas(nombre, j, g, p, e)) {
            partidasJugadas = j;
            partidasGanadas = g;
            partidasPerdidas = p;
            partidasEmpatadas = e;
        }
    }

    // Muestro las estadísticas del jugador en consola
    inline void mostrarEstadisticas() {
        cargarEstadisticasJugador(); // Primero cargo para mostrar datos actualizados
        cout << "\nEstadísticas del jugador:\n";
        cout << "Partidas jugadas: " << partidasJugadas << "\n";
        cout << "Partidas ganadas: " << partidasGanadas << "\n";
        cout << "Partidas perdidas: " << partidasPerdidas << "\n";
        cout << "Partidas empatadas: " << partidasEmpatadas << "\n";
    }

    // Agrego un nuevo registro al historial del jugador (si hay espacio)
    inline void agregarRegistro(const string& texto) {
        if (numRegistros < MAX_REGISTROS) {
            historial[numRegistros++].descripcion = texto;
        }
    }

    // Método para que el jugador deposite dinero
    inline void depositar(int cantidad) {
        if (cantidad > 0) {
            dinero += cantidad; // Aumento saldo
            cout << "Has depositado $" << cantidad << ". Saldo actual: $" << dinero << "\n";
            agregarRegistro("Depósito: $" + to_string(cantidad)); // Registro el movimiento
            registrarMovimientoDinero("Depósito", nombre, cantidad, dinero);
            guardarSaldo(nombre, dinero); // Guardo saldo actualizado
        } else {
            cout << "No puedes depositar una cantidad negativa o cero.\n";
        }
    }

    // Método para que el jugador retire dinero
    inline bool retirar(int cantidad) {
        if (cantidad > 0 && cantidad <= dinero) {
            dinero -= cantidad; // Disminuyo saldo
            cout << "Has retirado $" << cantidad << ". Saldo actual: $" << dinero << "\n";
            agregarRegistro("Retiro: $" + to_string(cantidad)); // Registro movimiento
            registrarMovimientoDinero("Retiro", nombre, cantidad, dinero);
            guardarSaldo(nombre, dinero); // Guardo saldo actualizado
            return true; // Retiro exitoso
        } else {
            cout << "Retiro inválido o saldo insuficiente.\n";
            return false; // Retiro fallido
        }
    }

    // Método para mostrar el historial completo del jugador
    inline void mostrarHistorial() {
        cout << "\nHistorial:\n";
        if (numRegistros == 0) cout << "Sin movimientos registrados.\n";
        else 
            for (int i = 0; i < numRegistros; ++i)
                cout << (i + 1) << ") " << historial[i].descripcion << "\n";
    }
};

#endif // JUGADOR_H
