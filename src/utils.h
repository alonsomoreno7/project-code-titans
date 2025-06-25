#ifndef UTILS_H
#define UTILS_H

// Incluyo <string> para manejar cadenas de texto fácilmente con std::string
#include <string>

// Incluyo <algorithm> para usar funciones útiles como std::transform que me ayuda a convertir texto a minúsculas
#include <algorithm>

// Incluyo <cctype> para usar funciones de caracteres, como convertir a minúsculas (::tolower), validar letras (isalpha) o espacios (isspace)
#include <cctype>

// Incluyo <iostream> para mostrar mensajes en consola y leer entradas (cout y cin)
#include <iostream>

// Incluyo <limits> para acceder a límites en entradas de datos (como numeric_limits), útil para limpiar buffer si fuera necesario
#include <limits>

// Incluyo <cstdlib> para usar funciones del sistema como system(), que me sirve para limpiar la consola
#include <cstdlib>

// Incluyo condicionalmente dependiendo del sistema operativo:
// - Si estoy en Windows (<windows.h>), uso Sleep() para pausar la ejecución en milisegundos
// - Si estoy en Linux/Mac (<unistd.h>), uso usleep() para pausar en microsegundos
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Función que uso para convertir cualquier cadena a minúsculas, así evito problemas de mayúsculas o minúsculas al comparar texto
inline string toLower(const string &s) {
   string res = s; // Copio la cadena original para no alterarla directamente
    transform(res.begin(), res.end(), res.begin(), ::tolower); // Aplico tolower a cada carácter
    return res; // Devuelvo la cadena transformada
}

// Función que uso para eliminar espacios en blanco al inicio y al final de una cadena, para limpiar entradas del usuario y evitar errores
inline string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r"); // Encuentro el primer carácter que no sea espacio
    if (first == string::npos) return ""; // Si solo había espacios, devuelvo cadena vacía
    size_t last = str.find_last_not_of(" \t\n\r"); // Encuentro el último carácter que no sea espacio
    return str.substr(first, (last - first + 1)); // Retorno solo la parte que no tiene espacios afuera
}

// Función que uso para normalizar texto: elimino todos los espacios y convierto todo a minúsculas.
// Esto me sirve para comparar cadenas ignorando espacios y mayúsculas/minúsculas
inline string normalizar(const string& texto) {
    string limpio;
    for (char c : texto) {
        if (!isspace(c))  // Solo agrego caracteres que no sean espacios
            limpio += tolower(c); // Convierto a minúsculas
    }
    return limpio;
}

// Función que valida que el nombre solo contenga letras y espacios
inline bool nombreValido(const string& nombre) {
    for (char c : nombre) {
        if (!isalpha(c) && !isspace(c)) {
            return false;  // Si no es letra ni espacio, el nombre no es válido
        }
    }
    return !nombre.empty(); // El nombre no debe estar vacío
}


// Función para preguntarle al jugador si quiere seguir jugando, aceptando respuestas "sí", "si" o "no" (sin importar mayúsculas)
inline bool preguntarSeguir() {
    string resp;
    while (true) {
        cout << "\n¿Querés seguir jugando? (sí / no): ";
        cin >> resp;
        resp = toLower(resp); // Normalizo para facilitar la comparación
        if (resp == "si" || resp == "sí") return true; // Si dice sí, retorno true
        else if (resp == "no") return false; // Si dice no, retorno false
        else cout << "Respuesta inválida. Por favor, responde 'sí' o 'no'.\n"; // Si responde mal, aviso y repito
    }
}

// Funciones para pausar la ejecución o limpiar la consola, adaptadas al sistema operativo
#ifdef _WIN32
inline void esperarMs(int ms) { Sleep(ms); } // En Windows uso Sleep que recibe milisegundos
inline void limpiarConsola() { system("cls"); } // Limpio pantalla con comando cls
#else
inline void esperarMs(int ms) { usleep(ms * 1000); } // En Linux/Mac uso usleep que recibe microsegundos, por eso multiplico por 1000
inline void limpiarConsola() { cout << "\033[2J\033[H"; } // Limpio pantalla con secuencia ANSI para terminal
#endif

#endif // UTILS_H
