#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include "hilo.h"

using namespace std;

//function to show the card
void ShowCard(int card) {
    if (card == 1) cout << "[A]";
    else if (card == 11) cout << "[J]";
    else if (card == 12) cout << "[Q]";
    else if (card == 13) cout << "[K]";
    else cout << "[" << card << "]";
}

//bring a random number between 1 - 13
int RandomCard() {
    return rand() % 13 + 1;
}


//HILO game
void hilo(int& bet, int& balance){
    int card = RandomCard();
    char guess, going;
    bool keep = true;

    //Show the first card to start de game
    cout << "the first card is: \n";
    ShowCard(card);
    cout << "\n";
    while (keep == true)
    {
        //generate a random "card2" in each loop
        int card2 = RandomCard();

        cout << "The next card will be Higher (H) or Lower (L) \n";
        cin >> guess;
        cout << "The next card is: ";
        ShowCard(card2);
        cout << endl;
        if ((guess == 'H' || guess == 'h') && card < card2 ||
            (guess == 'L' || guess == 'l') && card > card2)
        {
            card = card2;
            bet = bet * 2;
            cout << "Congratulations you win this round \n";
            cout << "Do you want to keep playing? (Y/N)";
            cin >> going;
            if (going == 'N' || going == 'n')
            {
                balance = balance + bet;
                cout <<"Thanks for playing" << endl;
                keep = false;
            }
            
        }else
        {
            cout << "Wrong!!! you lost your bet \n";
            bet = 0;
            keep = false;
        }
        
        
    }
    
    
}

//verify if the bet its possible
void BetConfirm(int& bet, int& balance){
    int option;
    do
    {
        cout << "1. make a bet \n";
        cout << "2. Exit \n";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "How much will your bet be? \n";
            cin >> bet;
            if (bet <= 0)
            {
                cout << "Your bet must be higher than 0 \n";
            }else if (bet > balance)
            {
                cout << "Your bet is higher than your balance \n";
            }else
            {
            //Check if the bet is valid
            balance = balance - bet;
            hilo(bet, balance);
            }
        break;
        case 2:
            cout << "Returning to the HI-LO menu \n";
        break;
        default:
        break;
        }
    } while (option != 2);
    

}

//HI-LO game main menu
void PlayHilo(int& balance){
    srand(time(0));

    int bet;
    int option;

    do
    {
        cout << "---- Welcome to HI-LO game ----\n";
        cout << "1. Game explanation \n";
        cout << "2. Play \n";
        cout << "3. check your balance \n";
        cout << "4. exit \n";
        cout << "Choose an option: ";
        cin >> option;
        switch (option)
        {
        case 1:
            //Game explanation
            cout << "Welcome to the HI-LO Game!\n\n";
            cout << "This one's super easy to play:\n\n";
            cout << "1. First, place your bet.\n";
            cout << "2. The dealer shows you a card.\n";
            cout << "3. Now it's your turn to guess -> will the next card be higher or lower?\n\n";
            cout << "If you guess right:\n";
            cout << "- You get your bet back plus a 0.5% bonus.\n";
            cout << "- You can keep playing to try and win even more, or cash out and take your reward.\n\n";
            cout << "If you guess wrong:\n";
            cout << "- You lose your bet \n\n";
        break;
        case 2:
            //Game logic
            BetConfirm (bet, balance);
        break;
        case 3:
            cout << "Your balance is: $" << balance << endl;
        break;
        case 4:
            cout << "Returning to the main menu... \n";
        break;
        default:
            cout << "Invalid option \n";
        break;
        }
    } while (option != 4);
    
}