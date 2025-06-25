#ifndef PLAYER_DATA_H 
#define PLAYER_DATA_H 

#include <string>     // Incluyo esto porque voy a usar objetos tipo string
#include <fstream>    // Lo necesito para leer y escribir en archivos
#include <iostream>   // Lo incluyo para depurar o mostrar mensajes si es necesario
#include <cmath>      // Lo uso por si necesito funciones matemáticas como abs
#include <limits>     // Lo uso para manejar límites, como en errores de lectura de archivo

using namespace std; // Uso el espacio de nombres estándar para evitar escribir std:: en todo

// Esta función la uso para guardar movimientos como depósitos o retiros en un archivo de historial
inline void guardarMovimiento(const string& tipoMovimiento, const string& jugador, int cantidad, int dineroRestante) {
    ofstream archivo("./documentos/movimientos.txt", ios::app); // Abro el archivo en modo de añadir al final
    if (archivo.is_open()) { // Verifico que se haya abierto correctamente
        archivo << "Jugador: " << jugador << " | Evento: " << tipoMovimiento
                << " | Cantidad: $" << cantidad
                << " | Dinero restante: $" << dineroRestante << "\n"; // Escribo toda la información del movimiento
    }
}

// Esta función la uso para registrar lo que ocurre en los juegos: si gano, pierdo o empato
inline void guardarJuego(const string& tipoEvento, const string& jugador, int cantidad, int resultado, int dineroRestante) {
    ofstream archivo("./documentos/juegos.txt", ios::app); // Abro el archivo para añadir eventos de juegos
    if (archivo.is_open()) {
        archivo << "Jugador: " << jugador << " | Evento: " << tipoEvento
                << " | Cantidad: $" << cantidad
                << " | Resultado: " << (resultado == 1 ? "Ganó" : (resultado == 0 ? "Perdió" : "Empate"))
                << " | Dinero restante: $" << dineroRestante << "\n"; // Escribo toda la información del evento
    }
}

// Esta función es una envoltura que simplemente llama a guardarMovimiento para registrar un depósito o retiro
inline void registrarMovimientoDinero(const string& tipoMovimiento, const string& jugador, int cantidad, int dineroRestante) {
    guardarMovimiento(tipoMovimiento, jugador, cantidad, dineroRestante); // Llamo directamente a guardarMovimiento
}

// Esta función me permite registrar un resultado de juego (victoria, derrota o empate)
inline void registrarJuego(const string& nombreJuego, const string& jugador, int gananciaPerdida, int dineroRestante) {
    int resultado = (gananciaPerdida > 0) ? 1 : (gananciaPerdida < 0) ? 0 : 2; // Determino si gané, perdí o empaté
    guardarJuego(nombreJuego, jugador, abs(gananciaPerdida), resultado, dineroRestante); // Registro el resultado
}

// Esta función guarda el saldo actual del jugador en su propio archivo de texto
inline void guardarSaldo(const string& jugador, int dinero) {
    ofstream archivo("./documentos/saldo_" + jugador + ".txt"); // Abro el archivo de saldo del jugador
    if (archivo.is_open()) {
        archivo << dinero << "\n"; // Escribo el saldo directamente
    }
}

// Esta función carga el saldo desde el archivo correspondiente al jugador
inline int cargarSaldo(const string& jugador) {
    ifstream archivo("./documentos/saldo_" + jugador + ".txt"); // Abro el archivo del jugador
    if (!archivo.is_open()) return 0; // Si falla al abrir, devuelvo 0

    int dineroGuardado;
    archivo >> dineroGuardado; // Intento leer el saldo
    if (archivo.fail()) return 0; // Si hubo error en la lectura, devuelvo 0
    return dineroGuardado; // Devuelvo el saldo leído
}

// Esta función guarda las estadísticas de juego del jugador en un archivo de texto
inline void guardarEstadisticas(const string& nombre, int jugadas, int ganadas, int perdidas, int empatadas) {
    ofstream archivo("./documentos/estadisticas_" + nombre + ".txt"); // Abro el archivo de estadísticas
    if (archivo.is_open()) {
        archivo << "Partidas jugadas: " << jugadas << "\n";
        archivo << "Partidas ganadas: " << ganadas << "\n";
        archivo << "Partidas perdidas: " << perdidas << "\n";
        archivo << "Partidas empatadas: " << empatadas << "\n"; // Escribo las 4 estadísticas
        archivo.close(); // Cierro el archivo cuando termino
    }
}

// Esta función carga las estadísticas desde el archivo del jugador
inline bool cargarEstadisticas(const string& nombre, int& jugadas, int& ganadas, int& perdidas, int& empatadas) {
    ifstream archivo("./documentos/estadisticas_" + nombre + ".txt"); // Intento abrir el archivo del jugador

    if (!archivo.is_open()) return false; // Si no lo pude abrir, retorno false

    string clave; // Aquí iré leyendo el nombre de cada estadística
    int valor;    // Y aquí guardaré el valor correspondiente

    // Leo el archivo línea por línea
    while (archivo >> ws && getline(archivo, clave, ':')) {
        archivo >> ws; // Elimino espacios en blanco

        if (!(archivo >> valor)) { // Intento leer el número
            archivo.clear(); // Si falló, limpio los flags
            archivo.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignoro el resto de la línea
            continue; // Paso a la siguiente
        }

        // Comparo la clave leída y asigno el valor a la variable correcta
        if (clave == "Partidas jugadas") {
            jugadas = valor;
        } else if (clave == "Partidas ganadas") {
            ganadas = valor;
        } else if (clave == "Partidas perdidas") {
            perdidas = valor;
        } else if (clave == "Partidas empatadas") {
            empatadas = valor;
        }
    }

    archivo.close(); // Cierro el archivo al terminar
    return true; // Devuelvo true porque logré cargar las estadísticas
}

#endif // PLAYER_DATA_H 
