#include <iostream>
#include <ctime>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace std;

// Caras ASCII de los dados
const char* carasDados[6][5] = {
    { "+-------+", "|       |", "|   o   |", "|       |", "+-------+" },
    { "+-------+", "| o     |", "|       |", "|     o |", "+-------+" },
    { "+-------+", "| o     |", "|   o   |", "|     o |", "+-------+" },
    { "+-------+", "| o   o |", "|       |", "| o   o |", "+-------+" },
    { "+-------+", "| o   o |", "|   o   |", "| o   o |", "+-------+" },
    { "+-------+", "| o   o |", "| o   o |", "| o   o |", "+-------+" }
};

void mostrarDadosASCII(int d1, int d2) {
    for (int i = 0; i < 5; ++i) {
        cout << carasDados[d1 - 1][i] << "   " << carasDados[d2 - 1][i] << "\n";
    }
    cout << endl;
}

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void esperarMilisegundos(int ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms * 1000);
    #endif
}

void pausar() {
    esperarMilisegundos(5000); 
}

int lanzarDadosAnimado() {
    int d1 = 1, d2 = 1;
    for (int i = 0; i < 10; ++i) {
        d1 = rand() % 6 + 1;
        d2 = rand() % 6 + 1;

        limpiarPantalla();
        cout << "Lanzando dados...\n\n";
        mostrarDadosASCII(d1, d2);
        esperarMilisegundos(100);
    }

    cout << "Resultado final:\n\n";
    mostrarDadosASCII(d1, d2);
    return d1 + d2;
}

int main() {
    srand(time(0));
    int come_out_roll = 0;
    int punto = 0;

    limpiarPantalla();
    cout << "||====================================================||\n";
    cout << "||           Bienvenido al juego de craps             ||\n";
    cout << "||====================================================||\n\n";

    cout << "Iniciando el come-out roll...\n";
    pausar();

    come_out_roll = lanzarDadosAnimado();
    cout << "El come-out roll es: " << come_out_roll << "\n";
    pausar();

    if (come_out_roll == 2 || come_out_roll == 3 || come_out_roll == 12)
    {
        cout << "Se ha generado un craps , has perdido la partida \n";
    }
    else if (come_out_roll == 7 || come_out_roll == 11)
    {
        cout << "¡¡Felicidades , ganaste la ronda!! \n";
    }
    else if (come_out_roll == 4 || come_out_roll == 5 || come_out_roll == 6 || come_out_roll == 8 || come_out_roll == 9  ||come_out_roll == 10 )
    {
        cout << "Este es el punto , aqui el shooter generara de nuevo un come-out roll ... \n";
        cout << "Si sale : " << come_out_roll << " entonces el shooter gana , si sale 7 entonce el shooter pierde \n";
        punto = come_out_roll;
        pausar();

    do
        {
            come_out_roll = lanzarDadosAnimado();
          
            cout << "El nuevo come-out roll es : " << come_out_roll << "\n";
            pausar();


            if (come_out_roll == punto)
            {
                cout << "¡¡Felicidades , has ganado \n"; break;
            }
            else if (come_out_roll == 7)
            {
                cout << "¡¡Lo sentimos , has perdido  \n"; break;
            }
        } while (true);
    }

    return 0;
}
