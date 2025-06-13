#ifndef JUGADOR_H   
#define JUGADOR_H

#include <string>     // Incluyo string para manejar nombres y textos
#include <fstream>    // Incluyo fstream para guardar y leer archivos
#include <iostream>   // Incluyo iostream para mostrar mensajes en consola
#include <cctype>     // Incluyo cctype para validar caracteres (letras y espacios)

using namespace std;

const int MAX_REGISTROS = 100;  // Defino un límite máximo de registros para el historial del jugador

// Función para validar que el nombre solo contenga letras y espacios
bool nombreValido(const string& nombre) {
    if (nombre.empty()) return false;  // Si el nombre está vacío, no es válido
    for (char c : nombre) {
        // Verifico que cada carácter sea una letra o un espacio
        if (!isalpha(c) && !isspace(c)) return false;
    }
    return true;  // Si todos son válidos, regreso true
}

// Función para guardar en un archivo el movimiento de dinero del jugador (depósito o retiro)
void guardarMovimiento(const string& tipoMovimiento, const string& jugador, int cantidad, int dineroRestante) {
    ofstream archivo("movimientos.txt", ios::app);  // Abro el archivo en modo append para no sobrescribir
    if (archivo.is_open()) {
        // Escribo la información del movimiento con formato claro
        archivo << "Jugador: " << jugador << " | Evento: " << tipoMovimiento
                << " | Cantidad: $" << cantidad
                << " | Dinero restante: $" << dineroRestante << "\n";
        archivo.close();  // Cierro el archivo para guardar cambios
    } else {
        // Mensaje de error si no se pudo abrir el archivo
        cout << "No se pudo guardar el movimiento.\n";
    }
}

// Función para guardar en un archivo los resultados de un juego (ganó, perdió, empate)
void guardarJuego(const string& tipoEvento, const string& jugador, int cantidad, int resultado, int dineroRestante) {
    ofstream archivo("juegos.txt", ios::app);  // Abro el archivo juegos.txt para agregar datos
    if (archivo.is_open()) {
        // Escribo datos del juego con formato legible
        archivo << "Jugador: " << jugador << " | Evento: " << tipoEvento
                << " | Cantidad: $" << cantidad
                << " | Resultado: " << (resultado == 1 ? "Ganó" : (resultado == 0 ? "Perdió" : "Empate"))
                << " | Dinero restante: $" << dineroRestante << "\n";
        archivo.close();
    } else {
        cout << "No se pudo guardar el juego.\n";
    }
}

// Función que llama a guardarMovimiento para registrar cualquier movimiento de dinero
void registrarMovimientoDinero(const string& tipoMovimiento, const string& jugador, int cantidad, int dineroRestante) {
    guardarMovimiento(tipoMovimiento, jugador, cantidad, dineroRestante);
}

// Función para registrar un juego, determina el resultado en base a ganancia o pérdida
void registrarJuego(const string& nombreJuego, const string& jugador, int gananciaPerdida, int dineroRestante) {
    int resultado;
    if (gananciaPerdida > 0) resultado = 1;   // Ganó si ganancia es positiva
    else if (gananciaPerdida < 0) resultado = 0; // Perdió si ganancia es negativa
    else resultado = 2; // Empate si es cero
    // Llamo a guardarJuego con la información procesada
    guardarJuego(nombreJuego, jugador, abs(gananciaPerdida), resultado, dineroRestante);
}

// Función para guardar el saldo actual del jugador en un archivo
void guardarSaldo(const string& jugador, int dinero) {
    ofstream archivo("saldo_jugador.txt");
    if (archivo.is_open()) {
        archivo << jugador << "\n" << dinero << "\n"; // Guardo nombre y dinero en líneas separadas
        archivo.close();
    } else {
        cout << "No se pudo guardar el saldo.\n";
    }
}

// Función para cargar el saldo guardado de un jugador desde archivo
int cargarSaldo(const string& jugador) {
    ifstream archivo("saldo_jugador.txt");
    string nombreArchivo;
    int dineroGuardado;

    if (archivo.is_open()) {
        getline(archivo, nombreArchivo);  // Leo el nombre guardado
        archivo >> dineroGuardado;         // Leo el dinero guardado
        archivo.close();
        if (nombreArchivo == jugador) {   // Verifico que el nombre coincida
            return dineroGuardado;         // Regreso el saldo
        }
    }
    return -1;  // Si no existe o falla, regreso -1
}

// Defino una estructura para guardar cada registro de movimiento o juego
struct Registro {
    string descripcion;  // Solo almaceno una descripción del evento
};

// Defino la estructura Jugador con atributos y métodos
struct Jugador {
    string nombre;             // Nombre del jugador
    int dinero = 0;            // Dinero disponible, inicializado en 0

    Registro historial[MAX_REGISTROS];  // Arreglo para almacenar historial de registros
    int numRegistros = 0;                // Número actual de registros

    // Método para agregar un texto al historial si no está lleno
    void agregarRegistro(const string& texto) {
        if (numRegistros < MAX_REGISTROS) {
            historial[numRegistros].descripcion = texto;
            numRegistros++;
        }
    }

    // Método para depositar dinero en la cuenta del jugador
    void depositar(int cantidad) {
        if (cantidad > 0) {  // Solo acepto depósitos positivos
            dinero += cantidad;  // Sumo al saldo actual
            cout << "Has depositado $" << cantidad << ". Saldo actual: $" << dinero << "\n";

            // Registro el movimiento en el historial interno y archivo
            agregarRegistro("Depósito: $" + to_string(cantidad));
            registrarMovimientoDinero("Depósito", nombre, cantidad, dinero);

            // Guardo el saldo actualizado en archivo
            guardarSaldo(nombre, dinero);
        } else {
            cout << "No puedes depositar una cantidad negativa o cero.\n";
        }
    }

    // Método para retirar dinero del saldo, devuelve true si éxito, false si falla
    bool retirar(int cantidad) {
        if (cantidad > 0) {  // Solo retiros positivos
            if (cantidad <= dinero) {  // Verifico que haya saldo suficiente
                dinero -= cantidad;    // Resto la cantidad del saldo
                cout << "Has retirado $" << cantidad << ". Saldo actual: $" << dinero << "\n";

                // Registro el movimiento en historial y archivo
                agregarRegistro("Retiro: $" + to_string(cantidad));
                registrarMovimientoDinero("Retiro", nombre, cantidad, dinero);

                // Guardo saldo actualizado
                guardarSaldo(nombre, dinero);

                return true;  // Retiro exitoso
            } else {
                cout << "No tienes suficiente dinero para retirar esa cantidad.\n";
                return false; // Saldo insuficiente
            }
        } else {
            cout << "Cantidad inválida para retirar.\n";
            return false; // Cantidad inválida
        }
    }

    // Método para mostrar el historial de movimientos y juegos
    void mostrarHistorial() {
        cout << "\nAquí está tu historial de movimientos:\n";
        if (numRegistros == 0) {
            cout << "Aún no hay movimientos registrados.\n"; // No hay registros
        } else {
            // Recorro y muestro cada registro con índice
            for (int i = 0; i < numRegistros; i++) {
                cout << (i + 1) << ") " << historial[i].descripcion << endl;
            }
        }
    }
};

// Función inline para mostrar el menú principal del casino
inline void mostrarMenu() {
    cout << "\nMenu Principal - Casino Virtual\n";
    cout << "=============================================\n";
    cout << "1) Depositar dinero\n";
    cout << "2) Retirar dinero\n";
    cout << "3) Ruleta\n";
    cout << "4) Blackjack\n";
    cout << "5) Tragamonedas\n";
    cout << "6) Craps (Dados)\n";
    cout << "7) Salir del casino\n";
    cout << "=============================================\n";
}

// Función principal para iniciar el juego y manejar la interacción con el jugador
inline void iniciar() {
    Jugador jugador;     // Creo un objeto Jugador
    jugador.dinero = 0;  // Inicializo el dinero en 0

    // Pido al usuario que ingrese su nombre, y valido que sea correcto
    do {
        cout << "Ingresa tu nombre para comenzar: ";
        getline(cin, jugador.nombre);
        if (!nombreValido(jugador.nombre)) {
            cout << "Nombre inválido. Solo se permiten letras y espacios. Intenta de nuevo.\n";
        }
    } while (!nombreValido(jugador.nombre));

    // Intento cargar el saldo guardado si existe para ese jugador
    int saldoCargado = cargarSaldo(jugador.nombre);
    if (saldoCargado != -1) {
        jugador.dinero = saldoCargado;
    }

    // Saludo inicial e indico saldo
    cout << "¡Hola, " << jugador.nombre << "! Tu saldo inicial es de $" << jugador.dinero << ". Deposita dinero para empezar a jugar.\n";

    bool jugando = true;  // Variable para controlar el bucle principal
    int opcion;           // Opción seleccionada en el menú

    while (jugando) {     // Ciclo hasta que el jugador decida salir
        mostrarMenu();    // Muestro menú cada vez
        cout << "Dinero actual: $" << jugador.dinero << endl;
        cout << "Elige una opción (1-7): ";
        cin >> opcion;

        // Manejo errores si el usuario no ingresa un número válido
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Entrada inválida. Ingresa un número del 1 al 7.\n";
            continue;
        }

        switch (opcion) {
            case 1: {  // Depósito
                int cantidad;
                cout << "¿Cuánto dinero deseas depositar? $";
                cin >> cantidad;
                if (cantidad > 0) {
                    jugador.depositar(cantidad);
                } else {
                    cout << "Cantidad inválida para depositar.\n";
                }
                break;
            }
            case 2: {  // Retiro
                int cantidad;
                cout << "¿Cuánto dinero deseas retirar? $";
                cin >> cantidad;
                if (cantidad > 0) {
                    if (!jugador.retirar(cantidad)) {
                        cout << "No se pudo realizar el retiro.\n";
                    }
                } else {
                    cout << "Cantidad inválida para retirar.\n";
                }
                break;
            }
            case 3:  // Ruleta (solo mensaje por ahora)
                if (jugador.dinero <= 0) {
                    cout << "No tienes saldo suficiente. Deposita dinero para jugar.\n";
                    break;
                }
                cout << "Juego en proceso...\n";
                break;
            case 4:  // Blackjack (solo mensaje por ahora)
                if (jugador.dinero <= 0) {
                    cout << "No tienes saldo suficiente. Deposita dinero para jugar.\n";
                    break;
                }
                cout << "Juego en proceso...\n";
                break;
            case 5:  // Tragamonedas (solo mensaje por ahora)
                if (jugador.dinero <= 0) {
                    cout << "No tienes saldo suficiente. Deposita dinero para jugar.\n";
                    break;
                }
                cout << "Juego en proceso...\n";
                break;
            case 6:  // Craps (Dados) (solo mensaje por ahora)
                if (jugador.dinero <= 0) {
                    cout << "No tienes saldo suficiente. Deposita dinero para jugar.\n";
                    break;
                }
                cout << "Juego en proceso...\n";
                break;
            case 7:  // Salir del casino
                cout << "Gracias por jugar. ¡Hasta luego!\n";
                jugando = false;  // Salgo del bucle
                break;
            default:  // Opción inválida
                cout << "Opción no válida. Intenta otra vez.\n";
        }

        cin.ignore();  // Limpio el buffer para evitar problemas con getline más adelante
        cout << endl;
    }
}

#endif // JUGADOR_H
