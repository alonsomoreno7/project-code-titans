#ifndef MULTIJUGADOR_H
#define MULTIJUGADOR_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

const int MAX_CARTAS = 16; // Defino el número total de cartas para el juego de memoria
const int MAX_NUMEROS = 8; // Defino el número total de números para el puzzle

// Renombro la estructura para evitar conflictos con otras partes del código
struct JugadorMinijuego {
    string nombre; // Almaceno el nombre del jugador
    int puntuacion = 0; // Inicializo la puntuación del jugador en 0
};

// Prototipos de funciones que voy a implementar más adelante
void menuMinijuegos(JugadorMinijuego& j1, JugadorMinijuego& j2);
void juegoMemoria(JugadorMinijuego& j1, JugadorMinijuego& j2);
void juegoEstrategia(JugadorMinijuego& j1, JugadorMinijuego& j2);
void puzzleNumeros(JugadorMinijuego& j1, JugadorMinijuego& j2);
void mostrarGanador(JugadorMinijuego& j1, JugadorMinijuego& j2);
void mezclarArreglo(int arreglo[], int tamano);
bool estaOrdenado(int arreglo[], int tamano);

// Función para mezclar un arreglo
void mezclarArreglo(int arreglo[], int tamano) {
    for (int i = tamano - 1; i > 0; i--) {
        int j = rand() % (i + 1); // Genero un índice aleatorio
        swap(arreglo[i], arreglo[j]); // Intercambio los elementos
    }
}

// Función para verificar si un arreglo está ordenado
bool estaOrdenado(int arreglo[], int tamano) {
    for (int i = 0; i < tamano - 1; i++) {
        if (arreglo[i] > arreglo[i + 1]) {
            return false; // Si encuentro un elemento mayor que el siguiente, no está ordenado
        }
    }
    return true; // Si todo está en orden, retorno verdadero
}

// Menú principal donde elijo qué minijuego jugar
void menuMinijuegos(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    int opcion;
    do {
        cout << "\n=== MENU DE MINIJUEGOS ===";
        cout << "\n1. Juego de Memoria";
        cout << "\n2. Juego de Estrategia";
        cout << "\n3. Puzzle de Números";
        cout << "\n4. Ver puntuaciones";
        cout << "\n5. Salir";
        cout << "\nSelecciona un juego: ";
        
        cin >> opcion; // Leo la opción elegida por el jugador
        
        switch(opcion) {
            case 1:
                juegoMemoria(j1, j2); // Llamo a la función del juego de memoria
                break;
            case 2:
                juegoEstrategia(j1, j2); // Llamo a la función del juego de estrategia
                break;
            case 3:
                puzzleNumeros(j1, j2); // Llamo a la función del puzzle de números
                break;
            case 4:
                mostrarGanador(j1, j2); // Muestro las puntuaciones actuales
                break;
            case 5:
                cout << "Volviendo al menu principal...\n"; // Mensaje de salida
                break;
            default:
                cout << "Opcion invalida. Intenta nuevamente.\n"; // Manejo de opciones inválidas
        }
    } while(opcion != 5); // Continúo hasta que elijo salir
}

// Juego de Memoria con arreglos
void juegoMemoria(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    cout << "\n=== JUEGO DE MEMORIA ===";
    cout << "\nEncuentra todas las parejas para ganar puntos!\n";
    
    int cartas[MAX_CARTAS] = {1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8}; // Inicializo las cartas
    bool reveladas[MAX_CARTAS] = {false}; // Inicializo el estado de las cartas como no reveladas
    mezclarArreglo(cartas, MAX_CARTAS); // Mezclo las cartas
    
    int parejasEncontradas = 0; // Contador de parejas encontradas
    int turno = 0; // 0 = jugador1, 1 = jugador2
    
    while(parejasEncontradas < 8) { // Mientras no se encuentren todas las parejas
        JugadorMinijuego& jugadorActual = (turno == 0) ? j1 : j2; // Determino quién es el jugador actual
        cout << "\nTurno de " << jugadorActual.nombre << endl;
        
        // Muestro el tablero
        cout << "Tablero:\n";
        for(int i = 0; i < MAX_CARTAS; i++) {
            if(reveladas[i]) {
                cout << cartas[i] << " "; // Muestro el número si la carta está revelada
            } else {
                cout << "* "; // Muestro un asterisco si la carta está oculta
            }
            if((i+1) % 4 == 0) cout << endl; // Cambio de línea cada 4 cartas
        }
        
        // Pido selecciones
        int pos1, pos2;
        cout << "Selecciona dos cartas (0-15): ";
        cin >> pos1 >> pos2;
        
        // Valido las posiciones seleccionadas
        if(pos1 < 0 || pos1 >= MAX_CARTAS || pos2 < 0 || pos2 >= MAX_CARTAS || 
           pos1 == pos2 || reveladas[pos1] || reveladas[pos2]) {
            cout << "Seleccion invalida. Pierdes tu turno.\n"; // Mensaje de error
            turno = 1 - turno; // Cambio de turno
            continue; // Vuelvo al inicio del bucle
        }
        
        // Revelo las cartas seleccionadas
        reveladas[pos1] = true;
        reveladas[pos2] = true;
        
        cout << "Seleccionaste: " << cartas[pos1] << " y " << cartas[pos2] << endl;
        
        // Verifico si las cartas son una pareja
        if(cartas[pos1] == cartas[pos2]) {
            cout << "¡Encontraste una pareja! +10 puntos\n";
            jugadorActual.puntuacion += 10; // Aumento la puntuación del jugador
            parejasEncontradas++; // Aumento el contador de parejas encontradas
        } else {
            cout << "No es una pareja. Turno del siguiente jugador.\n";
            reveladas[pos1] = false; // Vuelvo a ocultar las cartas
            reveladas[pos2] = false;
            turno = 1 - turno; // Cambio de turno
        }
    }
    
    cout << "\n¡Juego terminado!\n";
    mostrarGanador(j1, j2); // Muestro el ganador al final del juego
}

// Juego de Estrategia
void juegoEstrategia(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    cout << "\n=== JUEGO DE ESTRATEGIA ===";
    cout << "\nEl ultimo en sumar menos de 21 gana!\n";
    
    int total = 0; // Inicializo el total acumulado
    int turno = 0; // Alternar turnos
    
    while(total < 21) { // Mientras el total sea menor a 21
        JugadorMinijuego& jugadorActual = (turno == 0) ? j1 : j2; // Determino quién es el jugador actual
        int suma;
        
        cout << "\nTotal acumulado: " << total << endl;
        cout << jugadorActual.nombre << ", suma entre 1 y 5: ";
        cin >> suma; // Leo la suma que el jugador quiere agregar
        
        // Valido la suma
        if(suma < 1 || suma > 5) {
            cout << "Suma invalida. Debe ser entre 1 y 5.\n"; // Mensaje de error
            continue; // Vuelvo a pedir la suma
        }
        
        total += suma; // Aumento el total acumulado
        turno = 1 - turno; // Cambio de turno
    }
    
    // El jugador que NO causó que se pasara de 21 gana
    JugadorMinijuego& ganador = (turno == 0) ? j1 : j2; // Determino quién es el ganador
    cout << "\n¡" << ganador.nombre << " gana 15 puntos por estrategia!\n";
    ganador.puntuacion += 15; // Aumento la puntuación del ganador
    
    mostrarGanador(j1, j2); // Muestro el ganador
}

// Puzzle de Números con arreglos
void puzzleNumeros(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    cout << "\n=== PUZZLE DE NUMEROS ===";
    cout << "\nOrdena los números del 1 al 8 lo más rápido posible!\n";
    
    int numeros[MAX_NUMEROS] = {1,2,3,4,5,6,7,8}; // Inicializo los números
    mezclarArreglo(numeros, MAX_NUMEROS); // Mezclo los números
    
    int intentosJ1 = 0, intentosJ2 = 0; // Contadores de intentos para cada jugador
    
    // Turno del jugador 1
    cout << "\nTurno de " << j1.nombre << endl;
    int copiaJ1[MAX_NUMEROS];
    copy(numeros, numeros + MAX_NUMEROS, copiaJ1); // Copio los números a una copia para el jugador 1
    
    while(!estaOrdenado(copiaJ1, MAX_NUMEROS)) { // Mientras no esté ordenado
        cout << "Secuencia actual: ";
        for(int i = 0; i < MAX_NUMEROS; i++) cout << copiaJ1[i] << " "; // Muestro la secuencia actual
        cout << endl;
        
        cout << "Ingresa dos posiciones para intercambiar (0-7): ";
        int pos1, pos2;
        cin >> pos1 >> pos2; // Leo las posiciones a intercambiar
        
        if(pos1 < 0 || pos1 >= MAX_NUMEROS || pos2 < 0 || pos2 >= MAX_NUMEROS) {
            cout << "Posiciones invalidas. Intenta nuevamente.\n"; // Mensaje de error
            continue; // Vuelvo a pedir las posiciones
        }
        
        swap(copiaJ1[pos1], copiaJ1[pos2]); // Intercambio los números
        intentosJ1++; // Aumento el contador de intentos
    }
    
    // Turno del jugador 2
    cout << "\nTurno de " << j2.nombre << endl;
    int copiaJ2[MAX_NUMEROS];
    copy(numeros, numeros + MAX_NUMEROS, copiaJ2); // Copio los números a una copia para el jugador 2
    
    while(!estaOrdenado(copiaJ2, MAX_NUMEROS)) { // Mientras no esté ordenado
        cout << "Secuencia actual: ";
        for(int i = 0; i < MAX_NUMEROS; i++) cout << copiaJ2[i] << " "; // Muestro la secuencia actual
        cout << endl;
        
        cout << "Ingresa dos posiciones para intercambiar (0-7): ";
        int pos1, pos2;
        cin >> pos1 >> pos2; // Leo las posiciones a intercambiar
        
        if(pos1 < 0 || pos1 >= MAX_NUMEROS || pos2 < 0 || pos2 >= MAX_NUMEROS) {
            cout << "Posiciones invalidas. Intenta nuevamente.\n"; // Mensaje de error
            continue; // Vuelvo a pedir las posiciones
        }
        
        swap(copiaJ2[pos1], copiaJ2[pos2]); // Intercambio los números
        intentosJ2++; // Aumento el contador de intentos
    }
    
    // Determinar ganador
    if(intentosJ1 < intentosJ2) {
        cout << "\n¡" << j1.nombre << " gana con " << intentosJ1 << " intentos! +20 puntos\n";
        j1.puntuacion += 20; // Aumento la puntuación del jugador 1
    } else if(intentosJ2 < intentosJ1) {
        cout << "\n¡" << j2.nombre << " gana con " << intentosJ2 << " intentos! +20 puntos\n";
        j2.puntuacion += 20; // Aumento la puntuación del jugador 2
    } else {
        cout << "\n¡Empate! Ambos ganan 10 puntos\n";
        j1.puntuacion += 10; // Aumento la puntuación del jugador 1
        j2.puntuacion += 10; // Aumento la puntuación del jugador 2
    }
    
    mostrarGanador(j1, j2); // Muestro el ganador
}

// Mostrar resultados
void mostrarGanador(JugadorMinijuego& j1, JugadorMinijuego& j2) {
    cout << "\n=== PUNTUACIONES ===";
    cout << "\n" << j1.nombre << ": " << j1.puntuacion << " puntos";
    cout << "\n" << j2.nombre << ": " << j2.puntuacion << " puntos\n";
    
    if(j1.puntuacion > j2.puntuacion) {
        cout << "\n¡" << j1.nombre << " va ganando!\n"; // Mensaje si el jugador 1 va ganando
    } else if(j2.puntuacion > j1.puntuacion) {
        cout << "\n¡" << j2.nombre << " va ganando!\n"; // Mensaje si el jugador 2 va ganando
    } else {
        cout << "\n¡Estan empatados!\n"; // Mensaje si hay empate
    }
}

// Función para iniciar el modo multijugador
void modoMultijugador() {
    string nombre1, nombre2;
    
    cout << "\n=== MODO MULTIJUGADOR (Minijuegos) ===";
    cout << "\nJugador 1, ingresa tu nombre: ";
    cin >> nombre1; // Leo el nombre del jugador 1
    cout << "Jugador 2, ingresa tu nombre: ";
    cin >> nombre2; // Leo el nombre del jugador 2
    
    JugadorMinijuego j1 = {nombre1}; // Inicializo el jugador 1
    JugadorMinijuego j2 = {nombre2}; // Inicializo el jugador 2
    
    srand(time(nullptr));  // Inicializo la semilla aleatoria para mezclar cartas
    
    menuMinijuegos(j1, j2);  // Llamo al menú de minijuegos
    
    cout << "\n=== RESULTADO FINAL ===";
    mostrarGanador(j1, j2); // Muestro el ganador al final
}

#endif // MULTIJUGADOR_H
