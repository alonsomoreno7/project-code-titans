#ifndef JUGADOR_H   
#define JUGADOR_H

#include <string>    // Para manejar texto con la clase string
#include <fstream>   // Para leer y escribir en archivos
#include <iostream>  // Para mostrar mensajes en pantalla
#include <cctype>    // Para funciones que validan caracteres (isalpha, isspace)

using namespace std;

const int MAX_REGISTROS = 100;  // Defino un límite de cuántos movimientos guardaremos en memoria

// Función para verificar que el nombre solo tenga letras y espacios, y que no esté vacío
bool nombreValido(const string& nombre) {
    if (nombre.empty()) return false;  // Si no escribió nada, no es válido
    for (char c : nombre) {
        // Reviso carácter por carácter, si no es letra ni espacio, devuelvo falso
        if (!isalpha(c) && !isspace(c)) return false;
    }
    return true;  // Si pasó todas las pruebas, está bien
}

// Esta función guarda los movimientos (depósitos o retiros) en un archivo llamado movimientos.txt
// Solo registra el tipo de movimiento, quién lo hizo, cuánto y cuánto queda
void guardarMovimiento(const string& tipoMovimiento, const string& jugador, int cantidad, int dineroRestante) {
    ofstream archivo("movimientos.txt", ios::app);  // Abro el archivo para agregar al final (append)
    if (archivo.is_open()) {
        // Escribo la línea con formato legible
        archivo << "Jugador: " << jugador << " | Evento: " << tipoMovimiento
                << " | Cantidad: $" << cantidad
                << " | Dinero restante: $" << dineroRestante << "\n";
        archivo.close();  // Siempre cierro el archivo para guardar cambios
    } else {
        cout << "No se pudo guardar el movimiento.\n";  // Si falla, aviso al usuario
    }
}

// Función para guardar juegos con su resultado (ganó, perdió, empate) en juegos.txt
void guardarJuego(const string& tipoEvento, const string& jugador, int cantidad, int resultado, int dineroRestante) {
    ofstream archivo("juegos.txt", ios::app);  // Similar al anterior, abro archivo para agregar
    if (archivo.is_open()) {
        archivo << "Jugador: " << jugador << " | Evento: " << tipoEvento
                << " | Cantidad: $" << cantidad
                << " | Resultado: " << (resultado == 1 ? "Ganó" : (resultado == 0 ? "Perdió" : "Empate"))
                << " | Dinero restante: $" << dineroRestante << "\n";
        archivo.close();
    } else {
        cout << "No se pudo guardar el juego.\n";  // Aviso si algo salió mal
    }
}

// Aquí simplifico el llamado para registrar un movimiento de dinero, solo llama a guardarMovimiento
void registrarMovimientoDinero(const string& tipoMovimiento, const string& jugador, int cantidad, int dineroRestante) {
    guardarMovimiento(tipoMovimiento, jugador, cantidad, dineroRestante);
}

// Función para registrar el resultado de un juego: gano, perdió o empate según ganancia/perdida
void registrarJuego(const string& nombreJuego, const string& jugador, int gananciaPerdida, int dineroRestante) {
    int resultado;
    if (gananciaPerdida > 0) resultado = 1;    // Si ganó dinero, resultado 1
    else if (gananciaPerdida < 0) resultado = 0; // Si perdió, 0
    else resultado = 2;                         // Si no ganó ni perdió, empate (2)
    guardarJuego(nombreJuego, jugador, abs(gananciaPerdida), resultado, dineroRestante);
}

// Guardo el saldo actual del jugador en un archivo para poder recuperarlo después
void guardarSaldo(const string& jugador, int dinero) {
    ofstream archivo("saldo_jugador.txt");  // Abro el archivo para sobrescribir
    if (archivo.is_open()) {
        archivo << jugador << "\n" << dinero << "\n";  // Guardo el nombre y el dinero en líneas separadas
        archivo.close();
    } else {
        cout << "No se pudo guardar el saldo.\n";
    }
}

// Esta función intenta cargar el saldo guardado de un jugador, si no lo encuentra devuelve -1
int cargarSaldo(const string& jugador) {
    ifstream archivo("saldo_jugador.txt");  // Abro el archivo para leer
    string nombreArchivo;
    int dineroGuardado;

    if (archivo.is_open()) {
        getline(archivo, nombreArchivo);  // Leo el nombre guardado
        archivo >> dineroGuardado;         // Leo el saldo guardado
        archivo.close();
        if (nombreArchivo == jugador) {   // Solo devuelvo el saldo si el nombre coincide
            return dineroGuardado;
        }
    }
    return -1; // Si no existe archivo o nombre no coincide, retorno -1 para indicar error
}

// Estructura para guardar cada movimiento con una descripción sencilla
struct Registro {
    string descripcion;  // Texto corto explicando el movimiento (ej: "Depósito $50")
};

// Representa al jugador con su nombre, dinero y un historial de movimientos en memoria
struct Jugador {
    string nombre;        // Nombre del jugador
    int dinero = 0;       // Dinero actual, empieza en 0

    Registro historial[MAX_REGISTROS]; // Aquí guardo los últimos movimientos en memoria
    int numRegistros = 0;               // Cuántos movimientos tengo guardados

    // Agrega un nuevo movimiento al historial (solo si hay espacio)
    void agregarRegistro(const string& texto) {
        if (numRegistros < MAX_REGISTROS) {
            historial[numRegistros].descripcion = texto;
            numRegistros++;
        }
    }

    // Función para depositar dinero: suma al saldo y registra el movimiento
    void depositar(int cantidad) {
        if (cantidad > 0) {
            dinero += cantidad;  // Sumo el dinero
            cout << "Has depositado $" << cantidad << ". Saldo actual: $" << dinero << "\n";

            agregarRegistro("Depósito: $" + to_string(cantidad));  // Guardo en historial memoria
            registrarMovimientoDinero("Depósito", nombre, cantidad, dinero);  // Guardo en archivo

            guardarSaldo(nombre, dinero);  // Actualizo saldo persistente
        } else {
            cout << "No puedes depositar una cantidad negativa o cero.\n";  // Validación simple
        }
    }

    // Función para retirar dinero, solo si hay suficiente saldo, y registra el movimiento
    bool retirar(int cantidad) {
        if (cantidad > 0) {
            if (cantidad <= dinero) {  // Si alcanza el saldo
                dinero -= cantidad;    // Resto el dinero
                cout << "Has retirado $" << cantidad << ". Saldo actual: $" << dinero << "\n";

                agregarRegistro("Retiro: $" + to_string(cantidad));  // Guardo en historial memoria
                registrarMovimientoDinero("Retiro", nombre, cantidad, dinero);  // Guardo en archivo

                guardarSaldo(nombre, dinero);  // Actualizo saldo persistente

                return true;  // Indico que fue exitoso
            } else {
                cout << "No tienes suficiente dinero para retirar esa cantidad.\n";
                return false; // No alcanza saldo
            }
        } else {
            cout << "Cantidad inválida para retirar.\n";
            return false;  // Cantidad negativa o cero
        }
    }

    // Muestra en pantalla el historial de movimientos guardados en memoria
    void mostrarHistorial() {
        cout << "\nAquí está tu historial de movimientos:\n";
        if (numRegistros == 0) {
            cout << "Aún no hay movimientos registrados.\n";
        } else {
            for (int i = 0; i < numRegistros; i++) {
                cout << (i + 1) << ") " << historial[i].descripcion << endl;
            }
        }
    }
};

#endif  // Fin de la protección contra inclusiones múltiples
