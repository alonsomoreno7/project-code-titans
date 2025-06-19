#include <iostream>
#include <cstring>
using namespace std;

// Funcion para mostrar las intrucciones del juego
void showSlot()
{

    cout << endl;
    cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                   -PLAY SLOT MACHINE-                    . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*    A slot machine is a game where a series of random     . " << endl;
    cout << "|    symbols are displayed on each spin. If all the        . " << endl;
    cout << ".    symbols on a line match, you win.                     | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".                                                          | " << endl;
    cout << ".    MENU (M)                                 PLAY (P)     * " << endl;
    cout << ".                                                          | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
    //Se indica que se debe ingresar "M" para volver al menu o "P" para jugar
}

// Funcion para mostrar el menu de dificultades del juego tragamonedas
void showSlotmenu()
{

    cout << endl;
    cout << "* - * - * - * - * - * - * - * - *. . . . . . . . . . . . . . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                      -SLOT MACHINE-                      . " << endl;
    cout << "|                                                          . " << endl;
    cout << "*                  Choose the difficulty:                  . " << endl;
    cout << "|                                                          . " << endl;
    cout << ".   (E) EASY:      A single line of symbols                | " << endl;
    cout << ".   (M) MEDIUM:    3 paylines                              * " << endl;
    cout << ".   (H) HARD:      5 paylines + special symbols            | " << endl;
    cout << ".                                                          * " << endl;
    cout << ".     BACK (B)                                             | " << endl;
    cout << ". . . . . . . . . . . . . .* - * - * - * - * - * - * - * - * " << endl;
    cout << endl;
    //se indica que se debe ingresar "B" para volver al anterior menu
    //"E" para modo facil, "M" para modo medio, "H" para modo dificil
}


int main(){

    while (true){ //while infinito para primer menu

        showSlot(); //llama a la funcion showSlot (instrucciones del juego)
        string option;
        getline(cin, option); //Usuario ingresa opccion

        // verificacion de opccion ingresada
        if (option == "M" || option == "m"){

            cout<<"Returning to the main menu..."<<endl;
            break; // si ingresa "M" o "m" entonces se rompe el bucle y finaliza el programa (volver al menu inicial)
        }
        else if (option == "P" || option == "p"){
            // si ingresa "P" o "p" entonces el usuario se movera al menu de dificultades
            while (true){

                showSlotmenu(); // llama a funcion mostrar menu de dificultades
                string option;
                getline(cin, option); //usuario ingresa su opccion

                if (option == "B" || option == "b"){
                    break; //Volver al anterior menu
                } else if (option == "E"||option=="e"){

                } else if (option == "M"||option=="m"){

                } else if (option == "H"||option=="h"){

                } else {

                    // se muestra mensaje de error y se vuelve a pedir ingresar una opccion
                    cout << "Please enter a valid option (E),(M),(D) or (B), try again." << endl;

                }

            }
        }
        else
        {
            // se muestra mensaje de error y se vuelve a pedir ingresar una opccion
            cout << "Please enter a valid option (M) or (P), try again." << endl;
        }
    }

    return 0;
}
