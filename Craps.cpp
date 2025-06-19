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
const char *carasDados[6][5] = {
    {"+-------+", "|       |", "|   o   |", "|       |", "+-------+"},
    {"+-------+", "| o     |", "|       |", "|     o |", "+-------+"},
    {"+-------+", "| o     |", "|   o   |", "|     o |", "+-------+"},
    {"+-------+", "| o   o |", "|       |", "| o   o |", "+-------+"},
    {"+-------+", "| o   o |", "|   o   |", "| o   o |", "+-------+"},
    {"+-------+", "| o   o |", "| o   o |", "| o   o |", "+-------+"}};

void mostrarDadosASCII(int d1, int d2)
{
    for (int i = 0; i < 5; ++i)
    {
        cout << carasDados[d1 - 1][i] << "   " << carasDados[d2 - 1][i] << "\n";
    }
    cout << endl;
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void esperarMilisegundos(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void pausar()
{
    esperarMilisegundos(5000); // Espera 2 segundos sin necesidad de presionar nada
}

int lanzarDadosAnimado()
{
    int d1 = 1, d2 = 1;
    for (int i = 0; i < 10; ++i)
    {
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

int Jugabilidad(int intentosMaximos = 0)
{
    srand(time(0));
    int come_out_roll = 0;
    int punto = 0;

    cout << "Iniciando el come-out roll...\n";
    pausar();

    come_out_roll = lanzarDadosAnimado();
    cout << "El come-out roll es: " << come_out_roll << "\n";
    pausar();

    if (come_out_roll == 2 || come_out_roll == 3 || come_out_roll == 12)
    {
        cout << "Se ha generado un craps , has perdido la partida \n";
        return 0;
    }
    else if (come_out_roll == 7 || come_out_roll == 11)
    {
        cout << "Felicidades , ganaste la ronda!! \n";
        return 0;
    }
    else if (come_out_roll == 4 || come_out_roll == 5 || come_out_roll == 6 || come_out_roll == 8 || come_out_roll == 9 || come_out_roll == 10)
    {
        cout << "Este es el punto , aqui el shooter generara de nuevo un come-out roll ... \n";
        cout << "Si sale : " << come_out_roll << " entonces el shooter gana , si sale 7 entonce el shooter pierde \n";
        punto = come_out_roll;
        pausar();

        int intentos = 0;
        while (intentosMaximos == 0 || intentos < intentosMaximos)
        {
           
            intentos++;
            come_out_roll = lanzarDadosAnimado();

            cout << "El nuevo come-out roll es : " << come_out_roll << "\n";
            cout << "Intento:#" <<intentos <<endl;
            pausar();

            if (come_out_roll == punto)
            {
                cout << "Felicidades , has ganado \n";
                return 0;
            }
            else if (come_out_roll == 7)
            {
                cout << "Lo sentimos , has perdido  \n";
                return 0;
            }

          
        }

        cout << "Lo sentimos , ya se te acabaron los intentos ... \n";
    }
}

int main()
{

    int resultado;
    int opcion = 0;

    limpiarPantalla();
    cout << "||====================================================||\n";
    cout << "||           Bienvenido al juego de craps             ||\n";
    cout << "||====================================================||\n";

    cout << "A continuacion te presentamos el siguiente menu sobre la dificultad del juego : \n";

    cout << "||====================================================||\n";
    cout << "||                     1. Facil                       ||\n";
    cout << "||                     2. Medio                       ||\n";
    cout << "||                     3. Dificil                     ||\n";
    cout << "||====================================================||\n";

    cout << "Selecciona tu nivel de difiultad : \n";
    cin >> opcion;

    while (cin.fail() || cin.peek() != '\n' || opcion <= 0 || opcion > 3)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "Por favor no escriba letras ni caracteres especiales , solo numeros entre 1-3 \n";
        cout << "Selecciona tu nivel de dificultad : \n";
        cin >> opcion;
    }

    switch (opcion)
    {
    case 1:
        cout << "Has accedido al nivel facil \n";
        Jugabilidad();
        break;

    case 2:
        cout << "Has accedido al nivel medio , tienes 5 intentos para lanzar los datos lograr el come-out roll \n";

        Jugabilidad(5);

        break;

    case 3:
        cout << "Has accedido al nivel medio , tienes 3 intentos para lanzar los datos y lograr el come-out roll \n";
        Jugabilidad(3);

        break;

    default:
        cout << "Opcion invalida ... \n";
        break;
    }

    return 0;
}