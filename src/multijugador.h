#ifndef MULTIJUGADOR_H 
#define MULTIJUGADOR_H 

#include <iostream> // Incluyo para poder usar cin y cout
#include <cstdlib>  // Incluyo para funciones como rand y srand
#include <ctime>    // Incluyo para usar time y generar números aleatorios con srand
#include <algorithm> // Incluyo para usar funciones como swap y copy

using namespace std; // Uso el espacio de nombres estándar para no escribir std:: en todo

const int MAX_CARTAS = 16; // Defino el número total de cartas que usaré en el juego de memoria
const int MAX_NUMEROS = 8; // Defino el número de elementos para el puzzle de números

// Defino una estructura para representar a cada jugador en los minijuegos
struct JugadorMinijuego {
    string nombre; // Aquí guardo el nombre del jugador
    int puntuacion = 0; // Inicializo su puntuación en 0
};

// Declaro las funciones que usaré más abajo en el mismo archivo
void menuMinijuegos(JugadorMinijuego& j1, JugadorMinijuego& j2);
void juegoMemoria(JugadorMinijuego& j1, JugadorMinijuego& j2);
void juegoEstrategia(JugadorMinijuego& j1, JugadorMinijuego& j2);
void puzzleNumeros(JugadorMinijuego& j1, JugadorMinijuego& j2);
void mostrarGanador(JugadorMinijuego& j1, JugadorMinijuego& j2);
void mezclarArreglo(int arreglo[], int tamano);
bool estaOrdenado(int arreglo[], int tamano);

// Implemento una función para mezclar los valores de un arreglo aleatoriamente
void mezclarArreglo(int arreglo[], int tamano) {
    for (int i = tamano - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Elijo un índice aleatorio entre 0 y i
        swap(arreglo[i], arreglo[j]); // Intercambio los valores de las posiciones i y j
    }
}

// Implemento una función para verificar si un arreglo está ordenado de menor a mayor
bool estaOrdenado(int arreglo[], int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        if (arreglo[i] > arreglo[i + 1]) {
            return false; // Si encuentro un elemento mayor que el siguiente, el arreglo no está ordenado
        }
    }
    return true; // Si todo está bien, devuelvo true
}

// Aquí defino el menú de minijuegos donde los jugadores pueden elegir qué jugar
void menuMinijuegos(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    int opcion;
    do {
        // Muestro las opciones disponibles
        cout << "\n=== MENU DE MINIJUEGOS ===";
        cout << "\n1. Juego de Memoria";
        cout << "\n2. Juego de Estrategia";
        cout << "\n3. Puzzle de Números";
        cout << "\n4. Ver puntuaciones";
        cout << "\n5. Salir";
        cout << "\nSelecciona un juego: ";
        
        cin >> opcion; // Leo la opción que selecciona el jugador
        
        switch(opcion) {
            case 1:
                juegoMemoria(j1, j2); // Llamo al juego de memoria
                break;
            case 2:
                juegoEstrategia(j1, j2); // Llamo al juego de estrategia
                break;
            case 3:
                puzzleNumeros(j1, j2); // Llamo al puzzle de números
                break;
            case 4:
                mostrarGanador(j1, j2); // Muestro quién va ganando
                break;
            case 5:
                cout << "Volviendo al menu principal...\n"; // Mensaje de despedida
                break;
            default:
                cout << "Opcion invalida. Intenta nuevamente.\n"; // Si no elige una opción válida
        }
    } while(opcion != 5); // Repetir mientras no elijan salir
}

// Aquí defino el juego de memoria donde deben emparejar cartas iguales
void juegoMemoria(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    cout << "\n=== JUEGO DE MEMORIA ===";
    cout << "\nEncuentra todas las parejas para ganar puntos!\n";
    
    // Inicializo las cartas con pares del 1 al 8
    int cartas[MAX_CARTAS] = {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8};
    bool reveladas[MAX_CARTAS] = {false}; // Todas las cartas empiezan ocultas
    mezclarArreglo(cartas, MAX_CARTAS); // Mezclo las cartas

    int parejasEncontradas = 0; // Inicio el contador de parejas
    int turno = 0; // 0 es jugador 1, 1 es jugador 2

    while(parejasEncontradas < 8) { // El juego sigue hasta encontrar 8 parejas
        JugadorMinijuego& jugadorActual = (turno == 0) ? j1 : j2; // Determino quién juega
        cout << "\nTurno de " << jugadorActual.nombre << endl;

        // Muestro el tablero
        cout << "Tablero:\n";
        for(int i = 0; i < MAX_CARTAS; i++) {
            if(reveladas[i])
                cout << cartas[i] << " "; // Si está revelada, muestro el número
            else
                cout << "* "; // Si está oculta, muestro asterisco

            if((i+1) % 4 == 0) cout << endl; // Hago salto de línea cada 4 cartas
        }

        // Pido dos posiciones
        int pos1, pos2;
        cout << "Selecciona dos cartas (0-15): ";
        cin >> pos1 >> pos2;

        // Verifico que las posiciones sean válidas
        if(pos1 < 0 || pos1 >= MAX_CARTAS || pos2 < 0 || pos2 >= MAX_CARTAS || 
           pos1 == pos2 || reveladas[pos1] || reveladas[pos2]) {
            cout << "Seleccion invalida. Pierdes tu turno.\n";
            turno = 1 - turno; // Cambio de turno
            continue;
        }

        // Revelo las cartas seleccionadas
        reveladas[pos1] = true;
        reveladas[pos2] = true;

        cout << "Seleccionaste: " << cartas[pos1] << " y " << cartas[pos2] << endl;

        if(cartas[pos1] == cartas[pos2]) {
            cout << "¡Encontraste una pareja! +10 puntos\n";
            jugadorActual.puntuacion += 10;
            parejasEncontradas++;
        } else {
            cout << "No es una pareja. Turno del siguiente jugador.\n";
            reveladas[pos1] = false;
            reveladas[pos2] = false;
            turno = 1 - turno; // Cambio de turno
        }
    }

    cout << "\n¡Juego terminado!\n";
    mostrarGanador(j1, j2); // Muestro el ganador al final del juego
}

// Aquí defino el juego de estrategia donde no deben pasarse de 21
void juegoEstrategia(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    cout << "\n=== JUEGO DE ESTRATEGIA ===";
    cout << "\nEl ultimo en sumar menos de 21 gana!\n";

    int total = 0;
    int turno = 0;

    while(total < 21) {
        JugadorMinijuego& jugadorActual = (turno == 0) ? j1 : j2;
        int suma;

        cout << "\nTotal acumulado: " << total << endl;
        cout << jugadorActual.nombre << ", suma entre 1 y 5: ";
        cin >> suma;

        if(suma < 1 || suma > 5) {
            cout << "Suma invalida. Debe ser entre 1 y 5.\n";
            continue;
        }

        total += suma;
        turno = 1 - turno;
    }

    JugadorMinijuego& ganador = (turno == 0) ? j1 : j2;
    cout << "\n¡" << ganador.nombre << " gana 15 puntos por estrategia!\n";
    ganador.puntuacion += 15;

    mostrarGanador(j1, j2);
}

// Aquí defino el puzzle de números donde tienen que ordenar del 1 al 8
void puzzleNumeros(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    cout << "\n=== PUZZLE DE NUMEROS ===";
    cout << "\nOrdena los números del 1 al 8 lo más rápido posible!\n";

    int numeros[MAX_NUMEROS] = {1,2,3,4,5,6,7,8};
    mezclarArreglo(numeros, MAX_NUMEROS);

    int intentosJ1 = 0, intentosJ2 = 0;

    // Turno del jugador 1
    cout << "\nTurno de " << j1.nombre << endl;
    int copiaJ1[MAX_NUMEROS];
    copy(numeros, numeros + MAX_NUMEROS, copiaJ1);

    while(!estaOrdenado(copiaJ1, MAX_NUMEROS)) {
        cout << "Secuencia actual: ";
        for(int i = 0; i < MAX_NUMEROS; i++) cout << copiaJ1[i] << " ";
        cout << endl;

        int pos1, pos2;
        cout << "Ingresa dos posiciones para intercambiar (0-7): ";
        cin >> pos1 >> pos2;

        if(pos1 < 0 || pos1 >= MAX_NUMEROS || pos2 < 0 || pos2 >= MAX_NUMEROS) {
            cout << "Posiciones invalidas. Intenta nuevamente.\n";
            continue;
        }

        swap(copiaJ1[pos1], copiaJ1[pos2]);
        intentosJ1++;
    }

    // Turno del jugador 2
    cout << "\nTurno de " << j2.nombre << endl;
    int copiaJ2[MAX_NUMEROS];
    copy(numeros, numeros + MAX_NUMEROS, copiaJ2);

    while(!estaOrdenado(copiaJ2, MAX_NUMEROS)) {
        cout << "Secuencia actual: ";
        for(int i = 0; i < MAX_NUMEROS; i++) cout << copiaJ2[i] << " ";
        cout << endl;

        int pos1, pos2;
        cout << "Ingresa dos posiciones para intercambiar (0-7): ";
        cin >> pos1 >> pos2;

        if(pos1 < 0 || pos1 >= MAX_NUMEROS || pos2 < 0 || pos2 >= MAX_NUMEROS) {
            cout << "Posiciones invalidas. Intenta nuevamente.\n";
            continue;
        }

        swap(copiaJ2[pos1], copiaJ2[pos2]);
        intentosJ2++;
    }

    if(intentosJ1 < intentosJ2) {
        cout << "\n¡" << j1.nombre << " gana con " << intentosJ1 << " intentos! +20 puntos\n";
        j1.puntuacion += 20;
    } else if(intentosJ2 < intentosJ1) {
        cout << "\n¡" << j2.nombre << " gana con " << intentosJ2 << " intentos! +20 puntos\n";
        j2.puntuacion += 20;
    } else {
        cout << "\n¡Empate! Ambos ganan 10 puntos\n";
        j1.puntuacion += 10;
        j2.puntuacion += 10;
    }

    mostrarGanador(j1, j2);
}

// Función para mostrar quién va ganando
void mostrarGanador(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    cout << "\n=== PUNTUACIONES ===";
    cout << "\n" << j1.nombre << ": " << j1.puntuacion << " puntos";
    cout << "\n" << j2.nombre << ": " << j2.puntuacion << " puntos\n";

    if(j1.puntuacion > j2.puntuacion) {
        cout << "\n¡" << j1.nombre << " va ganando!\n";
    } else if(j2.puntuacion > j1.puntuacion) {
        cout << "\n¡" << j2.nombre << " va ganando!\n";
    } else {
        cout << "\n¡Estan empatados!\n";
    }
}

// Esta es la función principal para el modo multijugador
void modoMultijugador() {
    string nombre1, nombre2;

    cout << "\n=== MODO MULTIJUGADOR (Minijuegos) ===";
    cout << "\nJugador 1, ingresa tu nombre: ";
    cin >> nombre1;
    cout << "Jugador 2, ingresa tu nombre: ";
    cin >> nombre2;

    JugadorMinijuego j1 = {nombre1};
    JugadorMinijuego j2 = {nombre2};

    srand(time(nullptr)); // Inicializo la semilla aleatoria
    menuMinijuegos(j1, j2); // Llamo al menú con los dos jugadores

    cout << "\n=== RESULTADO FINAL ===";
    mostrarGanador(j1, j2); // Muestro la puntuación final
}

#endif // MULTIJUGADOR_H
