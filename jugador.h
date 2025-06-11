#ifndef JUGADOR_H   // Evita que este archivo se incluya más de una vez en el proyecto
#define JUGADOR_H

#include <string>   // Para usar el tipo string de C++
#include <fstream>  // Para manejar archivos (guardar registros)
#include <iostream> // Para imprimir mensajes en consola
#include <cctype>   // Para funciones que analizan caracteres (como isalpha e isspace)

using namespace std;

// Estructura que representa a un jugador con su nombre y la cantidad de dinero que tiene
struct Jugador {
    string nombre;  // Nombre del jugador
    int dinero;     // Dinero actual del jugador
};

// Función que verifica que el nombre sea válido: solo letras y espacios, no vacío
bool nombreValido(const string& nombre) {
    if (nombre.empty()) return false;  // Si el nombre está vacío, no es válido
    for (char c : nombre) {            // Recorremos cada caracter del nombre
        // Si algún caracter no es letra ni espacio, el nombre es inválido
        if (!isalpha(c) && !isspace(c)) return false;
    }
    return true;  // Si pasa todas las pruebas, el nombre es válido
}

// Función para guardar en un archivo un registro de la partida jugada
// Parámetros:
// juego: nombre del juego (ejemplo: "Ruleta")
// jugador: nombre del jugador
// apuesta: cuánto apostó el jugador
// resultado: 1 para ganancia, 0 para pérdida, 2 para empate
// dineroRestante: cuánto dinero le queda después de la jugada
void guardarRegistro(const string& juego, const string& jugador, int apuesta, int resultado, int dineroRestante) {
    ofstream archivo("registro.txt", ios::app);  // Abrimos el archivo en modo añadir al final
    if (archivo.is_open()) {                      // Verificamos que el archivo se abrió correctamente
        // Escribimos una línea con los datos de la jugada
        archivo << "Jugador: " << jugador << " | Juego: " << juego
                << " | Apuesta: $" << apuesta
                << " | Resultado: " << (resultado == 1 ? "Ganó" : (resultado == 0 ? "Perdió" : "Empate"))
                << " | Dinero restante: $" << dineroRestante << "\n";
        archivo.close();  // Cerramos el archivo para guardar los cambios
    } else {
        cout << "No se pudo guardar el registro.\n";  // Si no se pudo abrir el archivo, mostramos error
    }
}

#endif  // Fin del guardado múltiple del archivo
