#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <fstream>
#include <iostream>
#include <cctype>
#include <cstdlib>   // Para usar rand()
#include <ctime>     // Para usar time() y así inicializar rand()
#include <limits>    // Para limpiar buffer con cin.ignore()
#include <windows.h>

using namespace std;

const int MAX_REGISTROS = 100;  // Defino un máximo de registros para el historial del jugador

// ----------- Validación del nombre -----------//

// Esta función valida que el nombre solo tenga letras y espacios
bool nombreValido(const string& nombre) {
    if (nombre.empty()) return false;  // No acepto nombres vacíos
    for (char c : nombre) {
        if (!isalpha(c) && !isspace(c)) return false;  // Solo letras y espacios permitidos
    }
    return true;
}

// ----------- Función para limpiar espacios  -----------//

// Esta función me sirve para quitar los espacios en blanco al principio y final de una cadena
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
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
    ofstream archivo("usuarios.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "=== Usuario ===\n";
        archivo << "Nombre: " << nombre << "\n";
        archivo << "Contraseña: " << password << "\n";
        archivo << "Código: " << codigo << "\n";
        archivo << "=================\n\n";
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
    // Primero intento abrir el archivo donde están los usuarios
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        // Si no puedo abrirlo, aviso y termino la función
        cout << "Error al abrir archivo de usuarios.\n";
        return false;
    }

    // Le pido al usuario que ingrese su nombre y contraseña
    string nombreIngresado, passIngresada;
    cout << "\n=== Iniciar sesión ===\n";
    cout << "Nombre de usuario: ";
    getline(cin, nombreIngresado);
    cout << "Contraseña: ";
    getline(cin, passIngresada);

    string linea;
    // Empiezo a leer el archivo línea por línea buscando la etiqueta "=== Usuario ==="
    while (getline(archivo, linea)) {
        if (linea == "=== Usuario ===") {
            // Cuando encuentro esa etiqueta, sé que vienen los datos de un usuario
            string nombreArchivo, passArchivo, codigoArchivo;

            // Leo las siguientes líneas para obtener el nombre, contraseña y código
            getline(archivo, linea);
            nombreArchivo = linea.substr(8); // Quito "Nombre: " y me quedo con el nombre

            getline(archivo, linea);
            passArchivo = linea.substr(13); // Quito "Contraseña: " y guardo la contraseña

            getline(archivo, linea);
            codigoArchivo = linea.substr(8); // Quito "Código: " y guardo el código

            // Leo la línea de cierre para avanzar
            getline(archivo, linea);

            // Comparo los datos que ingresó el usuario con los que acabo de leer
            if (nombreArchivo == nombreIngresado && passArchivo == passIngresada) {
                // Si coinciden, le doy la bienvenida y guardo su nombre en 'jugador'
                jugador = nombreIngresado;
                cout << "¡Bienvenido, " << jugador << "!\n";
                return true; // Y retorno que todo salió bien
            }
        }
    }

    // Si llegué hasta aquí, significa que no encontré usuario con esos datos
    cout << "Credenciales incorrectas.\n";
    jugador.clear(); // Limpio el nombre por si acaso
    return false; // Retorno que no se pudo iniciar sesión
}

// Aquí busco si existe un usuario con su respectivo código de recuperación
// Si todo va bien, también recupero la contraseña original
bool verificarCodigoRecuperacion(const string& nombre, const string& codigo, string& password) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) return false; // Si el archivo no se puede abrir, regreso false.

    string linea;
    while (getline(archivo, linea)) {
        if (linea == "=== Usuario ===") {
            // Si llego aquí, empiezo a leer los datos del usuario
            getline(archivo, linea);
            string nombreArchivo = trim(linea.substr(8)); // Quito el "Nombre: "

            getline(archivo, linea);
            string passArchivo = trim(linea.substr(13)); // Quito el "Contraseña: "

            getline(archivo, linea);
            string codigoArchivo = trim(linea.substr(8)); // Quito el "Código: "

            getline(archivo, linea); // Esta línea es solo decorativa, así que la ignoro

            // Comparo el nombre y el código con los que recibí
            if (nombreArchivo == nombre && codigoArchivo == codigo) {
                password = passArchivo; // Guardo la contraseña si todo coincide
                return true;
            }
        }
    }
    return false; // Si no encuentro coincidencia, regreso false
}

// Esta función la hice para reemplazar la contraseña vieja con una nueva directamente en el archivo.
// Uso un archivo temporal para ir copiando todo, y luego reemplazo el archivo original.
void actualizarContrasena(const string& nombre, const string& nuevaPass) {
    ifstream archivo("usuarios.txt");
    ofstream temp("temp.txt");

    string linea;
    while (getline(archivo, linea)) {
        if (linea == "=== Usuario ===") {
            temp << linea << '\n';

            // Leo y copio el nombre
            getline(archivo, linea);
            string nombreArchivo = trim(linea.substr(8));
            temp << "Nombre: " << nombreArchivo << '\n';

            // Leo la contraseña actual (pero tal vez la cambie)
            getline(archivo, linea);
            string passArchivo = trim(linea.substr(13));

            // Leo el código
            getline(archivo, linea);
            string codigoArchivo = trim(linea.substr(8));

            // Leo el cierre decorativo
            getline(archivo, linea);

            // Si es el usuario al que quiero cambiarle la contraseña, lo hago aquí
            if (nombreArchivo == nombre) {
                temp << "Contraseña: " << nuevaPass << '\n';
            } else {
                temp << "Contraseña: " << passArchivo << '\n';
            }

            temp << "Código: " << codigoArchivo << '\n';
            temp << "=================\n";
        } else {
            // Si no estoy en un bloque de usuario, copio la línea como está
            temp << linea << '\n';
        }
    }

    // Cierro ambos archivos
    archivo.close();
    temp.close();

    // Borro el original y renombro el nuevo archivo como el principal
    remove("usuarios.txt");
    rename("temp.txt", "usuarios.txt");
}


void recuperarContrasena() {
    string nombre, codigo, password;
    cout << "\n=== Recuperar Contraseña ===\n";
    cout << "Nombre de usuario: ";
    getline(cin, nombre);
    cout << "Ingresa tu código de recuperación: ";
    getline(cin, codigo);

    // Siempre limpio espacios antes de comparar, para evitar errores tontos
    nombre = trim(nombre);
    codigo = trim(codigo);

    // Aquí uso mi función para verificar el código y recuperar la contraseña
    if (verificarCodigoRecuperacion(nombre, codigo, password)) {
        cout << "¡Código correcto! Tu contraseña actual es: " << password << "\n";

        // Le doy la opción de cambiarla
        string nuevaPass, confirmar;
        cout << "\n¿Deseas cambiar tu contraseña? (s/n): ";
        string respuesta;
        getline(cin, respuesta);

        if (respuesta == "s" || respuesta == "S") {
            // Pido y confirmo la nueva contraseña
            cout << "Nueva contraseña: ";
            getline(cin, nuevaPass);
            cout << "Confirma tu nueva contraseña: ";
            getline(cin, confirmar);

            // Si todo está bien, la actualizo
            if (nuevaPass == confirmar && !nuevaPass.empty()) {
                actualizarContrasena(nombre, nuevaPass);
                cout << "¡Contraseña actualizada exitosamente!\n";
            } else {
                cout << "Las contraseñas no coinciden o están vacías. No se actualizó nada.\n";
            }
        } else {
            cout << "No se hizo ningún cambio. Puedes seguir usando tu contraseña actual.\n";
        }
    } else {
        // Si algo falla, doy el aviso
        cout << "Usuario o código incorrecto.\n";
    }
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

    // ----------- Lógica del Blackjack -----------

  int generarCarta() {
    // Genero un número aleatorio entre 1 y 13 para representar una carta.
    int carta = rand() % 13 + 1;
    // Si la carta es mayor a 10, devuelvo 10 (J, Q, K).
    if (carta > 10) return 10;
    // Si la carta es un As, lo trato como 11.
    if (carta == 1) return 11; // As como 11
    // Devuelvo el valor de la carta.
    return carta;
}

    
  string obtenerPaloAleatorio() {
    // Defino los palos de las cartas.
    string palos[] = {"♠", "♥", "♦", "♣"};
    // Retorno un palo aleatorio.
    return palos[rand() % 4];
}

string ajustarValor(int valor) {
    // Ajusto el valor de la carta a su representación en texto.
    if (valor == 11) return "A"; // As
    if (valor == 10) return "10"; // Diez
    if (valor == 9) return "9"; // Nueve
    if (valor == 8) return "8"; // Ocho
    if (valor == 7) return "7"; // Siete
    if (valor == 6) return "6"; // Seis
    if (valor == 5) return "5"; // Cinco
    if (valor == 4) return "4"; // Cuatro
    if (valor == 3) return "3"; // Tres
    if (valor == 2) return "2"; // Dos
    // Si el valor no es válido, retorno un símbolo de interrogación.
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
    // Calculo el puntaje total de las cartas.
    int suma = 0, ases = 0;
    for (int i = 0; i < numCartas; i++) {
        suma += cartas[i];
        // Cuento cuántos Ases tengo.
        if (cartas[i] == 11) ases++;
    }
    // Ajusto el puntaje si me paso de 21 y tengo Ases.
    while (suma > 21 && ases > 0) {
        suma -= 10; // Considero el As como 1 en lugar de 11.
        ases--;
    }
    // Retorno el puntaje final.
    return suma;
}

   void jugarBlackjack() {
    // Verifico si tengo dinero para jugar.
    if (dinero <= 0) {
        cout << "No tienes dinero para jugar Blackjack.\n";
        return;
    }

    int apuesta;
    cout << "Tu dinero actual es $" << dinero << ". Ingresa tu apuesta: $";
    cin >> apuesta;

    // Verifico si la apuesta es válida.
    if (cin.fail() || apuesta <= 0 || apuesta > dinero) {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Apuesta inválida.\n";
        return;
    }

    // Inicializo los arreglos para las cartas del jugador y del dealer.
    int valoresJugador[10], valoresDealer[10];
    string palosJugador[10], palosDealer[10];
    int numJugador = 0, numDealer = 0;

    // Reparto 2 cartas a jugador y dealer.
    for (int i = 0; i < 2; i++) {
        valoresJugador[numJugador] = generarCarta();
        palosJugador[numJugador++] = obtenerPaloAleatorio();

        valoresDealer[numDealer] = generarCarta();
        palosDealer[numDealer++] = obtenerPaloAleatorio();
    }

    // Muestro las cartas del jugador.
    cout << "\nTus cartas:\n";
    mostrarCartasASCII(valoresJugador, palosJugador, numJugador);
    cout << "(Total: " << calcularPuntaje(valoresJugador, numJugador) << ")\n";

    // Muestro la carta visible del dealer.
    cout << "\nCarta visible del dealer:\n";
    mostrarCartasASCII(valoresDealer, palosDealer, 1);

    char opcion;
    while (true) {
        // Calculo el puntaje del jugador.
        int puntaje = calcularPuntaje(valoresJugador, numJugador);
        // Verifico si el jugador se pasó de 21.
        if (puntaje > 21) {
            cout << "\nTe pasaste de 21. Perdiste.\n";
            dinero -= apuesta;
            registrarJuego("Blackjack", nombre, -apuesta, dinero);
            guardarSaldo(nombre, dinero); // Actualizo el saldo después de perder
            return;
        }

        // Pregunto al jugador si quiere otra carta.
        cout << "\n¿Quieres otra carta? (s/n): ";
        cin >> opcion;
        if (tolower(opcion) != 's') break;

        // Reparto otra carta al jugador.
        valoresJugador[numJugador] = generarCarta();
        palosJugador[numJugador++] = obtenerPaloAleatorio();

        // Muestro las cartas del jugador nuevamente.
        cout << "\nTus cartas:\n";
        mostrarCartasASCII(valoresJugador, palosJugador, numJugador);
        cout << "(Total: " << calcularPuntaje(valoresJugador, numJugador) << ")\n";
    }

    // Turno del dealer.
    cout << "\nTurno del dealer...\n";
    mostrarCartasASCII(valoresDealer, palosDealer, numDealer);
    cout << "(Total: " << calcularPuntaje(valoresDealer, numDealer) << ")\n";

    // El dealer toma cartas hasta que su puntaje sea al menos 17.
    while (calcularPuntaje(valoresDealer, numDealer) < 17) {
        valoresDealer[numDealer] = generarCarta();
        palosDealer[numDealer++] = obtenerPaloAleatorio();

        cout << "\nDealer toma carta:\n";
        mostrarCartasASCII(valoresDealer, palosDealer, numDealer);
        cout << "(Total: " << calcularPuntaje(valoresDealer, numDealer) << ")\n";
    }

    // Calculo los puntajes finales.
    int puntajeJugador = calcularPuntaje(valoresJugador, numJugador);
    int puntajeDealer = calcularPuntaje(valoresDealer, numDealer);

    // Determino el resultado del juego.
    if (puntajeDealer > 21 || puntajeJugador > puntajeDealer) {
        cout << "\n¡Ganaste!\n";
        dinero += apuesta;
        registrarJuego("Blackjack", nombre, apuesta, dinero);
    } else if (puntajeJugador == puntajeDealer) {
        cout << "\nEmpate. No ganas ni pierdes.\n";
        registrarJuego("Blackjack", nombre, 0, dinero);
    } else {
        cout << "\nPerdiste.\n";
        dinero -= apuesta;
        registrarJuego("Blackjack", nombre, -apuesta, dinero);
    }

    // Actualizo el saldo después de cada partida.
    guardarSaldo(nombre, dinero);
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
            case 3:
                if (jugador.dinero <= 0)
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                else
                    cout << "Ruleta aún no implementada.\n"; // Placeholder
                break;
            case 4:
                if (jugador.dinero <= 0) {
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                } else {
                    jugador.jugarBlackjack();
                }
                break;
            case 5:
                if (jugador.dinero <= 0)
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                else
                    cout << "Tragamonedas aún no implementadas.\n"; // Placeholder
                break;
            case 6:
                if (jugador.dinero <= 0)
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                else
                    cout << "Craps aún no implementado.\n"; // Placeholder
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
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

    iniciar(nombre);  // Iniciar ciclo de juego después de login
}

#endif // JUGADOR_H
