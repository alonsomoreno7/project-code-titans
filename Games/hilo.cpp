#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream> 


using namespace std;

//bring a random number between 1 - 13
int RandomCard() {
    return rand() % 13 + 1;
}

//makes random suits for the cards
string RandomSuit() {
    string suit[] = {"♠", "♥", "♦", "♣"};
    return suit[rand() % 4];
}

//change the card value to string
string CardValue(int value) {
    if (value == 1) return "A";
    if (value == 11) return "J";
    if (value == 12) return "Q";
    if (value == 13) return "K";
    return to_string(value);
}

//makes a visual draw of the card
void AsciiHiloCards(int value[], string suit[], int count) {
    string line[7];
    for (int i = 0; i < count; i++) {
        string value2 = CardValue(value[i]);
        string izq = value2.length() == 1 ? value2 + " " : value2;
        string der = value2.length() == 1 ? " " + value2 : value2;

        line[0] += "┌─────────┐ ";
        line[1] += "│" + izq + "       │ ";
        line[2] += "│         │ ";
        line[3] += "│    " + suit[i] + "    │ ";
        line[4] += "│         │ ";
        line[5] += "│       " + der + "│ ";
        line[6] += "└─────────┘ ";
    }

    for (int i = 0; i < 7; i++) {
        cout << line[i] << endl;
    }
}



//HILO game
void hilo(int& bet, int& balance){
    int card = RandomCard();
    char guess, going;
    bool keep = true;
    string suit1 = RandomSuit();

    //Show the first card to start de game
    cout << "the first card is: \n";
    int values1[] = {card};
    string suits1[] = {suit1};
    AsciiHiloCards(values1, suits1, 1);
    cout << "\n";
    while (keep == true)
    {
        //generate a random "card2" in each loop
        int card2 = RandomCard();
        string suit2 = RandomSuit();

        //the player try to guess 
        while (true) {
            cout << "The next card will be Higher (H) or Lower (L): ";
            cin >> guess;
            if (guess == 'H' || guess == 'h' || guess == 'L' || guess == 'l') break;
            cout << "Invalid option, please select 'H' or 'L'\n";
        }

        //show the next card
        cout << "---------------------------------------------------\n";
        cout << "The next card is: \n";
        int values2[] = {card2};
        string suits2[] = {suit2};
        AsciiHiloCards(values2, suits2, 1);
        cout << endl;

        //verify if the answer was correct
        if ((guess == 'H' || guess == 'h') && card < card2 ||
            (guess == 'L' || guess == 'l') && card > card2)
        {
            card = card2;
            bet = bet * 2;
            cout << "Congratulations you win this round \n";
            //make sure that the player select Y or N
            while (true) {
                        cout << "Do you want to keep playing ";
                        cin >> going;
                        if (going == 'Y' || going == 'y' || going == 'N' || going == 'n') break;
                        cout << "Invalid option, please select 'Y' or 'N'\n";
            }
            //Return to de HILO menu
            if (going == 'N' || going == 'n')
            {
                balance = balance + bet;
                cout <<"Thanks for playing" << endl;
                keep = false;
            }
            
        }else if (card == card2)
        {
            cout << "It was a tie \n";
            cout << "No one loses, no one wins \n";
            //make sure that the player select Y or N
            while (true) {
                        cout << "Do you want to keep playing ";
                        cin >> going;
                        if (going == 'Y' || going == 'y' || going == 'N' || going == 'n') break;
                        cout << "Invalid option, please select 'Y' or 'N'\n";
            }
            //Return to de HILO menu
            if (going == 'N' || going == 'n')
            {
                balance = balance + bet;
                cout <<"Thanks for playing" << endl;
                keep = false;
            }
        }
        // lose the bet and return to the HILO menu
        else
        {
            cout << "Wrong!!! you lost your bet \n";
            bet = 0;
            keep = false;
        }
        
        
    }
    
    
}

//Confirm if the bet its valid
void BetConfirm(int& bet, int& balance) {
    cout << "How much will your bet be? \n";

    while (true) {
        cin >> bet;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Your bet is invalid, try entering a number\n";
        }
        else if (bet <= 0) {
            cout << "Your bet must be higher than 0\n";
        }
        else if (bet > balance) {
            cout << "Your bet is higher than your balance\n";
            cout <<"Your balance is: " << balance << endl;
        }
        else {
            //If the bet its valid:
            balance = balance - bet;
            hilo(bet, balance);
            break;
        }

        // Ask for a bet again
        cout << "Please enter a valid bet: $";
    }
}


//HI-LO game main menu
void PlayHilo(int& balance){
    srand(time(0));

    int bet;
    int option;

    do
    {
        //main menu
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
            cout << "- You get your bet back doubled.\n";
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