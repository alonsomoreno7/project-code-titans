#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <string>   // Uso esta librería para manejar texto con strings, así trabajo fácil con nombres, contraseñas y demás.
#include <fstream>  // La uso para abrir y guardar archivos donde guardo los datos de los usuarios.
#include <iostream> // Me permite mostrar mensajes y pedir datos por consola para interactuar con el usuario.
#include <cstdlib>  // La necesito para crear números aleatorios, por ejemplo para generar códigos de recuperación.
#include <ctime>    // La uso para saber la fecha y hora actual, para calcular si el usuario es mayor de edad.
#include <limits>   // Esta librería me sirve para controlar límites al recibir datos, aunque aquí no la uso directamente.
#include "utils.h"  // Aquí tengo funciones propias para limpiar y validar texto, así el código queda más ordenado.

// Uso el espacio de nombres std para no escribir std:: cada vez que uso funciones o clases estándar
using namespace std;

// Función que verifica si un usuario ya existe en el archivo usuarios.txt
inline bool existeUsuario(const string& nombre) {
    // Abro el archivo en modo lectura
    ifstream archivo("./documentos/usuarios.txt");

    // Si el archivo no se pudo abrir, retorno falso porque no puedo encontrar usuarios
    if (!archivo.is_open()) return false;

    // Declaro una variable para leer cada línea del archivo
    string linea;

    // Normalizo el nombre de usuario que recibí para comparar sin errores de mayúsculas o espacios
    string nombreNormalizado = normalizar(nombre);

    // Empiezo a leer línea por línea el archivo hasta que se termine
    while (getline(archivo, linea)) {
        // Cuando encuentro una línea que indica que empieza un bloque de usuario
        if (linea == "====== Usuario ======") {
            // Leo la siguiente línea, que debe contener el nombre del usuario
            getline(archivo, linea);

            // Quito el prefijo "Nombre: " que tiene 8 caracteres y guardo solo el nombre
            string nombreArchivo = linea.substr(8);

            // Normalizo el nombre que leí del archivo para compararlo correctamente
            string nombreArchivoNorm = normalizar(nombreArchivo);

            // Si el nombre normalizado del archivo es igual al nombre que busco, retorno true (usuario existe)
            if (nombreArchivoNorm == nombreNormalizado) return true;

            // Si no es el usuario que busco, salto las siguientes dos líneas que son contraseña y código
            getline(archivo, linea);
            getline(archivo, linea);
        }
    }

    // Si terminé de leer todo el archivo y no encontré el usuario, retorno false
    return false;
}

inline void eliminarUsuario() {
    // Primero limpio la pantalla para que el usuario vea solo lo necesario
    limpiarConsola();

    cout << "=== ELIMINAR USUARIO ===\n\n";

    // Pido el nombre del usuario que se desea eliminar
    cout << "Ingrese nombre de usuario a eliminar: ";
    string nombre;
    getline(cin, nombre);

    // Pido el código de recuperación para validar identidad
    cout << "Ingrese código de recuperación: ";
    string codigo;
    getline(cin, codigo);

    // Normalizo los datos para evitar problemas con mayúsculas o espacios
    string nombreInput = normalizar(nombre);
    string codigoInput = normalizar(codigo);

    // Inicializo bandera para saber si se eliminó un usuario
    bool eliminado = false;

    // Abro el archivo original para lectura
    ifstream archivo("./documentos/usuarios.txt");
    // Creo un archivo temporal para guardar los usuarios que NO se eliminarán
    ofstream temp("./documentos/temp.txt");

    // Verifico que ambos archivos se abran correctamente
    if (!archivo.is_open() || !temp.is_open()) {
        cout << "Error: No se pudo acceder a los archivos necesarios.\n";
        return;
    }

    string linea;
    // Leo el archivo línea por línea
    while (getline(archivo, linea)) {
        // Cuando encuentro el inicio de un bloque de usuario
        if (linea == "====== Usuario ======") {
            // Guardo el bloque completo para decidir si lo copio o ignoro
            string bloqueCompleto = linea + "\n";

            // Leo el nombre y lo agrego al bloque
            getline(archivo, linea);
            bloqueCompleto += linea + "\n";
            string nombreArchivo = trim(linea.substr(8));  // Quito "Nombre: "

            // Leo la contraseña y la agrego al bloque
            getline(archivo, linea);
            bloqueCompleto += linea + "\n";
            string passArchivo = trim(linea.substr(13));  // Quito "Contraseña: "

            // Leo el código de recuperación y lo agrego al bloque
            getline(archivo, linea);
            bloqueCompleto += linea + "\n";
            string codigoArchivo = trim(linea.substr(8));  // Quito "Código: "

            // Leo la línea vacía que cierra el bloque
            getline(archivo, linea);
            bloqueCompleto += linea + "\n\n";

            // Verifico si este bloque corresponde al usuario que quiero eliminar
            if (!eliminado && normalizar(nombreArchivo) == nombreInput && normalizar(codigoArchivo) == codigoInput) {
                // Marco que eliminé un usuario para evitar eliminar más por error
                eliminado = true;
                cout << "\n¡Usuario eliminado correctamente!\n";
                // No copio este bloque al archivo temporal (lo elimino)
            } else {
                // Si no es el usuario a eliminar, copio el bloque completo al temporal
                temp << bloqueCompleto;
            }
        } else {
            // Si la línea no es parte de un bloque, la copio tal cual
            temp << linea << '\n';
        }
    }

    // Cierro ambos archivos antes de reemplazar
    archivo.close();
    temp.close();

    // Reemplazo el archivo original por el temporal (actualizado)
    remove("./documentos/usuarios.txt");
    rename("./documentos/temp.txt", "./documentos/usuarios.txt");

    // Si no eliminé ningún usuario, informo al usuario
    if (!eliminado) {
        cout << "\nNo se encontró un usuario con ese nombre y código. No se eliminó nada.\n";
    }

    cout << "\nPresiona Enter para continuar...";
    cin.get(); // Pauso para que vea el mensaje
}


// Función que guarda toda la información de un usuario nuevo en el archivo usuarios.txt
inline void guardarUsuario(const string& nombre, const string& password, const string& codigo, const string& fechaNacimiento, const string& genero, const string& dui) {

    // Abro el archivo en modo agregar para no borrar datos anteriores
    ofstream archivo("./documentos/usuarios.txt", ios::app);

    // Verifico que el archivo se haya abierto correctamente
    if (archivo.is_open()) {

        // Escribo el encabezado para identificar un bloque de usuario
        archivo << "====== Usuario ======\n";

        // Guardo el nombre recibido
        archivo << "Nombre: " << nombre << "\n";

        // Guardo la contraseña recibida
        archivo << "Contraseña: " << password << "\n";

        // Guardo el código de recuperación generado
        archivo << "Código: " << codigo << "\n";

        // Guardo la fecha de nacimiento que recibí
        archivo << "Nacimiento: " << fechaNacimiento << "\n";

        // Guardo el género recibido (M/F/O)
        archivo << "Género: " << genero << "\n";

        // Guardo el DUI recibido con formato válido
        archivo << "DUI: " << dui << "\n";

        // Escribo una línea para cerrar el bloque del usuario y dejar espacio
        archivo << "=================\n\n";
    }
}

// Función que verifica si alguien es mayor de edad en base a la fecha de nacimiento dada (en formato DD/MM/AAAA)
// Ahora con validación completa de rangos y meses
inline bool esMayorDeEdad(const string& fechaNacimiento) {

    // Declaro variables para extraer día, mes y año
    int dia, mes, anio;

    // Intento extraer los números usando sscanf en formato DD/MM/AAAA
    // Si no puedo extraer 3 números, retorno falso porque la fecha está mal escrita
    if (sscanf(fechaNacimiento.c_str(), "%d/%d/%d", &dia, &mes, &anio) != 3)
        return false;

    // Valido que el año esté en un rango razonable (por ejemplo entre 1900 y 2100)
    // Si el año está fuera, retorno falso porque no es válido
    if (anio < 1900 || anio > 2100)
        return false;

    // Valido que el mes esté entre 1 y 12
    if (mes < 1 || mes > 12)
        return false;

    // Valido que el día esté entre 1 y 31
    if (dia < 1 || dia > 31)
        return false;

    // Ahora valido que el día sea válido según el mes específico
    // Por ejemplo, abril, junio, septiembre y noviembre tienen máximo 30 días
    bool diaValido = true; // variable para saber si el día es correcto

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        // Si el día es mayor a 30 en estos meses, es inválido
        if (dia > 30)
            diaValido = false;
    }
    else if (mes == 2) {
        // Para febrero debo considerar años bisiestos
        // Año bisiesto: divisible entre 400 o divisible entre 4 pero no entre 100
        bool esBisiesto = (anio % 400 == 0) || (anio % 4 == 0 && anio % 100 != 0);

        // Días que puede tener febrero dependiendo si es bisiesto o no
        int diasFeb = esBisiesto ? 29 : 28;

        // Si el día es mayor que los días permitidos en febrero, es inválido
        if (dia > diasFeb)
            diaValido = false;
    }

    // Si día no es válido, retorno falso
    if (!diaValido)
        return false;

    // Si llegué hasta aquí, la fecha tiene formato y rango válido
    // Ahora calculo la edad para verificar si es mayor de edad

    // Obtengo la fecha actual con time y localtime
    time_t t = time(nullptr);
    tm* ahora = localtime(&t);

    // Extraigo año, mes y día actuales
    int anioActual = ahora->tm_year + 1900; // tm_year cuenta desde 1900
    int mesActual = ahora->tm_mon + 1;      // tm_mon va de 0 a 11
    int diaActual = ahora->tm_mday;

    // Calculo la edad como diferencia entre años
    int edad = anioActual - anio;

    // Ajusto edad si aún no cumplió años este año
    if (mesActual < mes || (mesActual == mes && diaActual < dia))
        edad--;

    // Retorno true si tiene 18 años o más, sino false
    return edad >= 18;
}


// Función que verifica si un DUI ya está registrado en el archivo
inline bool duiRepetido(const string& dui) {
    ifstream archivo("./documentos/usuarios.txt");
    string linea;

    if (!archivo.is_open()) return false;

    while (getline(archivo, linea)) {
        // Busco la línea que contiene el DUI
        if (linea.rfind("DUI: ", 0) == 0) {  // Si comienza con "DUI: "
            string duiArchivo = trim(linea.substr(5)); // Extraigo el valor del DUI
            if (duiArchivo == dui) {
                archivo.close();
                return true; // El DUI ya existe
            }
        }
    }

    archivo.close();
    return false; // El DUI no se encontró
}

// Función que valida formato correcto y que no se repita el DUI
inline bool duiValido(const string& dui) {
    // Verifico formato: longitud 10 y guion en la posición 8
    if (dui.length() != 10 || dui[8] != '-') return false;

    // Verifico que los primeros 8 y el último carácter sean dígitos
    for (int i = 0; i < 8; ++i)
        if (!isdigit(dui[i])) return false;
    if (!isdigit(dui[9])) return false;

    // Verifico que no esté repetido en el archivo
    if (duiRepetido(dui)) {
        cout << "Ese DUI ya ha sido registrado.\n";
        return false;
    }

    return true; // Todo está bien
}



// Función que genera un código numérico aleatorio de longitud dada (por defecto 6 dígitos)
inline string generarCodigoRecuperacion(int longitud = 6) {
    // Inicializo un string vacío para el código
    string codigo;

    // Recorro desde 0 hasta longitud-1
    for (int i = 0; i < longitud; ++i)
        // Agrego un dígito aleatorio (0 a 9) al código en formato string
        codigo += to_string(rand() % 10);

    // Retorno el código generado
    return codigo;
}

// Función que registra un usuario pidiendo todos los datos necesarios y validándolos uno a uno
inline bool registrarUsuario() {

    // Declaro variables para guardar temporalmente los datos que el usuario ingrese
    string nombre, password, fechaNacimiento, genero, dui;
    limpiarConsola(); // Uso la función que ya tengo para limpiar pantalla antes de mostrar el registro
    // Muestro mensaje inicial para indicar registro nuevo
    cout << "\n=== Registro de nuevo usuario ===\n";

    // Pido y valido nombre: que sea válido y que no exista ya en archivo
    do {
        cout << "Nombre de usuario: ";
        getline(cin, nombre);

        // Verifico que el nombre solo tenga letras y espacios, sino aviso y repito
        if (!nombreValido(nombre)) {
            cout << "Nombre inválido. Solo letras y espacios.\n";
            nombre.clear(); 
            continue;
        }

        // Verifico que el nombre no esté ya registrado (normalizo antes)
        if (existeUsuario(normalizar(nombre))) {
            cout << "Ese nombre ya está registrado. Intenta otro.\n";
            nombre.clear(); // Limpio para repetir el ciclo
            continue;
        }
    } while (nombre.empty()); // Repetir hasta que el nombre sea válido y no esté vacío

    // Pido y valido fecha de nacimiento, además verifico que sea mayor de 18
    do {
        cout << "Fecha de nacimiento (DD/MM/AAAA): ";
        getline(cin, fechaNacimiento);

        // Si no es mayor de edad, muestro mensaje y limpio la variable para repetir
        if (!esMayorDeEdad(fechaNacimiento)) {
            cout << "Debes ser mayor de 18 años para registrarte.\n";
            fechaNacimiento.clear();
        }
    } while (fechaNacimiento.empty()); // Repetir hasta que se ingrese una fecha válida

  // Pido y valido DUI, que tenga formato correcto y que no esté repetido
    do {
    cout << "DUI (formato 12345678-9): ";
    getline(cin, dui);

    // Si el DUI no es válido o está repetido, aviso y limpio para repetir
    if (!duiValido(dui)) {
        cout << "DUI inválido o ya registrado. Intenta nuevamente.\n";
        dui.clear(); // Esto asegura que el ciclo se repita
    }
    } while (dui.empty()); // Repetir hasta ingresar DUI válido

    // Pido y valido género, solo acepto M, F u O (mayúscula o minúscula)
    do {
        cout << "Género (M/F/O): ";
        getline(cin, genero);

        if (genero != "M" && genero != "F" && genero != "O" &&
            genero != "m" && genero != "f" && genero != "o") {
            cout << "Género inválido. Usa M, F u O.\n";
            genero.clear();
        }
    } while (genero.empty()); // Repetir hasta ingresar género válido

    // Pido y valido contraseña, mínimo 8 caracteres
    do {
        cout << "Crea una contraseña (mínimo 8 caracteres): ";
        getline(cin, password);

        if (password.length() < 8) {
            cout << "La contraseña debe tener al menos 8 caracteres.\n";
            password.clear();
        }
    } while (password.empty()); // Repetir hasta ingresar contraseña válida

    // Genero un código aleatorio para recuperación de contraseña
    string codigo = generarCodigoRecuperacion();

    // Guardo el usuario en el archivo con todos sus datos
    guardarUsuario(nombre, password, codigo, fechaNacimiento, genero, dui);

    // Confirmo que el registro fue exitoso y muestro el código para que lo guarde el usuario
    cout << "¡Registro exitoso!\n";
    cout << "Tu código de recuperación es: " << codigo << "\nGuárdalo bien.\n";

    // Retorno true porque el registro fue exitoso
    return true;
}

// Función que inicia sesión pidiendo nombre y contraseña, validando en archivo usuarios.txt
inline bool iniciarSesion(string& jugador) {

    // Abro el archivo para lectura
    ifstream archivo("./documentos/usuarios.txt");

    // Si no se pudo abrir, aviso error y retorno falso
    if (!archivo.is_open()) {
        cout << "Error al abrir archivo de usuarios.\n";
        return false;
    }

    // Variables para guardar nombre y contraseña ingresadas
    string nombreIngresado, passIngresada;
     limpiarConsola(); // Uso la función que ya tengo para limpiar pantalla antes de mostrar el login
    // Muestro encabezado para iniciar sesión
    cout << "\n=== Iniciar sesión ===\n";
    cout << "Nombre de usuario: ";
    getline(cin, nombreIngresado);
    cout << "Contraseña: ";
    getline(cin, passIngresada);

    // Normalizo el nombre ingresado para comparar
    string nombreIngresadoNorm = normalizar(nombreIngresado);

    // Variable para leer líneas del archivo
    string linea;

    // Recorro línea por línea buscando el usuario y contraseña correctos
    while (getline(archivo, linea)) {
        // Cuando encuentro un bloque de usuario
        if (linea == "====== Usuario ======") {
            // Leo nombre y normalizo
            getline(archivo, linea);
            string nombreArchivo = normalizar(trim(linea.substr(8)));

            // Leo contraseña
            getline(archivo, linea);
            string passArchivo = trim(linea.substr(13));

            // Salto las líneas de código y cierre que no necesito aquí
            getline(archivo, linea);
            getline(archivo, linea);

            // Si el nombre y contraseña coinciden con lo ingresado, inicio sesión
            if (nombreArchivo == nombreIngresadoNorm && passArchivo == passIngresada) {
                // Guardo el nombre original sin normalizar en jugador para usarlo después
                jugador = nombreIngresado;

                // Doy la bienvenida
                cout << "¡Bienvenido, " << jugador << "!\n";
                cout << "==========================\n";

                // Retorno true porque el inicio fue exitoso
                return true;
            }
        }
    }

    // Si terminé de buscar y no encontré coincidencias, aviso error
    cout << "Credenciales incorrectas.\n";

    // Limpio variable jugador porque no hay usuario válido
    jugador.clear();

    // Retorno false porque no inicié sesión
    return false;
}

// Función que verifica que el código de recuperación y nombre coincidan y si sí devuelve la contraseña
inline bool verificarCodigoRecuperacion(const string& nombre, const string& codigo, string& password) {

    // Abro archivo para lectura
    ifstream archivo("./documentos/usuarios.txt");

    // Si no puedo abrir, retorno falso
    if (!archivo.is_open()) return false;

    // Normalizo el nombre para comparar
    string nombreNorm = normalizar(nombre);

    // Variable para leer líneas
    string linea;

    // Leo línea por línea buscando usuario y código coincidentes
    while (getline(archivo, linea)) {
        if (linea == "====== Usuario ======") {

            // Leo nombre y normalizo
            getline(archivo, linea);
            string nombreArchivo = normalizar(trim(linea.substr(8)));

            // Leo contraseña para guardarla si coincide
            getline(archivo, linea);
            string passArchivo = trim(linea.substr(13));

            // Leo código de recuperación
            getline(archivo, linea);
            string codigoArchivo = trim(linea.substr(8));

            // Salto línea vacía
            getline(archivo, linea);

            // Si el nombre y código coinciden, guardo la contraseña en variable y retorno true
            if (nombreArchivo == nombreNorm && codigoArchivo == codigo) {
                password = passArchivo;
                return true;
            }
        }
    }

    // Si no encontré coincidencia, retorno false
    return false;
}

// Función que actualiza la contraseña de un usuario en el archivo usuarios.txt
inline void actualizarContrasena(const string& nombre, const string& nuevaPass) {

    // Abro archivo original para lectura
    ifstream archivo("./documentos/usuarios.txt");

    // Abro archivo temporal para escritura
    ofstream temp("./documentos/temp.txt");

    // Variable para leer líneas
    string linea;

    // Leo línea por línea el archivo original
    while (getline(archivo, linea)) {

        // Cuando encuentro bloque de usuario
        if (linea == "====== Usuario ======") {

            // Copio el encabezado al temporal
            temp << linea << '\n';

            // Leo nombre
            getline(archivo, linea);
            string nombreArchivo = trim(linea.substr(8));
            temp << "Nombre: " << nombreArchivo << '\n';

            // Leo contraseña (la voy a cambiar si corresponde)
            getline(archivo, linea);
            string passArchivo = trim(linea.substr(13));

            // Leo código de recuperación
            getline(archivo, linea);
            string codigoArchivo = trim(linea.substr(8));

            // Leo línea vacía de cierre
            getline(archivo, linea);

            // Si este es el usuario que quiero actualizar, escribo la nueva contraseña
            if (nombreArchivo == nombre) {
                temp << "Contraseña: " << nuevaPass << '\n';
            } else {
                // Si no es, escribo la contraseña original
                temp << "Contraseña: " << passArchivo << '\n';
            }

            // Escribo el código original y la línea de cierre
            temp << "Código: " << codigoArchivo << '\n';

        } else {
            // Si no es línea de bloque usuario, copio línea normal
            temp << linea << '\n';
        }
    }

    // Cierro archivos
    archivo.close();
    temp.close();

    // Reemplazo archivo original con el temporal
    remove("./documentos/usuarios.txt");
    rename("./documentos/temp.txt", "./documentos/usuarios.txt");
}

// Función que permite al usuario recuperar su contraseña usando el código de recuperación
inline void recuperarContrasena() {

    // Variables para datos que pediremos
    string nombre, codigo, password;
    limpiarConsola(); // Uso la función que ya tengo para limpiar pantalla antes de mostrar recuperar
    // Mensaje inicial para recuperación
    cout << "\n====== Recuperar Contraseña ======\n";

    // Pido nombre de usuario
    cout << "Nombre de usuario: ";
    getline(cin, nombre);

    // Pido código de recuperación
    cout << "Ingresa tu código de recuperación: ";
    getline(cin, codigo);

    // Limpio espacios en entradas
    nombre = trim(nombre);
    codigo = trim(codigo);

    // Verifico si el código y nombre coinciden en archivo
    if (verificarCodigoRecuperacion(nombre, codigo, password)) {

        // Si es correcto, muestro la contraseña actual
        cout << "¡Código correcto! Tu contraseña actual es: " << password << "\n";

        // Variables para la nueva contraseña y confirmación
        string nuevaPass, confirmar;

        // Pregunto si desea cambiar contraseña
        cout << "\n¿Deseas cambiar tu contraseña? (s/n): ";
        string respuesta;
        getline(cin, respuesta);

        // Si responde sí (s o S)
        if (respuesta == "s" || respuesta == "S") {

            // Pido nueva contraseña
            cout << "Nueva contraseña: ";
            getline(cin, nuevaPass);

            // Pido confirmación
            cout << "Confirma tu nueva contraseña: ";
            getline(cin, confirmar);

            // Verifico que coincidan y no estén vacías
            if (nuevaPass == confirmar && !nuevaPass.empty()) {

                // Actualizo la contraseña en el archivo
                actualizarContrasena(nombre, nuevaPass);

                // Confirmo actualización
                cout << "¡Contraseña actualizada exitosamente!\n";
            } else {
                // Si no coinciden o están vacías, aviso que no actualicé nada
                cout << "Las contraseñas no coinciden o están vacías. No se actualizó nada.\n";
            }
        } else {
            // Si no desea cambiar, aviso que sigue con la misma contraseña
            cout << "No se hizo ningún cambio. Puedes seguir usando tu contraseña actual.\n";
        }

    } else {
        // Si código o nombre no coinciden, aviso error
        cout << "Usuario o código incorrecto.\n";
    }
}

#endif // USER_MANAGER_H
