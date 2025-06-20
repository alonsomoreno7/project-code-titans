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
   

//                                           EASY MODE
void emptySlotsE(){
    //Mostrar slots vacios al jugador
    cout<<endl;
    cout<<"* - * - * - * - * - *. . . . . . . "<<endl;
    cout<<"|                                ."<<endl;
    cout<<"*          Try your luck!        ."<<endl;
    cout<<"|                                ."<<endl;
    cout<<"*    -----------------------     ."<<endl;
    cout<<".   |       |       |       |    |"<< endl;
    cout<<".   |   -   |   -   |   -   |    *" <<endl;
    cout<<".   |       |       |       |    |"<< endl;
    cout<<".    -----------------------     *"<<endl;
    cout<<".   | Pull the lever (!)|        |"<<endl;
    cout<<". . . . . . .* - * - * - * - * - *"<<endl;
    cout<<endl;
    //se le indica al jugador que debe de presionar "!" para generar los simbolos aleatorios
}

char randomSymbolE (){

    //Funcion para generar simbolos aleatorios

    char symbol [3]= {'@','$','7'}; //arreglo con 3 simbolos
    int randomP = rand()%3; //variable para elegir un numero del 0 al 3
    return symbol[randomP]; //la funcion retornara un simbolo random

}

void finalSlotsE (char slots[3]) {
    //Mostrar slots finales al jugador
    cout<<"* - * - * - * - * - *. . . . . . . "<<endl;
    cout<<"|                                ."<<endl;
    cout<<"*            RESULTS!            ."<<endl;
    cout<<"|                                ."<<endl;
    cout<<"*    -----------------------     ."<<endl;
    cout<<".   |       |       |       |    *"<< endl;
    //En esta linea se mostraran los simbolos aleatorios
    cout<<".   |   "<< slots[0]<<"   | "<< "  "<< slots[1]<<"   | "<< "  "<< slots[2]<<"   |    |" <<endl;
    cout<<".   |       |       |       |    *"<< endl;
    cout<<".    -----------------------     |"<<endl;
    cout<<". . . . . . .* - * - * - * - * - *"<<endl;
    cout<<endl;

}

bool jackpotE(char slots[3]){
    //funcion para validar si los 3 simbolos son iguales
    return(slots[0]==slots[1] && slots[1]==slots[2]);
    //si los tres son iguales = true
}

void losePhrases (){
    //funcion para mostrar una frase motivadora aleatoria cuando el jugador pierda
    string lSentence_0 = "The next move could change everything…"; //frase 1
    string lSentence_1 = "The reels don't move by themselves! Dare!";//frase 2
    string lSentence_2 = "The reels are heating up… don’t give up!"; //frase 3
    string LSentence_3 = "Almost there! The next turn could be the winner."; //frase 4
    int randomLphase = rand()%4; //variable para elegir un numero del 0 al 4

    //condiciones para cada numero
    switch(randomLphase){
        case 0:                  //si es 0 se mostrara la frase 1
        cout<<endl;
        cout<<lSentence_0<<endl;
        break;

        case 1:                  //si es 1 se mostrara la frase 2
        cout<<endl;
        cout<<lSentence_1<<endl;
        break;

        case 2:                  //si es 2 se mostrara la frase 3
        cout<<endl;
        cout<<lSentence_2<<endl;
        break;

        case 3:                  //si es 3 se mostrara la frase 4
        cout<<endl;
        cout<<LSentence_3<<endl;
        break;

        default:                 //ante cualquier error se mostrara otra frase 
        cout<<endl;
        cout<<"Luck turns around… and yours is about to return."<<endl;
        break;
    }

}

//Main game easy
void easyMode(){

    char symbols[3]; //arreglo para guardar los simbolos aletorios
    
    int playerLose; //Validar si el jugador gano o perdio
    string anotherRound; //guardar respuesta del jugador

    while (true){ // while infinito para que el jugador decida seguir jugando

        srand(time(0)); //aleatoriedad
        
         for(int i=3;i>0;i--){ //bucle for que repite 3 veces cada tiro

            while(true){ //while infinito para mostrar al jugador los tiros restantes 

                string nextSpin; //variable para que el jugador inicie cada juego
                cout<<endl;
                cout<<"You have "<< i <<" remaining chances!"<<endl; //se le muestran al jugador las oportunidades restantes
                cout<<"(P) to continue..."<<endl; //se le indica al jugador debe de presionar "P" para continuar.
                getline(cin,nextSpin);  //se ingresa y se lee el character ingresado
                if(nextSpin=="P"|| nextSpin=="p"){
                    break; //si se ingresa "P" o "p" el bucle while termina y se continua con el juego.
                }else{
                    cout<<endl;
                    cout<<"Please enter a valid option (P), try again."<<endl; //si no se envia mensaje de error 
                          
                    //el bucle se repite hasta que el usuario ingrese "P" 
                }

            }
        
            while(true){

                string pull;
                emptySlotsE(); //Se llama a la funcion Mostrar slots vacios al jugador 
                getline(cin,pull); //el jugador debe ingresar "!" y se lee el character ingresado
    
                if(pull=="!"){
                    //si se ingresa "!" se continua con el juego.
                    for(int i=0;i<=3;i++){            //
                        symbols[i]= randomSymbolE();
                    }
                    finalSlotsE(symbols); //Se llama a la funcion Mostrar slots finales al jugador
                
                    if(jackpotE(symbols)){
                        cout<<"            * JACKPOT!! *   "<<endl;
                        cout<<endl;
                        cout<<" Congratulations!! you have earned: $x"<<endl;
                        i=0;
                        playerLose=0;
                        break;
                    }else{
                        cout<<"            KEEP TRYING "<<endl;
                        losePhrases();
                        playerLose=1;
                        break;
                    
                    }
                
                }else{
                    cout<<endl;
                    cout<<"Please enter a valid option (!), try again."<<endl;
                    //si no se envia mensaje de error 
                    //el bucle se repite hasta que el usuario ingrese "!" 
                
                }
        
            }

        }

        if(playerLose==1){
            cout<<endl;
            cout<<"   You'll be lucky next time."<<endl;
            cout<<"-$100"<<endl;
            cout<<endl;
        }

        while(true){ //while infinito para validar que se ingreso un caracter valido
            cout<<"Do you want to play another round?"<<endl;
            cout<<"     YES (Y).        NO(N)"<<endl;
            getline(cin,anotherRound); //jugador ingresa su opccion y se lee su respuesta

            if(anotherRound=="Y"||anotherRound=="y"){
                cout<<"GOOD LUCK!!"<<endl; //si se ingresa "Y" o "y" (yes) el bucle termina
                anotherRound="";
                break;
            }else if(anotherRound=="N"||anotherRound=="n"){
                cout<<"Return to menu..."<<endl; //si se ingresa "N" o "n" (no) el bucle termina
                break;
            }else{
                cout<<"Please enter a valid option (Y) or (N), try again."<<endl; 
                //si no se envia mensaje de error y el bucle se repite
            }

        }

        if(anotherRound=="N"||anotherRound=="n"){ //validar si el juegador eligio si o no
            break; //si el usuario ingreso "N" o "n" (no) la funcion termina
        } 

    }

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
                    easyMode();
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
