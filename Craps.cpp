#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

// Funciones a diseñar:
/*
1. Funcion para generar el numero aleatorio y simular la tirada de los dados
2. Funcion para generar la tirada de dados.
*/

int GeneracionNumeroAletorio()
{
    srand(time(0));
    return rand() % 10 + 1; // Números de 1 a 10 
}

int main()
{
    int come_out_roll = 0;
    int punto = 0;
    // Version Demo - la mas basica

    cout << "||====================================================||\n";
    cout << "||           Bienvenido al juego de craps             ||\n";
    cout << "||====================================================||\n";

    // Probar la generacion de numeros aletorios

    come_out_roll = GeneracionNumeroAletorio();
    cout << "Iniciando el come-out roll \n";
    cout << "El come-out roll es : " << come_out_roll << "\n";

    if (come_out_roll == 2 || come_out_roll == 3 || come_out_roll == 12)
    {
        cout << "Se ha generado un craps , has perdido la partida \n";
    }
    else if (come_out_roll == 7 || come_out_roll == 11)
    {
        cout << "¡¡Felicidades , ganaste la ronda!! \n";
    }
    else if (come_out_roll == 4 || come_out_roll == 5 || come_out_roll == 6 || come_out_roll == 9 || come_out_roll == 10)
    {
        cout << "Este es el punto , aqui el shooter generara de nuevo un come-out roll ... \n";
        cout << "Si sale : " << come_out_roll << " entonces el shooter gana , si sale 7 entonce el shooter pierde \n";
        punto = come_out_roll;

        do
        {
            come_out_roll = GeneracionNumeroAletorio();
            cout << "El nuevo come-out roll es : " << come_out_roll << "\n";

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
