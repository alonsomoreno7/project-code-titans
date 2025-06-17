#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include <cstdlib>   // Para usar rand()
#include <ctime>     // Para usar time() y así inicializar rand()
#include <limits>    // Para limpiar buffer con cin.ignore()

using namespace std;

const int MAX_REGISTROS = 100;  // Defino un máximo de registros para el historial del jugador

// ----------- Validación del nombre -----------

// Esta función valida que el nombre solo tenga letras y espacios
bool nombreValido(const string& nombre) {
    if (nombre.empty()) return false;  // No acepto nombres vacíos
    for (char c : nombre) {
        if (!isalpha(c) && !isspace(c)) return false;  // Solo letras y espacios permitidos
    }
    return true;
}

// ----------- Gestión de usuarios -----------

// Verifico si el usuario ya está registrado en el archivo usuarios.txt
bool existeUsuario(const string& nombre) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) return false;  // Si no puedo abrir el archivo, asumo que no existe usuario

    string linea;
    while (getline(archivo, linea)) {
        if (linea == nombre) return true;  // Si encuentro el nombre en alguna línea, ya existe
        // Ignoro las siguientes 2 líneas (contraseña y código) porque cada usuario ocupa 3 líneas
        getline(archivo, linea);
        getline(archivo, linea);
    }
    return false;  // No encontré el usuario
}

// Guardo un nuevo usuario en usuarios.txt (nombre, contraseña y código de recuperación)
void guardarUsuario(const string& nombre, const string& password, const string& codigo) {
    ofstream archivo("usuarios.txt", ios::app);  // Abro en modo agregar (append)
    if (archivo.is_open()) {
        archivo << nombre << "\n" << password << "\n" << codigo << "\n";
    }
}

// Genero un código numérico de recuperación aleatorio, por defecto de 6 dígitos
string generarCodigoRecuperacion(int longitud = 6) {
    string codigo;
    for (int i = 0; i < longitud; ++i)
        codigo += to_string(rand() % 10);  // Agrego un dígito aleatorio (0-9)
    return codigo;
}

// Registro un nuevo usuario pidiendo nombre y contraseña, valido y verifico duplicados
bool registrarUsuario() {
    string nombre, password;

    cout << "\n=== Registro de nuevo jugador ===\n";
    do {
        cout << "Nombre de usuario: ";
        getline(cin, nombre);

        if (!nombreValido(nombre)) {
            cout << "Nombre inválido. Solo letras y espacios.\n";
            continue;  // Vuelvo a pedir el nombre
        }

        if (existeUsuario(nombre)) {
            cout << "Ese nombre ya está registrado. Intenta otro.\n";
            nombre.clear();
            continue;
        }
    } while (nombre.empty());  // Mientras el nombre sea inválido o duplicado, sigo pidiendo

    cout << "Crea una contraseña: ";
    getline(cin, password);

    string codigo = generarCodigoRecuperacion();
    guardarUsuario(nombre, password, codigo);

    cout << "¡Registro exitoso!\n";
    cout << "Tu código de recuperación es: " << codigo << "\nGuárdalo bien.\n";

    return true;
}

// Inicio sesión pidiendo nombre y contraseña, verifico contra archivo usuarios.txt
bool iniciarSesion(string& jugador) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo de usuarios.\n";
        return false;
    }

    string nombre, pass, codigo;
    cout << "\n=== Iniciar sesión ===\n";
    cout << "Nombre de usuario: ";
    getline(cin, jugador);
    cout << "Contraseña: ";
    getline(cin, pass);

    string linea;
    while (getline(archivo, linea)) {
        string u = linea;         // Nombre guardado en archivo
        if (!getline(archivo, pass)) break;   // Contraseña guardada
        if (!getline(archivo, codigo)) break; // Código guardado

        // Aquí comparo nombre y contraseña que ingresó el usuario con las del archivo
        if (u == jugador && pass == pass) {
            cout << "¡Bienvenido, " << jugador << "!\n";
            return true;
        }
    }

    cout << "Credenciales incorrectas.\n";
    jugador.clear();
    return false;
}

// Recupero contraseña usando el código de recuperación
void recuperarContrasena() {
    string nombre, codigoIngresado;
    cout << "\n=== Recuperar Contraseña ===\n";
    cout << "Nombre de usuario: ";
    getline(cin, nombre);
    cout << "Ingresa tu código de recuperación: ";
    getline(cin, codigoIngresado);

    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo de usuarios.\n";
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        string u = linea;
        string p, c;
        if (!getline(archivo, p)) break;
        if (!getline(archivo, c)) break;

        if (u == nombre) {
            if (c == codigoIngresado) {
                cout << "¡Código correcto! Tu contraseña es: " << p << "\n";
                return;
            } else {
                cout << "Código incorrecto.\n";
                return;
            }
        }
    }

    cout << "Usuario no encontrado.\n";
}

// ----------- Movimiento, juegos y saldo -----------

// Registro movimientos de dinero en un archivo para historial general
void guardarMovimiento(const string& tipoMovimiento, const string& jugador, int cantidad, int dineroRestante) {
    ofstream archivo("movimientos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Jugador: " << jugador << " | Evento: " << tipoMovimiento
                << " | Cantidad: $" << cantidad
                << " | Dinero restante: $" << dineroRestante << "\n";
    }
}

// Registro eventos de juegos en un archivo para historial general
void guardarJuego(const string& tipoEvento, const string& jugador, int cantidad, int resultado, int dineroRestante) {
    ofstream archivo("juegos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Jugador: " << jugador << " | Evento: " << tipoEvento
                << " | Cantidad: $" << cantidad
                << " | Resultado: " << (resultado == 1 ? "Ganó" : (resultado == 0 ? "Perdió" : "Empate"))
                << " | Dinero restante: $" << dineroRestante << "\n";
    }
}

// Función auxiliar para registrar movimiento (depósito o retiro)
void registrarMovimientoDinero(const string& tipoMovimiento, const string& jugador, int cantidad, int dineroRestante) {
    guardarMovimiento(tipoMovimiento, jugador, cantidad, dineroRestante);
}

// Registro el resultado de un juego, calculando si ganó, perdió o empató
void registrarJuego(const string& nombreJuego, const string& jugador, int gananciaPerdida, int dineroRestante) {
    int resultado = (gananciaPerdida > 0) ? 1 : (gananciaPerdida < 0) ? 0 : 2;
    guardarJuego(nombreJuego, jugador, abs(gananciaPerdida), resultado, dineroRestante);
}

// Guardo el saldo actual del jugador en un archivo exclusivo para evitar conflictos
void guardarSaldo(const string& jugador, int dinero) {
    ofstream archivo("saldo_" + jugador + ".txt");  // Archivo separado por jugador
    if (archivo.is_open()) {
        archivo << dinero << "\n";
    }
}

// Cargo el saldo guardado para un jugador desde su archivo
int cargarSaldo(const string& jugador) {
    ifstream archivo("saldo_" + jugador + ".txt");
    if (!archivo.is_open()) return 0;

    int dineroGuardado;
    archivo >> dineroGuardado;
    if (archivo.fail()) return 0;  // Si no pudo leer el entero, devuelvo 0
    return dineroGuardado;
}

// ----------- Estructura Jugador -----------

struct Registro {
    string descripcion;  // Texto simple para describir un movimiento o acción
};

struct Jugador {
    string nombre;
    int dinero = 0;
    Registro historial[MAX_REGISTROS];
    int numRegistros = 0;

    // Agrego un nuevo registro al historial si no está lleno
    void agregarRegistro(const string& texto) {
        if (numRegistros < MAX_REGISTROS) {
            historial[numRegistros++].descripcion = texto;
        }
    }

    // Método para depositar dinero, actualizar saldo, guardar registro y archivo
    void depositar(int cantidad) {
        if (cantidad > 0) {
            dinero += cantidad;
            cout << "Has depositado $" << cantidad << ". Saldo actual: $" << dinero << "\n";
            agregarRegistro("Depósito: $" + to_string(cantidad));
            registrarMovimientoDinero("Depósito", nombre, cantidad, dinero);
            guardarSaldo(nombre, dinero);
        } else {
            cout << "No puedes depositar una cantidad negativa o cero.\n";
        }
    }

    // Método para retirar dinero si hay saldo suficiente
    bool retirar(int cantidad) {
        if (cantidad > 0 && cantidad <= dinero) {
            dinero -= cantidad;
            cout << "Has retirado $" << cantidad << ". Saldo actual: $" << dinero << "\n";
            agregarRegistro("Retiro: $" + to_string(cantidad));
            registrarMovimientoDinero("Retiro", nombre, cantidad, dinero);
            guardarSaldo(nombre, dinero);
            return true;
        } else {
            cout << "Retiro inválido o saldo insuficiente.\n";
            return false;
        }
    }

    // Mostrar historial simple por pantalla
    void mostrarHistorial() {
        cout << "\nHistorial:\n";
        if (numRegistros == 0) cout << "Sin movimientos registrados.\n";
        else for (int i = 0; i < numRegistros; ++i)
            cout << (i + 1) << ") " << historial[i].descripcion << "\n";
    }
};

// ----------- Menú -----------

// Mostrar las opciones disponibles para el usuario
inline void mostrarMenu() {
    cout << "\nMenu Principal - Casino Virtual\n";
    cout << "1) Depositar dinero\n";
    cout << "2) Retirar dinero\n";
    cout << "3) Ruleta\n";
    cout << "4) Blackjack\n";
    cout << "5) Tragamonedas\n";
    cout << "6) Craps (Dados)\n";
    cout << "7) Mostrar historial\n";
    cout << "8) Salir\n";
}

// Función principal que maneja el ciclo del juego después de iniciar sesión
inline void iniciar(const string& nombreUsuario) {
    Jugador jugador;
    jugador.nombre = nombreUsuario;
    jugador.dinero = cargarSaldo(nombreUsuario);

    cout << "Hola, " << jugador.nombre << "! Saldo actual: $" << jugador.dinero << "\n";

    int opcion;
    bool jugando = true;
    while (jugando) {
        mostrarMenu();
        cout << "Dinero actual: $" << jugador.dinero << "\n";
        cout << "Elige una opción: ";
        cin >> opcion;

        if (cin.fail()) {  // Si la entrada no es válida (no es número), limpio buffer y pido otra vez
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida.\n";
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpio buffer para evitar problemas con getline más adelante

        switch (opcion) {
            case 1: {
                int cantidad;
                cout << "¿Cuánto deseas depositar? $";
                cin >> cantidad;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                jugador.depositar(cantidad);
                break;
            }
            case 2: {
                int cantidad;
                cout << "¿Cuánto deseas retirar? $";
                cin >> cantidad;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                jugador.retirar(cantidad);
                break;
            }
            case 3: case 4: case 5: case 6:
                if (jugador.dinero <= 0)
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                else
                    cout << "Juego en proceso... (aquí se debe implementar la lógica del juego)\n";
                break;
            case 7:
                jugador.mostrarHistorial();
                break;
            case 8:
                cout << "Gracias por jugar. ¡Hasta luego!\n";
                jugando = false;
                break;
            default:
                cout << "Opción no válida.\n";
        }
        cout << endl;
    }
}

// Menú de inicio que permite iniciar sesión, registrarse o recuperar contraseña
inline void menuInicio() {
    // Inicializo la semilla para números aleatorios para el código de recuperación
    srand(static_cast<unsigned int>(time(nullptr)));

    string nombre;
    bool sesion = false;

    while (!sesion) {
        cout << "\n===== MENU DE INICIO =====\n";
        cout << "1) Iniciar sesión\n";
        cout << "2) Registrarse\n";
        cout << "3) Recuperar contraseña\n";
        cout << "4) Salir\n";
        cout << "==========================\n";
        cout << "Opción: ";
        int opcion;
        cin >> opcion;
        if (cin.fail()) {
        cin.clear();  // Limpia el error
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Descarta basura en el buffer
         cout << "Entrada inválida. Por favor, ingresa un número.\n";
    continue;
}

cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                sesion = iniciarSesion(nombre);
                break;
            case 2:
                registrarUsuario();
                break;
            case 3:
                recuperarContrasena();
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                return;
            default:
                cout << "Opción inválida. Intenta nuevamente.\n";
        }
    }

    iniciar(nombre);  // Una vez que se inicia sesión, paso a la función principal del juego
}

#endif // JUGADOR_H