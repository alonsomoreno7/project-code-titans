#ifndef ROULETTE_GAME_H   
#define ROULETTE_GAME_H   

#include <string>         // Uso strings para manejar texto en el juego
#include <iostream>       // Para imprimir y leer desde la consola (cout, cin)
#include <cmath>          // Uso funciones matemáticas como cos, sin, y la constante M_PI
#include <limits>         // Uso para limpiar buffer de entrada y manejar límites
#include <cstdlib>        // Uso para generar números aleatorios con rand()

#include "gameConstants.h" // Incluyo constantes y variables globales del juego, como números y colores
#include "utils.h"         // Uso funciones auxiliares para texto, consola y pausas
#include "playerData.h"    // Uso funciones para registrar resultados y guardar el saldo del jugador
#include "jugador.h"       // Uso la estructura Jugador con sus atributos y métodos

using namespace std;      // Para no tener que escribir std:: en cada uso

inline void calcularPosiciones() {  // Función que calcula la posición X, Y de cada número en la ruleta
    for (int i = 0; i < NUMEROS; i++) {  // Recorro todos los números de la ruleta
        double angulo = (2 * M_PI * i / NUMEROS) - M_PI / 2; // Calculo el ángulo para colocar el número i
        posiciones[i].x = CENTRO_X + int(RADIO * cos(angulo) * 1.9); // Calcula la posición X (ajustada)
        posiciones[i].y = CENTRO_Y + int(RADIO * sin(angulo));       // Calcula la posición Y
    }
}

inline void imprimirCanvas(int iluminado) {  // Función para dibujar la ruleta en consola
    string canvas[HEIGHT][WIDTH];  // Creo un "canvas" 2D para almacenar caracteres por posición

    for (int i = 0; i < HEIGHT; i++)  // Recorro filas
        for (int j = 0; j < WIDTH; j++)  // Recorro columnas
            canvas[i][j] = " ";  // Inicializo cada celda con espacio vacío

    for (int i = 0; i < NUMEROS; i++) {  // Para cada número en la ruleta
        int x = posiciones[i].x;  // Obtengo su posición X
        int y = posiciones[i].y;  // Obtengo su posición Y
        string color = (colores[i] == 'R') ? rojo : (colores[i] == 'N') ? negro : verde; // Asigno color según arreglo

        if (i == iluminado) color = fondo_blanco + color;  // Si está iluminado, cambio fondo a blanco

        string numStr = (numeros[i] < 10 ? " " : "") + to_string(numeros[i]);  // Formateo el número para alinearlo

        if (x >= 0 && x + 1 < WIDTH && y >= 0 && y < HEIGHT) {  // Verifico que esté dentro del canvas
            canvas[y][x] = color + numStr + reset;  // Pongo el número coloreado en la posición
            canvas[y][x + 1] = "";  // Limpio la celda adyacente para evitar errores visuales
        }
    }

    for (int r = 1; r < RADIO - 2; r++) {  // Para radios internos para decoración
        for (int a = 0; a < 360; a += 15) {  // Cada 15 grados
            double rad = a * M_PI / 180.0;  // Convierto grados a radianes
            int x = CENTRO_X + int(r * cos(rad) * 0.5);  // Calculo posición X
            int y = CENTRO_Y + int(r * sin(rad));        // Calculo posición Y
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)  // Verifico dentro del canvas
                canvas[y][x] = ".";  // Pongo un punto para decorar
        }
    }

    canvas[CENTRO_Y][CENTRO_X] = "O";  // Pongo una 'O' en el centro para marcar el eje

    for (int i = 0; i < HEIGHT; i++) {  // Recorro filas para imprimir
        string linea = "";  // Inicializo la línea vacía
        for (int j = 0; j < WIDTH; j++) {  // Recorro columnas
            if (!canvas[i][j].empty()) linea += canvas[i][j];  // Concateno si hay algo
        }
        cout << linea << "\n";  // Imprimo la línea completa
    }
}

inline string pedirTipoApuesta() {  // Función para pedir el tipo de apuesta y validar
    string tipo;  // Variable donde guardo la opción
    while (true) {  // Bucle hasta que el usuario ingrese una opción válida
        cout << "\n╔══════════════════════════════════════╗\n";  // Muestro menú con bordes
        cout << "║         MENÚ DE APUESTAS             ║\n";
        cout << "╠══════════════════════════════════════╣\n";
        cout << "║  1. Número exacto      →  paga 35x   ║\n";
        cout << "║  2. Color (Rojo/Negro) →  paga 2x    ║\n";
        cout << "║  3. Par o Impar        →  paga 2x    ║\n";
        cout << "╚══════════════════════════════════════╝\n";
        cout << "→ Escoge una opción: ";  // Pido la opción
        cin >> tipo;  // Leo la opción del usuario
        tipo = toLower(tipo);  // Paso a minúscula para evitar errores

        if (tipo == "1" || tipo == "2" || tipo == "3")  // Si es una opción válida
            return tipo;  // La retorno y salgo
        else
            cout << "Opción inválida, intenta de nuevo.\n";  // Mensaje de error y repito
    }
}

inline int pedirNumero() {  // Función para pedir un número válido de apuesta (0-36)
    int num;  // Variable donde guardo el número
    while (true) {  // Hasta que sea válido
        cout << "Ingresa el número (0-36): ";  // Pido el número
        if (cin >> num) {  // Si el usuario ingresó un número entero
            if (num >= 0 && num <= 36)  // Si está dentro del rango válido
                return num;  // Retorno el número
            else
                cout << "Número inválido. Debe estar entre 0 y 36.\n";  // Si no, muestro error
        } else {
            cout << "Entrada inválida. Ingresa un número entero.\n";  // Si no ingresó número
            cin.clear();  // Limpio el estado de error de cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoro el resto del buffer
        }
    }
}

inline char pedirColor() {  // Función para pedir el color de la apuesta (rojo o negro)
    string color;  // Variable temporal para leer texto
    while (true) {  // Repetir hasta recibir respuesta válida
        cout << "Ingresa el color (Rojo / Negro): ";  // Pido el color
        cin >> color;  // Leo la entrada
        color = toLower(color);  // Paso a minúsculas para comparar
        if (color == "rojo")  // Si es rojo
            return 'R';  // Retorno código 'R'
        else if (color == "negro")  // Si es negro
            return 'N';  // Retorno código 'N'
        else
            cout << "Color inválido. Solo 'Rojo' o 'Negro'.\n";  // Mensaje error
    }
}

inline char pedirParidad() {  // Función para pedir si apuesta a par o impar
    string paridad;  // Variable temporal para la respuesta
    while (true) {  // Hasta respuesta válida
        cout << "¿Par o Impar?: ";  // Pido la opción
        cin >> paridad;  // Leo entrada
        paridad = toLower(paridad);  // Paso a minúsculas
        if (paridad == "par")  // Si es par
            return 'P';  // Retorno código 'P'
        else if (paridad == "impar")  // Si es impar
            return 'I';  // Retorno código 'I'
        else
            cout << "Opción inválida. Solo 'Par' o 'Impar'.\n";  // Mensaje error
    }
}

inline void jugarRuleta(Jugador& jugador) {  // Función principal que maneja la ruleta completa
    calcularPosiciones();  // Calculo las posiciones para dibujar la ruleta en pantalla

    while (jugador.dinero > 0) {  // Mientras el jugador tenga dinero para apostar
        if (jugador.dinero <= 0) {  // Reviso de nuevo por si ya se quedó sin dinero
            cout << "No tienes dinero para jugar Ruleta.\n";  // Mensaje de advertencia
            return;  // Salgo de la función porque no puede seguir
        }

        int apuesta;  // Variable para guardar la apuesta del jugador
        cout << "Tu dinero actual es $" << jugador.dinero << ". Ingresa tu apuesta (mínimo $10, máximo $500): $";

        while (true) {  // Valido que la apuesta sea correcta
            cin >> apuesta;  // Leo apuesta
            // Si falla o está fuera del rango o excede saldo
            if (cin.fail() || apuesta < 10 || apuesta > 500 || apuesta > jugador.dinero) {
                cin.clear();  // Limpio error de cin
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignoro buffer
                cout << "Apuesta inválida. Debe ser entre $10 y $500 y no puede exceder tu saldo actual.\n";
                cout << "Tu dinero actual es $" << jugador.dinero << ". Ingresa tu apuesta: $";
                continue;  // Vuelvo a pedir apuesta
            }
            break;  // Salgo si es válida
        }

        jugador.partidasJugadas++;  // Aumento la cuenta de partidas jugadas

        string tipo = pedirTipoApuesta();  // Pido tipo de apuesta (número, color, paridad)
        int eleccion = -1;  // Inicializo para número exacto
        string resumen;  // Para imprimir resumen de la apuesta
        char colorElegido = 0;  // Inicializo para color
        char paridadElegida = 0;  // Inicializo para paridad

        if (tipo == "1") {  // Si apuesta a número
            eleccion = pedirNumero();  // Pido número elegido
            resumen = "Apuesta: al número " + to_string(eleccion);  // Creo resumen
        } else if (tipo == "2") {  // Si apuesta a color
            colorElegido = pedirColor();  // Pido color elegido
            resumen = "Apuesta: al color " + string((colorElegido == 'R') ? "Rojo" : "Negro") + " | Monto: $" + to_string(apuesta);
        } else {  // Si apuesta a par o impar
            paridadElegida = pedirParidad();  // Pido paridad elegida
            resumen = "Apuesta: a " + string((paridadElegida == 'P') ? "par" : "impar") + " | Monto: $" + to_string(apuesta);
        }

        cout << "\n" << resumen << "\nGirando la ruleta...\n";  // Muestro resumen y aviso que gira

        int ganador = rand() % NUMEROS;  // Genero número ganador aleatorio (0 a 36)
        int vueltas = 3;  // Defino cuántas vueltas dará la ruleta para la animación
        int totalPasos = vueltas * NUMEROS + ganador;  // Total pasos para animar giro y detenerse en ganador
        int iluminado = 0;  // Número iluminado (simula la bola girando)

        for (int paso = 0; paso <= totalPasos; paso++) {  // Bucle que anima la ruleta girando
            limpiarConsola();  // Limpio pantalla para mostrar siguiente frame
            cout << "\nSaldo actual: $" << jugador.dinero << "\n";  // Muestro saldo
            cout << resumen << "\n";  // Muestro apuesta
            imprimirCanvas(iluminado);  // Dibujo ruleta con número iluminado
            iluminado = (iluminado + 1) % NUMEROS;  // Paso al siguiente número iluminado

            // Pausas para hacer que la ruleta frene suavemente
            if (paso > totalPasos - 10) esperarMs(200);
            else if (paso > totalPasos - 20) esperarMs(150);
            else esperarMs(60);
        }

        int numGanador = numeros[ganador];  // Número ganador real
        char colorGanador = colores[ganador];  // Color ganador

        cout << "\nLa ruleta cayó en el número " << numGanador << " (";
        cout << (colorGanador == 'R' ? "Rojo" : colorGanador == 'N' ? "Negro" : "Verde") << ")\n";  // Muestro resultado

        bool gano = false;  // Variable para saber si ganó

        // Verifico si el jugador ganó según su tipo de apuesta
        if (tipo == "1" && numGanador == eleccion) {  // Apuesta a número exacto y coincide
            cout << "¡Ganaste 35 veces tu apuesta!\n";
            jugador.dinero += apuesta * 35;  // Pago 35 veces la apuesta
            jugador.partidasGanadas++;  // Aumento partidas ganadas
            gano = true;
        } else if (tipo == "2" && colorGanador == colorElegido) {  // Apuesta a color y coincide
            cout << "¡Ganaste 2 veces tu apuesta!\n";
            jugador.dinero += apuesta * 2;  // Pago 2 veces la apuesta
            jugador.partidasGanadas++;
            gano = true;
        } else if (tipo == "3") {  // Apuesta a par o impar
            if (numGanador != 0) {  // El 0 no cuenta para par/impar
                if ((paridadElegida == 'P' && numGanador % 2 == 0) ||
                    (paridadElegida == 'I' && numGanador % 2 != 0)) {
                    cout << "¡Ganaste 2 veces tu apuesta!\n";
                    jugador.dinero += apuesta * 2;
                    jugador.partidasGanadas++;
                    gano = true;
                }
            }
        }

        if (!gano) {  // Si no ganó
            cout << "No ganaste esta vez.\n";
            jugador.dinero -= apuesta;  // Pierde la apuesta
            jugador.partidasPerdidas++;  // Aumento partidas perdidas
        }

        cout << "\nSaldo actualizado: $" << jugador.dinero << "\n";  // Muestro saldo actualizado
        guardarSaldo(jugador.nombre, jugador.dinero);  // Guardo saldo en archivo
        jugador.actualizarEstadisticas();  // Actualizo estadísticas internas

        // Registro la partida jugada en el historial con resultado y saldo
        guardarJuego("Ruleta", jugador.nombre, apuesta, gano ? 1 : 0, jugador.dinero);

        if (!preguntarSeguir()) break;  // Pregunto si quiere seguir jugando, si no, salgo
    }

    if (jugador.dinero <= 0) {  // Si se quedó sin dinero
        cout << "\nTe has quedado sin dinero. Juego terminado.\n";  // Mensaje final
        guardarSaldo(jugador.nombre, jugador.dinero);  // Guardo saldo final
        jugador.actualizarEstadisticas();  // Actualizo estadísticas
    }

    cout << "\nGracias por jugar. Tu saldo final fue: $" << jugador.dinero << "\n";  // Mensaje de despedida
}

#endif // ROULETTE_GAME_H  
