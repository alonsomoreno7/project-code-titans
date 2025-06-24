#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// se define el numero total de casillas que tendra la ruleta
const int NUMEROS = 37;

//  Coloca los numero que tendra la ruleta dentro de un arreglo
const int numeros[NUMEROS] = {
    0, 32, 15, 19, 4, 21, 2, 25, 17,
    34, 6, 27, 13, 36, 11, 30, 8, 
    23, 10, 5, 24, 16, 33, 1, 20, 14, 31,
    9, 22, 18, 29, 7, 28, 12, 35, 3, 26

};

//colores que corresponderian a cada numero dentro de la ruleta
const char colores[NUMEROS]={
'G','N','R','N','R','N','R','N','R','N','R',
    'N','R','N','R','N','R','N','R','N','R',
    'N','R','N','R','N','R','N','R','N','R',
    'N','R','N','R','N','R'
//el numero 0 es de color verde
};    

// codigos de escape ANSI para darle color
const string rojo = "\033[31m";
const string negro = "\033[30m";
const string verde = "\033[32m";
const string fondo_blanco = "\033[47m";
const string reset = "\033[0m";

//Funciones para limpiar consola y pausar
#ifdef _WIN32
void esperarMs (int ms) { Sleep (ms);}
void limpiarConsola(){ system ("cls");}
#else
void esperarMs(int ms){ usleep(ms * 1000);}
void limpiarConsola(){ cout << "\033[2J\033[H"; }
#endif

// esructura que representa la posicion (X y Y) de cada numero 
struct Posicion{int x, y; };

//Definir dimensiones y centro de la canvas para dibujar la ruleta

const int WIDTH = 90;
const int HEIGHT = 30;
const int RADIO = 13;
const int CENTRO_X = WIDTH / 2;
const int CENTRO_Y = HEIGHT / 2;

//arreglo para guardar posiciones calculadas
Posicion posiciones[NUMEROS];


//Calcular las posiciones den circulo para dibujar la ruleta 
void calcularPosiciones() {
    for (int i = 0; i < NUMEROS; i++) {
        double angulo = (2 * M_PI * i / NUMEROS) - M_PI / 2;
        posiciones[i].x = CENTRO_X + int(RADIO * cos(angulo) * 1.9); 
        posiciones[i].y = CENTRO_Y + int(RADIO * sin(angulo));
    }
}
void imprimirCanvas(int iluminado) {
    string canvas[HEIGHT][WIDTH];
    // Primero lleno todo con espacios para limpiar el canvas
    for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++)
            canvas[i][j] = " ";

    // se pone  cada numero en su posición con el color correspondiente
    for (int i = 0; i < NUMEROS; i++) {
        int x = posiciones[i].x;
        int y = posiciones[i].y;
        string color = (colores[i] == 'R') ? rojo : (colores[i] == 'N') ? negro : verde;

        // Si es el número iluminado se resalta con fondo blanco
        if (i == iluminado) color = fondo_blanco + color;

        string numStr = (numeros[i] < 10 ? " " : "") + to_string(numeros[i]);

        // se verifica que la posición este dentro del canvas
        if (x >= 0 && x + 1 < WIDTH && y >= 0 && y < HEIGHT) {
            canvas[y][x] = color + numStr + reset;
            canvas[y][x + 1] = ""; // Evito sobreescribir por error
        }
    }
 // se agregan puntos para poder darle un efecto de círculo
    for (int r = 1; r < RADIO - 2; r++) {
        for (int a = 0; a < 360; a += 15) {
            double rad = a * M_PI / 180.0;
            int x = CENTRO_X + int(r * cos(rad) * 0.5);
            int y = CENTRO_Y + int(r * sin(rad));
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
                canvas[y][x] = ".";
        }
    }

    // se marca el centro con una "O"
    canvas[CENTRO_Y][CENTRO_X] = "O";

    // imprimo el canvas línea por línea
    for (int i = 0; i < HEIGHT; i++) {
        string linea = "";
        for (int j = 0; j < WIDTH; j++) {
            if (!canvas[i][j].empty()) linea += canvas[i][j];
        }
        cout << linea << "\n";
    }
}
//funcion para poder pasar una cadena a minusculas
string toLower(const string &s){
    string res = s;
    transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}


// pide la apuesta y se valida, se repito si la entrada es inválida o si se apuesta más de lo que tienen
int pedirApuesta(int saldo){
 int apuesta;
    while (true) {
        cout << "¿Cuánto deseas apostar?: ";
        if (cin >> apuesta) {
            if (apuesta > 0 && apuesta <= saldo)
                return apuesta;
            else
                cout << "Apuesta inválida. Debe ser mayor que 0 y no mayor que tu saldo.\n";
        } else {
            cout << "Entrada inválida. Ingresa un número entero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }    
}


// pido el tipo de apuesta (número, color o par/impar) y se valida que sea una opción válida
string pedirTipoApuesta() {
    string tipo;
    while (true) {
        cout << "\n╔════════════════════════════════════╗\n";
        cout << "║         MENÚ DE APUESTAS          ║\n";
        cout << "╠════════════════════════════════════╣\n";
        cout << "║  1. Número exacto      →  paga 35x ║\n";
        cout << "║  2. Color (Rojo/Negro) →  paga 2x  ║\n";
        cout << "║  3. Par o Impar        →  paga 2x  ║\n";
        cout << "╚════════════════════════════════════╝\n";
        cout << "→ Escoge una opción: ";
        cin >> tipo;
        tipo = toLower(tipo);

        if(tipo == "1" || tipo == "2" || tipo == "3")
           return tipo;
        else 
            cout << "Opcion invalida, intenta de nuevo.\n"; 
    }
}

//pide un numero del 0 al 36 para la apuesta a numero exacto
int pedirNumero(){
    int num;
    while(true) {
        cout << "Ingresa el número (0-36): ";
        if (cin >> num){
            if (num >= 0 && num <= 36)
                return num;
            else 
            cout << "Número inválido. El número debe estar entre 0 y 36.\n";
        } else {
            cout << "Entrada inválida. Ingrese un número entero.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    
    }
}

// se pide el color "rojo" o "negro", se convierte a mayusculas y valida que sea correcto
char pedirColor(){
    string color;
    while (true){
        cout << "Ingresa el color (Rojo / Negro): ";
        cin >> color;
        color = toLower(color);
        if (color == "rojo")
            return 'R';
        else if (color == "negro")
            return 'N';
        else
        cout << "Color inválido. Solo puede ingresar 'Rojo' o 'Negro'.\n";

    }
}
//Se pide si la apuesta es a par o impar y valido la enntrada
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
// Pregunto si el jugador quiere seguir jugando, acepta respuestas 
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
int main() {
    srand(time(nullptr)); // Inicio la semilla aleatoria para que los números cambien
    calcularPosiciones();  // Calculo dónde se deben colocar los números en la ruleta visual

    int saldo = 1000; // Inicio con 1000 de saldo para apostar

    while (saldo > 0) {
        limpiarConsola();
        cout << "\nSaldo actual: $" << saldo << "\n";

        // Pido la apuesta al usuario validando que sea correcta
        int apuesta = pedirApuesta(saldo);

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
            cout << "\nSaldo actual: $" << saldo << "\n";
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
        if (tipo == "1" && numGanador == eleccion)
        bool gano = false;
        // Evaluo si la apuesta fue ganadora
        if (tipo == "1" && numGanador == eleccion) {
            cout << "¡Ganaste 35 veces tu apuesta!\n";
            saldo += apuesta * 35;
            gano = true;
        } else if (tipo == "2" && colorGanador == colorElegido) {
            cout << "¡Ganaste 2 veces tu apuesta!\n";
            saldo += apuesta * 2;
            gano = true;
        } else if (tipo == "3") {
            // Para par o impar, el 0 no cuenta como ganador
            if (numGanador != 0) {
                if ((paridadElegida == 'P' && numGanador % 2 == 0) ||
                    (paridadElegida == 'I' && numGanador % 2 != 0)) {
                    cout << "¡Ganaste 2 veces tu apuesta!\n";
                    saldo += apuesta * 2;
                    gano = true;
                }
            }
        }

        if (!gano) {
            cout << "No ganaste esta vez.\n";
            saldo -= apuesta;
        }

        cout << "\nSaldo actualizado: $" << saldo << "\n";

        // Pregunto si quiere seguir jugando, validando que la respuesta sea correcta
        if (!preguntarSeguir()) break;
    }

    if (saldo <= 0)
        cout << "\nTe has quedado sin dinero. Juego terminado.\n";

    cout << "\nGracias por jugar. Tu saldo final fue: $" << saldo << "\n";

    return 0;
}