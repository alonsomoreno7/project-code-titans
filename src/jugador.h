#ifndef JUGADOR_H
#define JUGADOR_H

// Incluyo las librerías necesarias para el funcionamiento del código:
#include <string>      // Para manejar texto (strings)
#include <fstream>     // Para trabajar con archivos (leer/escribir)
#include <cmath>       // Para operaciones matemáticas (como cos, sin, M_PI)
#include <iostream>    // Para entrada/salida estándar (cout, cin)
#include <cctype>      // Para funciones de caracteres (isalpha, tolower)
#include <cstdlib>     // Para rand() y system()
#include <ctime>       // Para time() (semilla de números aleatorios)
#include <limits>      // Para limpiar buffers de entrada (numeric_limits)
#include <windows.h>   // Para Sleep() en Windows (solo se incluye en Windows)
#include <algorithm>   // Para transform() y otras operaciones con contenedores
/*
#include "hilo.h"
*/
#include "multijugador.h"

using namespace std;

const int MAX_REGISTROS = 100;  // Defino un máximo de registros para el historial del jugador

// Defino constantes para los niveles de dificultad del blackjack
const int NORMAL = 2;
const int MEDIO = 3;
const int DIFICIL = 4;

// Defino la cantidad de números que tiene la ruleta
const int NUMEROS = 37;

// Aquí pongo los números reales de la ruleta, en el orden que aparecen
const int numeros[NUMEROS] = {
    0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6,
    27, 13, 36, 11, 30, 8, 23, 10, 5, 24,
    16, 33, 1, 20, 14, 31, 9, 22, 18, 29,
    7, 28, 12, 35, 3, 26
};

// Asigno el color correspondiente a cada número: 'R' rojo, 'N' negro, 'G' verde (solo el 0)
const char colores[NUMEROS] = {
    'G', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R', 'N', 'R',
    'N', 'R', 'N', 'R', 'N', 'R'
};

// Defino los códigos ANSI para cambiar el color del texto en consola
const string rojo = "\033[31m";
const string negro = "\033[30m";
const string verde = "\033[32m";
const string fondo_blanco = "\033[47m";
const string reset = "\033[0m";

// Estructura para guardar la posición X y Y de cada número en la ruleta visual
struct Posicion { int x, y; };

// Configuro las dimensiones y centro del "canvas" donde dibujaré la ruleta
const int WIDTH = 90;
const int HEIGHT = 30;
const int RADIO = 13;
const int CENTRO_X = WIDTH / 2;
const int CENTRO_Y = HEIGHT / 2;

// Array para guardar las posiciones calculadas de cada número
Posicion posiciones[NUMEROS];

// Aquí calculo la posición de cada número en forma circular para mostrar la ruleta
void calcularPosiciones() {
    for (int i = 0; i < NUMEROS; i++) {
        double angulo = (2 * M_PI * i / NUMEROS) - M_PI / 2; // Distribuyo equitativamente en 360°
        posiciones[i].x = CENTRO_X + int(RADIO * cos(angulo) * 1.9); // Ajusto factor X para visual mejor
        posiciones[i].y = CENTRO_Y + int(RADIO * sin(angulo));
    }
}

// Esta función dibuja la ruleta en consola, con los números y sus colores, y resalta uno iluminado
void imprimirCanvas(int iluminado) {
    string canvas[HEIGHT][WIDTH];
    // Primero lleno todo con espacios para limpiar el canvas
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            canvas[i][j] = " ";

    // Pongo cada número en su posición con su color correspondiente
    for (int i = 0; i < NUMEROS; i++) {
        int x = posiciones[i].x;
        int y = posiciones[i].y;
        string color = (colores[i] == 'R') ? rojo : (colores[i] == 'N') ? negro : verde;

        // Si es el número iluminado, lo resalto con fondo blanco
        if (i == iluminado) color = fondo_blanco + color;

        string numStr = (numeros[i] < 10 ? " " : "") + to_string(numeros[i]);

        // Verifico que la posición esté dentro del canvas
        if (x >= 0 && x + 1 < WIDTH && y >= 0 && y < HEIGHT) {
            canvas[y][x] = color + numStr + reset;
            canvas[y][x + 1] = ""; // Evito sobreescribir por error
        }
    }

    // Dibujo puntos decorativos para darle un efecto de círculo
    for (int r = 1; r < RADIO - 2; r++) {
        for (int a = 0; a < 360; a += 15) {
            double rad = a * M_PI / 180.0;
            int x = CENTRO_X + int(r * cos(rad) * 0.5);
            int y = CENTRO_Y + int(r * sin(rad));
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
                canvas[y][x] = ".";
        }
    }

    // Marco el centro con una "O"
    canvas[CENTRO_Y][CENTRO_X] = "O";

    // Finalmente imprimo el canvas línea por línea
    for (int i = 0; i < HEIGHT; i++) {
        string linea = "";
        for (int j = 0; j < WIDTH; j++) {
            if (!canvas[i][j].empty()) linea += canvas[i][j];
        }
        cout << linea << "\n";
    }
}

// Función para pasar a minúsculas una cadena (me sirve para validar entradas)
string toLower(const string &s) {
    string res = s;
    transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

// Pido el tipo de apuesta (número, color o par/impar) y valido que sea una opción válida
string pedirTipoApuesta() {
    string tipo;
    while (true) {
        cout << "\n╔══════════════════════════════════════╗\n";
        cout << "║         MENÚ DE APUESTAS             ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║  1. Número exacto      →  paga 35x   ║\n";
        cout << "║  2. Color (Rojo/Negro) →  paga 2x    ║\n";
        cout << "║  3. Par o Impar        →  paga 2x    ║\n";
        cout << "╚══════════════════════════════════════╝\n";
        cout << "→ Escoge una opción: ";
        cin >> tipo;
        tipo = toLower(tipo);

        if (tipo == "1" || tipo == "2" || tipo == "3")
            return tipo;
        else
            cout << "Opción inválida, intenta de nuevo.\n";
    }
}

// Pido un número del 0 al 36 para la apuesta a número exacto
int pedirNumero() {
    int num;
    while (true) {
        cout << "Ingresa el número (0-36): ";
        if (cin >> num) {
            if (num >= 0 && num <= 36)
                return num;
            else
                cout << "Número inválido. Debe estar entre 0 y 36.\n";
        } else {
            cout << "Entrada inválida. Ingresa un número entero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Pido el color (Rojo o Negro), convierto a mayúsculas y valido que sea correcto
char pedirColor() {
    string color;
    while (true) {
        cout << "Ingresa el color (Rojo / Negro): ";
        cin >> color;
        color = toLower(color);
        if (color == "rojo")
            return 'R';
        else if (color == "negro")
            return 'N';
        else
            cout << "Color inválido. Solo 'Rojo' o 'Negro'.\n";
    }
}

// Pido si apuesta a par o impar, valido la entrada
char pedirParidad() {
    string paridad;
    while (true) {
        cout << "¿Par o Impar?: ";
        cin >> paridad;
        paridad = toLower(paridad);
        if (paridad == "par")
            return 'P';
        else if (paridad == "impar")
            return 'I';
        else
            cout << "Opción inválida. Solo 'Par' o 'Impar'.\n";
    }
}

// Pregunto si el jugador quiere seguir jugando, acepto respuestas variadas
bool preguntarSeguir() {
    string resp;
    while (true) {
        cout << "\n¿Querés seguir jugando? (sí / no): ";
        cin >> resp;
        resp = toLower(resp);
        if (resp == "si" || resp == "sí") return true;
        else if (resp == "no") return false;
        else cout << "Respuesta inválida. Por favor, responde 'sí' o 'no'.\n";
    }
}

// Según el sistema operativo defino cómo pausar o limpiar la consola
#ifdef _WIN32
void esperarMs(int ms) { Sleep(ms); }
void limpiarConsola() { system("cls"); }
#else
void esperarMs(int ms) { usleep(ms * 1000); }
void limpiarConsola() { cout << "\033[2J\033[H"; }
#endif


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

// Esta función la hice para "normalizar" un texto, es decir, eliminar espacios y poner todo en minúsculas.
// Me sirve para comparar nombres sin que importe si el usuario usó mayúsculas o dejó espacios.
string normalizar(const string& texto) {
    string limpio; // Aquí voy guardando el texto ya limpio

    for (char c : texto) {
        // Recorro cada carácter del texto original
        if (!isspace(c)) // Si el carácter NO es un espacio...
            limpio += tolower(c); // ... lo convierto a minúscula y lo agrego al string limpio
    }

    // Al final devuelvo el texto ya procesado, sin espacios ni mayúsculas
    return limpio;
}

// ----------- Gestión de usuarios -----------

// Verifico si el usuario ya está registrado en el archivo usuarios.txt
// Esta función me sirve para verificar si ya existe un usuario con el mismo nombre
bool existeUsuario(const string& nombre) {
    ifstream archivo("./documentos/usuarios.txt");
    if (!archivo.is_open()) return false;  // Si no puedo abrir el archivo, asumo que no existe usuario

    string linea;
    string nombreNormalizado = normalizar(nombre);  // Normalizo el nombre que busco

    while (getline(archivo, linea)) {
        if (linea == "=== Usuario ===") {
            getline(archivo, linea);
            string nombreArchivo = linea.substr(8);  // Quito "Nombre: "
            string nombreArchivoNorm = normalizar(nombreArchivo);  // Normalizo nombre del archivo

            // Si coinciden los nombres normalizados, ya existe el usuario
            if (nombreArchivoNorm == nombreNormalizado) return true;

            // Ignoro las siguientes 2 líneas (contraseña y código) porque cada usuario ocupa 3 líneas
            getline(archivo, linea);
            getline(archivo, linea);
        }
    }
    return false;  // No encontré el usuario
}

// Función para eliminar un usuario verificando su código de recuperación
// Esta función elimina un usuario del archivo, solo si el nombre y el código coinciden.
// Yo me aseguro de comparar los datos de manera normalizada para evitar errores por mayúsculas o espacios.
void eliminarUsuario() {
    // Abro el archivo original y el archivo temporal donde escribiré los datos filtrados
    ifstream archivo("./documentos/usuarios.txt");
    ofstream temp("./documentos/temp.txt");

    // Pido los datos al usuario
    string nombre, codigo;
    cout << "Ingrese nombre de usuario a eliminar: ";
    getline(cin, nombre);
    cout << "Ingrese código de recuperación: ";
    getline(cin, codigo);

    // Normalizo lo que el usuario escribió, para que no fallen las comparaciones por errores menores
    string nombreInput = normalizar(nombre);
    string codigoInput = normalizar(codigo);

    bool eliminado = false;
    string linea;

    // Si los archivos se abrieron correctamente, procedo
    if (archivo.is_open() && temp.is_open()) {
        while (getline(archivo, linea)) {
            if (linea == "=== Usuario ===") {
                // Leo las siguientes líneas que contienen los datos del usuario
                string bloqueCompleto = linea + "\n";

                getline(archivo, linea);
                bloqueCompleto += linea + "\n";
                string nombreArchivo = trim(linea.substr(8));  // Quito "Nombre: "

                getline(archivo, linea);
                bloqueCompleto += linea + "\n";
                string passArchivo = trim(linea.substr(13));  // Quito "Contraseña: "

                getline(archivo, linea);
                bloqueCompleto += linea + "\n";
                string codigoArchivo = trim(linea.substr(8));  // Quito "Código: "

                getline(archivo, linea); // Línea decorativa final
                bloqueCompleto += linea + "\n\n";

                // Comparo usando los valores normalizados
                if (!eliminado && normalizar(nombreArchivo) == nombreInput && normalizar(codigoArchivo) == codigoInput) {
                    eliminado = true;  // Encontré el usuario y no lo copio al archivo nuevo
                    cout << "Usuario eliminado correctamente.\n";
                } else {
                    // Si no es el usuario que quiero eliminar, lo copio igual al archivo temporal
                    temp << bloqueCompleto;
                }
            } else {
                // Si no es parte de un bloque de usuario, copio normalmente
                temp << linea << '\n';
            }
        }

        archivo.close();
        temp.close();

        // Reemplazo el archivo original por el nuevo
        remove("./documentos/usuarios.txt");
        rename("./documentos/temp.txt", "./documentos/usuarios.txt");

        // Si nunca marqué como eliminado, entonces no lo encontré
        if (!eliminado) {
            cout << "Usuario o código incorrecto, no se eliminó nada.\n";
        }
    } else {
        cout << "Error al abrir archivos.\n";
    }
}

// Guardo un nuevo usuario en usuarios.txt (nombre, contraseña y código de recuperación)
void guardarUsuario(const string& nombre, const string& password, const string& codigo) {
    ofstream archivo("./documentos/usuarios.txt", ios::app);
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

        // Valido que el nombre solo tenga letras y espacios (usando otra función que tengas).
        if (!nombreValido(nombre)) {
            cout << "Nombre inválido. Solo letras y espacios.\n";
            continue;  // Si es inválido, pido de nuevo
        }

        // Normalizo el nombre y verifico que no exista ya en el archivo.
        if (existeUsuario(normalizar(nombre))) {
            cout << "Ese nombre ya está registrado. Intenta otro.\n";
            nombre.clear();
            continue;
        }
    } while (nombre.empty());

    // Si llego aquí, el nombre está bien y no está repetido.
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
    // Primero intento abrir el archivo donde guardo los usuarios.
    ifstream archivo("./documentos/usuarios.txt");
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo de usuarios.\n";
        return false;
    }

    // Pido al usuario su nombre y contraseña para iniciar sesión.
    string nombreIngresado, passIngresada;
    cout << "\n=== Iniciar sesión ===\n";
    cout << "Nombre de usuario: ";
    getline(cin, nombreIngresado);
    cout << "Contraseña: ";
    getline(cin, passIngresada);

    // Normalizo el nombre ingresado para evitar problemas de mayúsculas y espacios.
    string nombreIngresadoNorm = normalizar(nombreIngresado);

    string linea;
    while (getline(archivo, linea)) {
        if (linea == "=== Usuario ===") {
            // Cuando encuentro la etiqueta, leo los datos del usuario.
            getline(archivo, linea);
            string nombreArchivo = normalizar(trim(linea.substr(8)));

            getline(archivo, linea);
            string passArchivo = trim(linea.substr(13));

            getline(archivo, linea);
            getline(archivo, linea); // Línea decorativa, solo avanzo

            // Comparo el nombre normalizado y la contraseña ingresada.
            if (nombreArchivo == nombreIngresadoNorm && passArchivo == passIngresada) {
                // Si coinciden, guardo el nombre real y doy la bienvenida.
                jugador = nombreIngresado;
                cout << "¡Bienvenido, " << jugador << "!\n";
                cout <<"=========================="<<"\n";
                return true;
            }
        }
    }

    // Si no encuentro coincidencia, aviso que las credenciales son incorrectas.
    cout << "Credenciales incorrectas.\n";
    jugador.clear();
    return false;
}


// Aquí busco si existe un usuario con su respectivo código de recuperación
// Si todo va bien, también recupero la contraseña original
bool verificarCodigoRecuperacion(const string& nombre, const string& codigo, string& password) {
    // Intento abrir el archivo para buscar el usuario y su código.
    ifstream archivo("./documentos/usuarios.txt");
    if (!archivo.is_open()) return false;

    // Normalizo el nombre para comparar sin importar mayúsculas o espacios.
    string nombreNorm = normalizar(nombre);

    string linea;
    while (getline(archivo, linea)) {
        if (linea == "=== Usuario ===") {
            // Leo la información de un usuario.
            getline(archivo, linea);
            string nombreArchivo = normalizar(trim(linea.substr(8)));

            getline(archivo, linea);
            string passArchivo = trim(linea.substr(13));

            getline(archivo, linea);
            string codigoArchivo = trim(linea.substr(8));

            getline(archivo, linea); // Ignoro línea decorativa

            // Comparo si el nombre y código coinciden.
            if (nombreArchivo == nombreNorm && codigoArchivo == codigo) {
                // Si sí, guardo la contraseña para devolverla.
                password = passArchivo;
                return true;
            }
        }
    }
    // Si no encuentro coincidencia, retorno falso.
    return false;
}

// Esta función la hice para reemplazar la contraseña vieja con una nueva directamente en el archivo.
// Uso un archivo temporal para ir copiando todo, y luego reemplazo el archivo original.
void actualizarContrasena(const string& nombre, const string& nuevaPass) {
    ifstream archivo("./documentos/usuarios.txt");
    ofstream temp("./documentos/temp.txt");

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
    remove("./documentos/usuarios.txt");
    rename("./documentos/temp.txt", "./documentos/usuarios.txt");
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
    ofstream archivo("./documentos/movimientos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "Jugador: " << jugador << " | Evento: " << tipoMovimiento
                << " | Cantidad: $" << cantidad
                << " | Dinero restante: $" << dineroRestante << "\n";
    }
}

// Registro eventos de juegos en un archivo para historial general
void guardarJuego(const string& tipoEvento, const string& jugador, int cantidad, int resultado, int dineroRestante) {
    ofstream archivo("./documentos/juegos.txt", ios::app);
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
    ofstream archivo("./documentos/saldo_" + jugador + ".txt");  // Archivo separado por jugador
    if (archivo.is_open()) {
        archivo << dinero << "\n";
    }
}

// Cargo el saldo guardado para un jugador desde su archivo
int cargarSaldo(const string& jugador) {
    ifstream archivo("./documentos/saldo_" + jugador + ".txt");
    if (!archivo.is_open()) return 0;

    int dineroGuardado;
    archivo >> dineroGuardado;
    if (archivo.fail()) return 0;  // Si no pudo leer el entero, devuelvo 0
    return dineroGuardado;
}

// Agrega estas funciones auxiliares (pueden estar en la clase Jugador o como funciones libres)
void guardarEstadisticas(const string& nombre, int jugadas, int ganadas, int perdidas, int empatadas) {
    ofstream archivo("./documentos/estadisticas_" + nombre + ".txt");
    if (archivo.is_open()) {
        archivo << "Partidas jugadas: " << jugadas << "\n";
        archivo << "Partidas ganadas: " << ganadas << "\n";
        archivo << "Partidas perdidas: " << perdidas << "\n";
        archivo << "Partidas empatadas: " << empatadas << "\n";
        archivo.close();
    }
}

bool cargarEstadisticas(const string& nombre, int& jugadas, int& ganadas, int& perdidas, int& empatadas) {
    // Primero intento abrir el archivo que contiene las estadísticas del jugador
    ifstream archivo("./documentos/estadisticas_" + nombre + ".txt");

    // Si no se puede abrir el archivo, devuelvo false para indicar el error
    if (!archivo.is_open()) return false;

    string clave;
    int valor;

    // Empiezo a leer línea por línea, separando la clave y el valor usando ':' como delimitador
    while (archivo >> ws && getline(archivo, clave, ':')) {
        archivo >> ws; // Elimino espacios innecesarios antes del valor

        // Verifico que el valor sea un número válido
        if (!(archivo >> valor)) {
            archivo.clear(); // Limpio cualquier estado de error del archivo
            archivo.ignore(numeric_limits<streamsize>::max(), '\n'); // Me salto la línea si está mal escrita
            continue; // Paso a la siguiente línea
        }

        // Comparo la clave leída para saber a qué estadística corresponde el valor
        if (clave == "Partidas jugadas") {
            jugadas = valor; // Asigno el valor a la variable de jugadas
        } else if (clave == "Partidas ganadas") {
            ganadas = valor; // Asigno el valor a la variable de ganadas
        } else if (clave == "Partidas perdidas") {
            perdidas = valor; // Asigno el valor a la variable de perdidas
        } else if (clave == "Partidas empatadas") {
            empatadas = valor; // Asigno el valor a la variable de empatadas
        }
    }

    // Cierro el archivo al finalizar la lectura
    archivo.close();

    // Devuelvo true porque todo salió bien
    return true;
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

    int partidasJugadas = 0;
    int partidasGanadas = 0;
    int partidasPerdidas = 0;
    int partidasEmpatadas = 0;

     void actualizarEstadisticas() {
        guardarEstadisticas(nombre, partidasJugadas, partidasGanadas, partidasPerdidas, partidasEmpatadas);
    }

    void cargarEstadisticasJugador() {
        int j, g, p, e;
        if (cargarEstadisticas(nombre, j, g, p, e)) {
            partidasJugadas = j;
            partidasGanadas = g;
            partidasPerdidas = p;
            partidasEmpatadas = e;
        }
    }

    // Actualiza el método mostrarEstadisticas
 void mostrarEstadisticas() {
    // Cargar estadísticas del jugador desde el archivo
    cargarEstadisticasJugador();
    
    cout << "\nEstadísticas del jugador:\n";
    cout << "Partidas jugadas: " << partidasJugadas << "\n";
    cout << "Partidas ganadas: " << partidasGanadas << "\n";
    cout << "Partidas perdidas: " << partidasPerdidas << "\n";
    cout << "Partidas empatadas: " << partidasEmpatadas << "\n";
}


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

    // ----------- Lógica de la Ruleta ----------- //

     void jugarRuleta() {
        calcularPosiciones(); // Calculo las posiciones de la ruleta
        while (dinero > 0) {
    // Verifico si tengo dinero para jugar.
    if (dinero <= 0) {
        cout << "No tienes dinero para jugar Blackjack.\n";
        return;
    }
    int apuesta;
    cout << "Tu dinero actual es $" << dinero << ". Ingresa tu apuesta (mínimo $10, máximo $500): $";
    
    while (true) {
        cin >> apuesta;
        // Verifico si la apuesta es válida.
        if (cin.fail() || apuesta < 10 || apuesta > 500 || apuesta > dinero) {
            cin.clear(); 
            cin.ignore(1000, '\n');
            cout << "Apuesta inválida. Debe ser entre $10 y $500 y no puede exceder tu saldo actual.\n";
            cout << "Tu dinero actual es $" << dinero << ". Ingresa tu apuesta: $";
            continue;
        }
        
        // Acepto la apuesta válida
        break;
    }
    partidasJugadas++; // Incremento el total de partidas jugadas

            // Pido qué tipo de apuesta quiere hacer
            string tipo = pedirTipoApuesta();

            int eleccion = -1;
            string resumen;
            char colorElegido = 0;
            char paridadElegida = 0;

            // Según el tipo pido más datos y armo un resumen para mostrar después
            if (tipo == "1") {
                eleccion = pedirNumero();
                resumen = "Apuesta: al número " + to_string(eleccion);
            } else if (tipo == "2") {
                colorElegido = pedirColor();
                resumen = "Apuesta: al color " + string((colorElegido == 'R') ? "Rojo" : "Negro") + " | Monto: $" + to_string(apuesta);
            } else { // tipo == "3"
                paridadElegida = pedirParidad();
                resumen = "Apuesta: a " + string((paridadElegida == 'P') ? "par" : "impar") + " | Monto: $" + to_string(apuesta);
            }

            cout << "\n" << resumen << "\nGirando la ruleta...\n";

            // Genero un número ganador aleatorio y simulo el giro con un efecto de desaceleración
            int ganador = rand() % NUMEROS;
            int vueltas = 3;
            int totalPasos = vueltas * NUMEROS + ganador;
            int iluminado = 0;

            for (int paso = 0; paso <= totalPasos; paso++) {
                limpiarConsola();
                cout << "\nSaldo actual: $" << dinero << "\n";
                cout << resumen << "\n";
                imprimirCanvas(iluminado);
                iluminado = (iluminado + 1) % NUMEROS;

                // Aquí hago que la animación desacelere conforme se acerca al número ganador
                if (paso > totalPasos - 10) esperarMs(200);
                else if (paso > totalPasos - 20) esperarMs(150);
                else esperarMs(60);
            }

            int numGanador = numeros[ganador];
            char colorGanador = colores[ganador];

            cout << "\nLa ruleta cayó en el número " << numGanador << " (";
            cout << (colorGanador == 'R' ? "Rojo" : colorGanador == 'N' ? "Negro" : "Verde") << ")\n";

            bool gano = false;
             // Evaluo si la apuesta fue ganadora
        if (tipo == "1" && numGanador == eleccion) {
            cout << "¡Ganaste 35 veces tu apuesta!\n";
            dinero += apuesta * 35;
            partidasGanadas++;
            gano = true;
        } else if (tipo == "2" && colorGanador == colorElegido) {
            cout << "¡Ganaste 2 veces tu apuesta!\n";
            dinero += apuesta * 2;
            partidasGanadas++;
            gano = true;
        } else if (tipo == "3") {
            // Para par o impar, el 0 no cuenta como ganador
            if (numGanador != 0) {
                if ((paridadElegida == 'P' && numGanador % 2 == 0) ||
                    (paridadElegida == 'I' && numGanador % 2 != 0)) {
                    cout << "¡Ganaste 2 veces tu apuesta!\n";
                    dinero += apuesta * 2;
                    partidasGanadas++;
                    gano = true;
                }
            }
        }

   if (!gano) {
    cout << "No ganaste esta vez.\n";
    dinero -= apuesta;
    partidasPerdidas++;
    }

            cout << "\nSaldo actualizado: $" << dinero << "\n";

              // Guardar saldo y estadísticas después de cada jugada
                guardarSaldo(nombre, dinero);
                actualizarEstadisticas();
                
            // Pregunto si quiere seguir jugando, validando que la respuesta sea correcta
            if (!preguntarSeguir()) break;
        }

        if (dinero <= 0) {
        cout << "\nTe has quedado sin dinero. Juego terminado.\n";
        // Asegurar guardado final del saldo y estadísticas
        guardarSaldo(nombre, dinero);
        actualizarEstadisticas();
        }

        cout << "\nGracias por jugar. Tu saldo final fue: $" << dinero << "\n";
    }

    // ----------- Lógica del Blackjack ----------- //

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
    cout << "Tu dinero actual es $" << dinero << ". Ingresa tu apuesta (mínimo $10, máximo $500): $";
    
    while (true) {
        cin >> apuesta;
        // Verifico si la apuesta es válida.
        if (cin.fail() || apuesta < 10 || apuesta > 500 || apuesta > dinero) {
            cin.clear(); 
            cin.ignore(1000, '\n');
            cout << "Apuesta inválida. Debe ser entre $10 y $500 y no puede exceder tu saldo actual.\n";
            cout << "Tu dinero actual es $" << dinero << ". Ingresa tu apuesta: $";
            continue;
        }
        
        // Acepto la apuesta válida
        break;
    }

    // Elijo el nivel de dificultad.
    int nivelDificultad;
   // Bucle para asegurarme de que el jugador elija una dificultad válida
while (true) {
    cout << "======================================\n";
    cout << "     Selecciona el nivel de dificultad\n";
    cout << "--------------------------------------\n";
    cout << "  1. Normal  (2 cartas)\n";
    cout << "  2. Medio   (3 cartas)\n";
    cout << "  3. Difícil (4 cartas)\n";
    cout << "======================================\n";
    cout << "Opción: ";
    
    cin >> nivelDificultad;

    // Verifico si la entrada fue numérica y está entre 1 y 3
    if (!cin.fail() && nivelDificultad >= 1 && nivelDificultad <= 3) {
        limpiarConsola();
        cout << "Has seleccionado el nivel ";
        if (nivelDificultad == 1) cout << "Normal.\n";
        else if (nivelDificultad == 2) cout << "Medio.\n";
        else cout << "Difícil.\n";
        break;
    }

    // Si la entrada fue inválida, la limpio y muestro el error
    cin.clear(); // Limpio el error de cin
    cin.ignore(1000, '\n'); // Descarto el resto de la línea
    limpiarConsola();
    cout << "Entrada inválida. Por favor ingresa un número del 1 al 3.\n\n";
}


    // Determino la cantidad de cartas según la dificultad seleccionada.
    int cartasIniciales = NORMAL + (nivelDificultad - 1); // Normal = 2, Medio = 3, Difícil = 4

    int valoresJugador[10], valoresDealer[10];
    string palosJugador[10], palosDealer[10];
    int numJugador = 0, numDealer = 0;

    // Reparto cartas según la dificultad seleccionada.
    for (int i = 0; i < cartasIniciales; i++) {
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
        partidasGanadas++;
        registrarJuego("Blackjack", nombre, apuesta, dinero);
    } else if (puntajeJugador == puntajeDealer) {
        cout << "\nEmpate. No ganas ni pierdes.\n";
        registrarJuego("Blackjack", nombre, 0, dinero);
        partidasEmpatadas++; 
    } else {
        cout << "\nPerdiste.\n";
        dinero -= apuesta;
        registrarJuego("Blackjack", nombre, -apuesta, dinero);
        partidasPerdidas++;
    }

    // Actualizo el saldo después de cada partida.
    guardarSaldo(nombre, dinero);
    // Actualizo las estadísticas en el archivo
    actualizarEstadisticas();
}

//----------- Lógica del Craps ----------- //


 //----------- Lógica del Craps ----------- //

void jugarCraps() {
    if (dinero <= 0) {
        cout << "No tienes saldo suficiente. Deposita para jugar.\n";
        return;
    }

    char jugarOtraVez;
    do {
        // Solicitar apuesta primero
        int apuesta;
        cout << "\nTu dinero actual es $" << dinero << ". Ingresa tu apuesta (mínimo $10, máximo $500): $";
        
        while (true) {
            cin >> apuesta;

            if (apuesta == 0) {
                cout << "Apuesta cancelada.\n";
                return;
            }
            
            if (cin.fail() || apuesta < 10 || apuesta > 500) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Apuesta inválida. Debe ser entre $10 y $500.\n";
                cout << "Ingresa tu apuesta: $";
                continue;
            }
            
            if (apuesta > dinero) {
                cout << "Saldo insuficiente. Tu saldo actual es $" << dinero << ".\n";
                cout << "Ingresa tu apuesta: $";
                continue;
            }
            
            break;
        }

        // Mostrar menú de dificultad después de la apuesta
        cout << "\n╔═══════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                       ♠ ♥ Welcome to Craps ♥ ♣                        ║\n";
        cout << "║                                                                       ║\n";
        cout << "║          Select the difficulty level to start:                        ║\n";
        cout << "║                                                                       ║\n";
        cout << "║                  1. Easy     ♣     2. Medium     ♦                    ║\n";
        cout << "║                            3. Hard       ♠                            ║\n";
        cout << "║                                                                       ║\n";
        cout << "╚═══════════════════════════════════════════════════════════════════════╝\n";

        int selection = validarEntradaCraps();
        
        partidasJugadas++;
        
        // Ejecutar la lógica del juego según la dificultad seleccionada
        int resultado = 0;
        switch (selection) {
            case 1:
                cout << "Has seleccionado el nivel fácil (intentos ilimitados)\n";
                resultado = ejecutarJuegoCraps(0, apuesta);
                break;
            case 2:
                cout << "Has seleccionado el nivel medio (5 intentos)\n";
                resultado = ejecutarJuegoCraps(5, apuesta);
                break;
            case 3:
                cout << "Has seleccionado el nivel difícil (3 intentos)\n";
                resultado = ejecutarJuegoCraps(3, apuesta);
                break;
        }

        dinero += resultado;
        guardarSaldo(nombre, dinero);
        actualizarEstadisticas();

        // Preguntar si quiere jugar otra vez
        cout << "\n¿Quieres jugar otra vez? (s/n): ";
        cin >> jugarOtraVez;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
    } while (tolower(jugarOtraVez) == 's');
}

// Función auxiliar para validar entrada en Craps
int validarEntradaCraps() {
    int choice = 0;
    cout << "Selecciona tu nivel de dificultad: ";
    cin >> choice;

    while (cin.fail() || cin.peek() != '\n' || choice < 1 || choice > 3) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                                            ♠ ♥ Message ♥ ♣                                           ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║           Please do not enter letters or special characters, only numbers between 1 and 3            ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                     Select your difficulty level:                                                    ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        cin >> choice;
    }
    return choice;
}

// Función principal que ejecuta el juego Craps
int ejecutarJuegoCraps(int maxAttempts, int apuesta) {
    cout << "Iniciando tirada inicial...\n";
    Sleep(3000);

    int comeOutRoll = lanzarDadosAnimado();
    cout << "La tirada inicial es: " << comeOutRoll << "\n";
    Sleep(3000);

    if (comeOutRoll == 2 || comeOutRoll == 3 || comeOutRoll == 12) {
        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                 ♠ ♥ You Lost ♥ ♣                  ║\n";
        cout << "║                                                   ║\n";
        cout << "║           Craps! You lost the game.               ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";
        registrarJuego("Craps", nombre, -apuesta, dinero - apuesta);
        partidasPerdidas++;
        return -apuesta;
    }
    else if (comeOutRoll == 7 || comeOutRoll == 11) {
        cout << "╔═══════════════════════════════════════════════╗\n";
        cout << "║                 ♠ ♥ You Won ♥ ♣               ║\n";
        cout << "║                                               ║\n";
        cout << "║     Congratulations, you won the round!       ║\n";
        cout << "║                                               ║\n";
        cout << "╚═══════════════════════════════════════════════╝\n";
        registrarJuego("Craps", nombre, apuesta, dinero + apuesta);
        partidasGanadas++;
        return apuesta;
    }
    else {
        int point = comeOutRoll;
        cout << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                                            ♠ ♥ Message ♥ ♣                                                  ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                              The point is set, the shooter will roll again...                               ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                      If the roll is: " << comeOutRoll << ", the shooter wins; if it's 7, the shooter loses                      ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        Sleep(3000);

        int attempts = 0;
        while (maxAttempts == 0 || attempts < maxAttempts) {
            attempts++;
            comeOutRoll = lanzarDadosAnimado();
            cout << "Intento #" << attempts << endl;
            cout << "La nueva tirada es: " << comeOutRoll << "\n";
            Sleep(3000);

            if (comeOutRoll == point) {
                cout << "╔═════════════════════════════════════════════════════╗\n";
                cout << "║                    ♠ ♥ You Won ♥ ♣                  ║\n";
                cout << "║                                                     ║\n";
                cout << "║                Congratulations, you won!            ║\n";
                cout << "║                                                     ║\n";
                cout << "╚═════════════════════════════════════════════════════╝\n";
                registrarJuego("Craps", nombre, apuesta, dinero + apuesta);
                partidasGanadas++;
                return apuesta;
            }
            else if (comeOutRoll == 7) {
                cout << "╔═════════════════════════════════════════════════════╗\n";
                cout << "║                   ♠ ♥ You Lost ♥ ♣                  ║\n";
                cout << "║                                                     ║\n";
                cout << "║               Sorry, you lost the game.             ║\n";
                cout << "║                                                     ║\n";
                cout << "╚═════════════════════════════════════════════════════╝\n";
                registrarJuego("Craps", nombre, -apuesta, dinero - apuesta);
                partidasPerdidas++;
                return -apuesta;
            }
        }

        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                  ♠ ♥ Message ♥ ♣                  ║\n";
        cout << "║                                                   ║\n";
        cout << "║       Sorry, you have run out of attempts.        ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";
        registrarJuego("Craps", nombre, -apuesta, dinero - apuesta);
        partidasPerdidas++;
        return -apuesta;
    }
}

// Función para mostrar dados en ASCII
void mostrarDadosASCII(int d1, int d2) {
    const char* diceFaces[6][5] = {
    {"+-------+", "|       |", "|   o   |", "|       |", "+-------+"},
    {"+-------+", "| o     |", "|       |", "|     o |", "+-------+"},
    {"+-------+", "| o     |", "|   o   |", "|     o |", "+-------+"},
    {"+-------+", "| o   o |", "|       |", "| o   o |", "+-------+"},
    {"+-------+", "| o   o |", "|   o   |", "| o   o |", "+-------+"},
    {"+-------+", "| o   o |", "| o   o |", "| o   o |", "+-------+"}
    };

    for (int i = 0; i < 5; ++i) {
        cout << diceFaces[d1 - 1][i] << "   " << diceFaces[d2 - 1][i] << "\n";
    }
    cout << endl;
}

// Función para animación de lanzamiento de dados
int lanzarDadosAnimado() {
  int d1 = 1, d2 = 1;
    
    // Limpiar consola de forma compatible
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    for (int i = 0; i < 10; ++i) {
        d1 = rand() % 6 + 1;
        d2 = rand() % 6 + 1;
        
        // Limpiar consola para cada frame de la animación
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        cout << "Tirando dados...\n\n";
        mostrarDadosASCII(d1, d2);
        Sleep(100);
    }
    
    // Mostrar resultado final
    cout << "Resultado final:\n\n";
    mostrarDadosASCII(d1, d2);
    return d1 + d2;
}

};

// ----------- Menú -----------

// Mostrar las opciones disponibles para el usuario
inline void mostrarMenu() {
    cout <<"\n====================================";
    cout << "\nMenu Principal - Casino Virtual\n";
    cout << "1) Depositar dinero\n";
    cout << "2) Retirar dinero\n";
    cout << "3) Ruleta\n";
    cout << "4) Blackjack\n";
    cout << "5) Tragamonedas\n";
    cout << "6) Craps (Dados)\n";
    cout << "7) Hi-Lo\n";
    cout << "8) Mostrar historial\n";
     cout << "9) Mostrar estadísticas \n";
    cout << "10) Salir\n";
    cout <<"====================================\n";
}

// Función principal que maneja el ciclo del juego después de iniciar sesión
inline void iniciar(const string& nombreUsuario) {
    Jugador jugador;
    jugador.nombre = nombreUsuario;
    jugador.dinero = cargarSaldo(nombreUsuario);
    jugador.cargarEstadisticasJugador(); 

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
                     jugador.jugarRuleta();
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
                else {
                    jugador.jugarCraps();
                }
                    
                break;
                /*
            case 7:
                if (jugador.dinero <= 0)
                    cout << "No tienes saldo suficiente. Deposita para jugar.\n";
                else
                    PlayHilo(jugador.dinero);
                break;
                */
            case 8:
                jugador.mostrarHistorial();
                break;
            case 9:  // Opción para mostrar estadísticas
                jugador.mostrarEstadisticas();
                break;
            case 10:
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
        cout << "4) Eliminar usuario\n";   
        cout << "5) Salir\n";
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
                eliminarUsuario();
                break;
            case 5:
                cout << "Saliendo del programa...\n";
                return;
            default:
                cout << "Opción inválida. Intenta nuevamente.\n";
        }
    }

    iniciar(nombre);  // Iniciar ciclo de juego después de login
}

// Este es el primer menú que muestro cuando se ejecuta el programa.
// Aquí el jugador elige si quiere jugar solo o con otra persona de forma local.
inline void menuModoJuego() {
    int opcion;

    while (true) {
        // Muestro las opciones con un diseño claro
        cout << "\n=========== MODO DE JUEGO ===========\n";
        cout << "1) Jugar solo\n";
        cout << "2) Multijugador local\n";
        cout << "3) Salir del juego\n";
        cout << "=====================================\n";
        cout << "Escoge una opción: ";
        cin >> opcion;

        // Verifico si lo que ingresó es válido (que sea número)
        if (cin.fail()) {
            cin.clear(); // Limpio el error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpio el buffer
            cout << "Entrada inválida. Ingresa un número del 1 al 3.\n";
            continue;
        }

        // Limpio el buffer por si escribió algo más después del número
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                // Si elige jugar solo, lo mando al menú de inicio (login, registro, etc.)
                menuInicio(); 
                return;

            case 2:
                // Si elige multijugador, llamo la función que maneja ese modo
                modoMultijugador();
                return;

            case 3:
                // Si decide salir, le doy un mensaje y termino
                cout << "¡Gracias por jugar! Hasta pronto.\n";
                return;

            default:
                // Si escribe un número fuera de 1-3, le aviso
                cout << "Opción inválida. Intenta de nuevo.\n";
        }
    }
}


#endif // JUGADOR_H