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

/* Función Jugabilidad , tipo int. Esta funcion tiene el objetivo de manipular toda la lógica del juego , lanzar los dados y verificar el número del
lanzamiento mediante condicionales if , else if y también verificar que si el lanzamiento se convierte en un punto y luego se realizan lanzamientos
hasta que el jugador obtenga el número ganador o el número perderdor o que se le acaben los intentos. */
void MostrarMenu()
{

    cout << "\n";
    cout << "╔═══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                       ♠ ♥ Bienvenido a Craps ♥ ♣                      ║\n";
    cout << "║                                                                       ║\n";
    cout << "║            ¡Prepárate para probar tu suerte en este juego!            ║\n";
    cout << "║                                                                       ║\n";
    cout << "║          Selecciona el nivel de dificultad para comenzar:             ║\n";
    cout << "║                                                                       ║\n";
    cout << "║                  1. Fácil     ♣     2. Medio     ♦                    ║\n";
    cout << "║                            3. Difícil     ♠                           ║\n";
    cout << "║                                                                       ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

int Validacion()
{
    int opcion = 0;
    cout << "Selecciona tu nivel de dificultad : \n";
    cin >> opcion;

    while (cin.fail() || cin.peek() != '\n' || opcion <= 0 || opcion > 3)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                                            ♠ ♥ Mensaje ♥ ♣                                           ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║               Por favor no escriba letras ni caracteres especiales , solo numeros entre 1-3          ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║               Selecciona tu nivel de dificultad :                                                    ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        cin >> opcion;
    }

    return opcion;
}

int Jugabilidad(int intentosMaximos = 0)
{
    string NuevaPartida;
    srand(time(0));

    /*Variable come_out_roll , tipo int. Esta variable inicializada en 0 , es la encargada de guardar el número que el lanzador saque durante la primera
    tirada de los dados. */
    int come_out_roll = 0;

    /*Variable point , tipo int. Esta variable inicializada en 0 , es la encargada de guardar el número que salga del lanzamiento siempre y cuando esta no
    sea 2,3 , 12 , 7 o 11 , luego esta variable se utilizara para ser fijada y comnparada con las tiradas del lanzador . */
    int punto = 0;

    cout << "Iniciando el come-out roll...\n";
    pausar();

    /*El jugador inicia su primera tirada de dados , mandamos a llamar a la función lanzarDadosAnimados que es la encargada de generar un número aleatorio
    que luego se asignara en la variable come_out_roll para ser verificada para ver que condiciones cumple la variable*/
    come_out_roll = lanzarDadosAnimado();

    cout << "El come-out roll es: " << come_out_roll << "\n";

    // Pausar pendiente
    pausar();

    // Verifica si la variable come_out_roll es 2 , 3 o 12 , si es asi entonces se le imprime un mensaje al jugador indicandole que perdió la partida.
    if (come_out_roll == 2 || come_out_roll == 3 || come_out_roll == 12)
    {

        // Mensaje que se mostrará en consola
        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                 ♠ ♥ Perdiste ♥ ♣                  ║\n";
        cout << "║                                                   ║\n";
        cout << "║ Se ha generado un craps , has perdido la partida  ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";
    }

    // Verifica si la variable come_out_roll es igual a 7 o 12 , entonces el jugador gana en la primer ronda.
    else if (come_out_roll == 7 || come_out_roll == 11)
    {
        // Mensaje que le mostramos al jugador en consola.
        cout << "╔═══════════════════════════════════════════════╗\n";
        cout << "║                 ♠ ♥ Ganaste ♥ ♣               ║\n";
        cout << "║                                               ║\n";
        cout << "║        Felicidades , has ganado  la ronda     ║\n";
        cout << "║                                               ║\n";
        cout << "╚═══════════════════════════════════════════════╝\n";
    }

    // Verificamos si la variable es igual a 4,5,6,8,9,10 entonces aqui se establece el punto.
    else if (come_out_roll == 4 || come_out_roll == 5 || come_out_roll == 6 || come_out_roll == 8 || come_out_roll == 9 || come_out_roll == 10)
    {
        // Le indicamos al usuario que se ha establecido un punto , aqui el jugador podrá realizar varios lanzamientos hasta que el come_out_roll sea el punto o 7.
        cout << "Este es el punto , aqui el shooter generara de nuevo un come-out roll ... \n";
        cout << "Si sale : " << come_out_roll << " entonces el shooter gana , si sale 7 entonce el shooter pierde \n";

        /*Esta variable point guardara el valor del primer lanzamiento (come_out_roll) a partir de aqui esta variable funcionara para comparar con cada nuevo lanzamiento
        que realiza el jugador.*/
        punto = come_out_roll;
        pausar();

        /*Declaramos la variable intentos , tipo int. Inicializada en 0 , esta variable tendrá la funcionalidad de guardar las veces que el jugador lanza el dado
        dado que existen niveles de dificultad nos funcionará para indicarle al juego cuando se le acaben los lanzamientos al tirador y cerrar el juego o decirle si desea seguir jugando. */
        int intentos = 0;

        // Bucle While. Contiene dos condiciones diferentes que se estan comparando.

        /*Condición 1. Compara si intentosMaximos (parametro que recibe la función al inicio) es igual a 0 con el objetivo
        de que si el jugador selecciona el nivel facil entonces no tenga limite de lanzamientos. */

        /*Condición 2. Compara si intentosMaximos es menor a intentos dado que nos permitira controlar cuando el jugador seleccione el nivel medio o dificil
        entonces se repetira hasta que el jugador supere el máximo de intentos dependiendo la dificultad entonces el bucle deja de cumplirse y el jugador pierde la partida. */
        while (intentosMaximos == 0 || intentos < intentosMaximos)
        {

            /*Variable intentos , es una variable que utilizamos como contador , la cual aumenta a medida el tirador realiza cada lanzamiento de dados ,
             luego la vamos a comparar para saber si esta aun sigue siendo menor o si es mayor a intentosMaximos. */
            intentos++;

            /*El jugador realiza un nuevo lanzamiento de dados y ese nuevo lanzamiento lo guardamos en la variable come_out_roll y la vamos a comparar con
            la variable point.*/
            come_out_roll = lanzarDadosAnimado();

            // Le mostramos por mensaje en consola al jugador cuantos intentos a realizado.
            cout << "Intento:#" << intentos << endl;

            // Le mostramos en la consola al jugador cual es su nuevo lanzamiento resultado de realizar una nueva tirada de dados.
            cout << "El nuevo come-out roll es : " << come_out_roll << "\n";

            pausar();

            // Con la condicional if verificamos si el nuevo lanzamiento del jugador es igual al punto entonces el jugador gana.
            if (come_out_roll == punto)
            {
                // Le mostramos un mensaje de felicitación al jugador.
                cout << "╔═════════════════════════════════════════════════════╗\n";
                cout << "║                    ♠ ♥ Ganaste ♥ ♣                  ║\n";
                cout << "║                                                     ║\n";
                cout << "║                Felicidades , has ganado             ║\n";
                cout << "║                                                     ║\n";
                cout << "╚═════════════════════════════════════════════════════╝\n";
                return 0;
            }

            // Else if verificamos si el nuevo lanzamiento del jugador es igual a 7 entonces el jugador pierde.
            else if (come_out_roll == 7)
            {
                // Le mostramos un mensaje al jugador el mensaje que ha perdido.
                cout << "╔═════════════════════════════════════════════════════╗\n";
                cout << "║                   ♠ ♥ Perdiste ♥ ♣                  ║\n";
                cout << "║                                                     ║\n";
                cout << "║               Lo sentimos , has perdido             ║\n";
                cout << "║                                                     ║\n";
                cout << "╚═════════════════════════════════════════════════════╝\n";
                pausar();
                limpiarPantalla();

                return 0;
            }
        }

        // Le mostramos por consola al jugador indicando que ya no tiene intentos , por lo tanto pierde.
        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                  ♠ ♥ Mensaje ♥ ♣                  ║\n";
        cout << "║                                                   ║\n";
        cout << "║   Lo sentimos , ya se te acabaron los intentos    ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";

        pausar();
        limpiarPantalla();
    }
}

int Niveles(int seleccion)
{
    switch (seleccion)
    {
    case 1:
        cout << "Has accedido al nivel facil \n";
        Jugabilidad();
        break;

    case 2:
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                                            ♠ ♥ Mensaje ♥ ♣                                           ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║   Has accedido al nivel medio , tienes 5 intentos para lanzar los datos lograr el come-out roll      ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";

        Jugabilidad(5);

        break;

    case 3:
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                                            ♠ ♥ Mensaje ♥ ♣                                           ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║   Has accedido al nivel medio , tienes 3 intentos para lanzar los datos lograr el come-out roll      ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";
        Jugabilidad(3);

        break;

    default:
        cout << "Opcion invalida ... \n";
        break;
    }
}

void ReiniciarPartida()
{
    string continuarPartida = "";
    do
    {

        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                ¿Desea seguir jugando?             ║\n";
        cout << "║                                                   ║\n";
        cout << "║   Si (S)                               No (N)     ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";
        cin >> continuarPartida;

        if (continuarPartida == "S" || continuarPartida == "s")
        {
            int seleccion = 0;
            limpiarPantalla();
            MostrarMenu();
            seleccion = Validacion();
            Niveles(seleccion);
        }
        else if (continuarPartida == "N" || continuarPartida == "n")
        {
            cout << " Retornando al menú principal ... \n";
            return;
        }
        else
        {
            cout << "Ingrese un valor valido , por favor \n";
        }

    } while (continuarPartida != "N" && continuarPartida != "n");
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);

    int seleccion = 0;
    limpiarPantalla();
    MostrarMenu();
    seleccion = Validacion();
    Niveles(seleccion);
    ReiniciarPartida();

    return 0;
}
