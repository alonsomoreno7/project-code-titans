#include <iostream>
#include <ctime>
#include <cstdlib>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Array diceFaces that stores the ASCII representations of dice faces.
// Each row represents one face of the die, from 1 to 6.
// Each column contains a line of the ASCII drawing for that face.
const char *diceFaces[6][5] = {

    // Die face 1: one center dot
    {"+-------+", "|       |", "|   o   |", "|       |", "+-------+"},
    // Die face 2: dots in opposite corners
    {"+-------+", "| o     |", "|       |", "|     o |", "+-------+"},
    // Die face 3: dots in two corners and one in the center
    {"+-------+", "| o     |", "|   o   |", "|     o |", "+-------+"},
    // Die face 4: dots in all four corners
    {"+-------+", "| o   o |", "|       |", "| o   o |", "+-------+"},
    // Die face 5: dots in all four corners and one in the center
    {"+-------+", "| o   o |", "|   o   |", "| o   o |", "+-------+"},
    // Die face 6: dots in all four corners and two in the middle lines (top and bottom)
    {"+-------+", "| o   o |", "| o   o |", "| o   o |", "+-------+"}};

void clearScreen()
{
    // #ifdef checks if the macro is already defined, in this case _WIN32.
    // _WIN32 lets us detect if the code is being compiled on Windows and executes the system("cls") command.

#ifdef _WIN32
    // Executes the (cls) command to clear the console from the cpp file on Windows.
    system("cls");
#else
    // Executes the (clear) command to clear the console on operating systems like macOS, Linux, etc.
    system("clear");
#endif
}

// Function showASCIIDice. This function displays two dice side by side on the screen using drawings made with ASCII characters.
void showASCIIDice(int d1, int d2)
{
    // It receives two numbers representing the dice (from 1 to 6) and prints them in the console so the player can clearly see them.
    for (int i = 0; i < 5; ++i)
    {
        // To do this, it goes through each line of the drawing of each die and prints them together on the same line.
        cout << diceFaces[d1 - 1][i] << "   " << diceFaces[d2 - 1][i] << "\n";
    }
    cout << endl;
}

// Function waitMilliseconds. Receives an integer parameter from the pause() function.
void waitMilliseconds(int ms)
{
    // #ifdef checks if the macro is already defined, in this case _WIN32.
    // _WIN32 lets us detect if the code is being compiled on Windows, then executes the Sleep() function.
#ifdef _WIN32

    // Performs a pause with the received parameter, converting milliseconds to seconds.
    Sleep(ms);

    // If not Windows, executes usleep() for other operating systems.
#else

    usleep(ms * 1000);
#endif
}

// Function pause. Temporarily stops execution for a few seconds to display validation messages to the user. Does not return any value.
void pause()
{
    // Call the function waitMilliseconds() passing 3000, which equals 3 seconds of wait to show messages.
    waitMilliseconds(3000);
}

// Function rollDiceAnimated. This function simulates rolling two dice showing an animation in the console.
int rollDiceAnimated()
{
    // Declare two variables for the dice and initialize them to 1.
    int d1 = 1, d2 = 1;

    // Run a loop 10 times to simulate the animation.
    for (int i = 0; i < 10; ++i)
    {
        // Generate random numbers between 1 and 6 for each die.
        d1 = rand() % 6 + 1;
        d2 = rand() % 6 + 1;

        // Clear the screen to show only the current animation frame.
        clearScreen();

        // Show the dice in ASCII with the generated values.
        cout << "Rolling dice...\n\n";
        showASCIIDice(d1, d2);

        // Pause briefly to create the animation effect.
        waitMilliseconds(100);
    }

    // After the animation, show the final result message.
    cout << "Final result:\n\n";

    // Show the dice with the final values.
    showASCIIDice(d1, d2);

    // Return the sum of the values of both dice.
    return d1 + d2;
}

// Function showMenu. A void function that simply displays the difficulty levels to the user.
void showMenu()
{
    // Line break.
    cout << "\n";
    // Message displayed to the user in the console.
    cout << "╔═══════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                       ♠ ♥ Welcome to Craps ♥ ♣                        ║\n";
    cout << "║                                                                       ║\n";
    cout << "║            Get ready to test your luck in this game!                  ║\n";
    cout << "║                                                                       ║\n";
    cout << "║          Select the difficulty level to start:                        ║\n";
    cout << "║                                                                       ║\n";
    cout << "║                  1. Easy     ♣     2. Medium     ♦                    ║\n";
    cout << "║                            3. Hard       ♠                            ║\n";
    cout << "║                                                                       ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

// Function validateInput. It validates the user's input to ensure only values 1, 2, or 3 are accepted — no text or special characters.
int validate()
{
    // Declare variable choice to store the player's input, initialized to 0 to avoid errors.
    int choice = 0;

    // Console message
    cout << "Select your difficulty level: \n";
    // Receive input value
    cin >> choice;

    /*
       While loop verifies no values less than 1 or greater than 3 are received.
       cin.fail(): checks if the input is an integer; triggers if input is char, string, etc.
       cin.peek(): checks that the next character is '\n' to ensure only integer input.
       cin.clear(): clears error flags in the input stream.
       cin.ignore(1000, '\n'): removes remaining characters in the buffer to avoid garbage input.
    */
    while (cin.fail() || cin.peek() != '\n' || choice < 1 || choice > 3)
    {
        cin.clear();
        cin.ignore(1000, '\n');

        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                                            ♠ ♥ Message ♥ ♣                                           ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║           Please do not enter letters or special characters, only numbers between 1 and 3            ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                     Select your difficulty level:                                                    ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";

        // Read input again
        cin >> choice;
    }

    // Return validated integer (1, 2, or 3) to be used in the levels() function.
    return choice;
}

/* Function gameplay. This function handles all the game logic: rolling the dice and verifying the roll number
   through if, else if conditionals. It also checks if the roll becomes a point, then continues rolling until
   the player gets the winning number, the losing number, or runs out of attempts. */

int gameplay(int maxAttempts = 0)
{

    // I declare the player's starting balance. I use 'static' so it keeps its value across games.
    static int balance = 100;

    // I use this variable to store the amount the player wants to bet.
    int bet = 0;

    // If the player has no money left, I end the game immediately.
    if (balance <= 0)
    {
        cout << "You have no money left to bet. Game over.\n";
        pause();
        return 0;
    }

    // I show the player's current balance and ask for a bet within the allowed range.
    cout << "Your current balance: $" << balance << endl;
    cout << "Enter your bet (min $1, max $" << balance << "): ";
    cin >> bet;

    // I validate the input to make sure it's a number and within the allowed range.
    while (cin.fail() || bet < 1 || bet > balance)
    {
        cin.clear();                 // I clear the error state if input failed
        cin.ignore(1000, '\n');      // I discard the rest of the input buffer
        cout << "Invalid bet. Enter a value between $1 and $" << balance << ": ";
        cin >> bet;
    }

    balance -= bet;
    string newGame;
    srand(time(0));

    /* Variable comeOutRoll, type int. Initialized to 0, it stores the number rolled by the shooter on the first dice roll. */
    int comeOutRoll = 0;

    /* Variable point, type int. Initialized to 0, it stores the number rolled that is not 2, 3, 12, 7 or 11,
       then is used to compare with subsequent rolls. */
    int point = 0;

    cout << "Starting the come-out roll...\n";
    pause();

    /* The player starts the first dice roll; we call the rollDiceAnimated function, which generates a random number
       assigned to comeOutRoll to be checked against game conditions. */
    comeOutRoll = rollDiceAnimated();

    cout << "The come-out roll is: " << comeOutRoll << "\n";

    pause();

    // Check if comeOutRoll is 2, 3, or 12; if so, print a losing message.
    if (comeOutRoll == 2 || comeOutRoll == 3 || comeOutRoll == 12)
    {
        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                 ♠ ♥ You Lost ♥ ♣                  ║\n";
        cout << "║                                                   ║\n";
        cout << "║           Craps! You lost the game.               ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";
        pause();
        clearScreen();
    }
    // Check if comeOutRoll is 7 or 11; if so, player wins immediately.
    else if (comeOutRoll == 7 || comeOutRoll == 11)
    {
        cout << "╔═══════════════════════════════════════════════╗\n";
        cout << "║                 ♠ ♥ You Won ♥ ♣               ║\n";
        cout << "║                                               ║\n";
        cout << "║     Congratulations, you won the round!       ║\n";
        cout << "║                                               ║\n";
        cout << "╚═══════════════════════════════════════════════╝\n";
        pause();
        clearScreen();
    }
    // Check if comeOutRoll is 4,5,6,8,9,10 to set the point.
    else if (comeOutRoll == 4 || comeOutRoll == 5 || comeOutRoll == 6 || comeOutRoll == 8 || comeOutRoll == 9 || comeOutRoll == 10)
    {
        cout << "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                                            ♠ ♥ Message ♥ ♣                                                  ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                              The point is set, the shooter will roll again...                               ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                                                                                                             ║\n";
        cout << "║                      If the roll is: " << comeOutRoll << ", the shooter wins; if it's 7, the shooter loses                      ║\n";
        cout << "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";

        // Set the point value for comparison in subsequent rolls.
        point = comeOutRoll;
        pause();

        /* Declare attempts variable, int type, initialized to 0. It counts the number of rolls the player makes.
           This is used to control the number of rolls according to difficulty level, ending the game or prompting
           if the player wants to continue when attempts are exhausted. */
        int attempts = 0;

        // While loop with two conditions:
        // Condition 1: if maxAttempts == 0, meaning unlimited attempts (easy level).
        // Condition 2: if attempts < maxAttempts, limiting attempts for medium or hard levels.
        while (maxAttempts == 0 || attempts < maxAttempts)
        {
            // Increment attempts count for each roll.
            attempts++;

            // Player rolls the dice again; assign new roll to comeOutRoll to compare with point.
            comeOutRoll = rollDiceAnimated();

            cout << "Attempt #" << attempts << endl;
            cout << "The new come-out roll is: " << comeOutRoll << "\n";

            pause();

            // If roll equals the point, player wins.
            if (comeOutRoll == point)
            {
                cout << "╔═════════════════════════════════════════════════════╗\n";
                cout << "║                    ♠ ♥ You Won ♥ ♣                  ║\n";
                cout << "║                                                     ║\n";
                cout << "║                Congratulations, you won!            ║\n";
                cout << "║                                                     ║\n";
                cout << "╚═════════════════════════════════════════════════════╝\n";
                pause();
                clearScreen();
                return 0;
            }
            // If roll is 7, player loses.
            else if (comeOutRoll == 7)
            {
                cout << "╔═════════════════════════════════════════════════════╗\n";
                cout << "║                   ♠ ♥ You Lost ♥ ♣                  ║\n";
                cout << "║                                                     ║\n";
                cout << "║               Sorry, you lost the game.             ║\n";
                cout << "║                                                     ║\n";
                cout << "╚═════════════════════════════════════════════════════╝\n";
                pause();
                clearScreen();
                return 0;
            }
        }

        // If attempts exhausted, player loses.
        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                  ♠ ♥ Message ♥ ♣                  ║\n";
        cout << "║                                                   ║\n";
        cout << "║       Sorry, you have run out of attempts.        ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";

        pause();
        clearScreen();
    }
}

/* Function levels. This function handles the logic of selecting difficulty levels through a switch statement.
There are three cases: (easy, medium, hard). Depending on the selection, we receive the parameter and validate it accordingly. */
int levels(int selection)
{
    switch (selection)
    {

    // If the player selects the easy level, the player has no limit on attempts until they win or lose.
    case 1:
        cout << "You have selected the easy level \n";

        // Call the gameplay function; here MaxAttempts is declared as 0 to indicate unlimited attempts, so no parameter is passed.
        gameplay();

        // Break the switch if this level is selected.
        break;

    case 2:
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                                            ♠ ♥ Message ♥ ♣                                           ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║   You have selected the medium level, you have 5 attempts to roll the dice and get the come-out roll ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";

        /* Call the gameplay function again but this time with a parameter of 5,
           which sets MaxAttempts = 5, and then it will evaluate the attempts until the condition is no longer met. */
        gameplay(5);

        // Break the switch if this level is selected.
        break;

    case 3:
        cout << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════╗\n";
        cout << "║                                                                                                      ║\n";
        cout << "║                                            ♠ ♥ Message ♥ ♣                                           ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "║   You have selected the hard level, you have 3 attempts to roll the dice and get the come-out roll   ║\n";
        cout << "║                                                                                                      ║\n";
        cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════╝\n";

        /* Apply the same logic as the previous case but with a parameter of 3,
           which sets MaxAttempts = 3, and then evaluates attempts until the condition is no longer met. */
        gameplay(3);

        // Break the switch if this level is selected.
        break;

    default:
        cout << "Invalid option ... \n";
        break;
    }
}

/* Function RestartGame. Its purpose is to display a message in the console to the player whether they win or lose,
we indicate if they want to continue playing dice or return to the main menu where there are other games and mini-games. */
void restartGame()
{

    // Declare the variable continuePlaying of type string to store the player's decision.
    string continuePlaying;

    /* We use a do-while to display the message in the console and to receive and store the variable value
    as long as the condition is met. It also allows us to validate if the player is entering an invalid
    parameter that is not Y/N or y/n. */
    do
    {

        // Display the message to the player
        cout << "╔═══════════════════════════════════════════════════╗\n";
        cout << "║                Do you want to keep playing?       ║\n";
        cout << "║                                                   ║\n";
        cout << "║   Yes (Y)                             No (N)      ║\n";
        cout << "║                                                   ║\n";
        cout << "╚═══════════════════════════════════════════════════╝\n";

        // Receive the player's decision and store it in continuePlaying.
        cin >> continuePlaying;

        // Verify that the player enters Y or y; if so, show the menu again.
        if (continuePlaying == "Y" || continuePlaying == "y")
        {
            // Reset the variable selection to 0 to ensure it doesn't keep previous values.
            int selection = 0;

            // Call the clearScreen function to give the player a better experience.
            clearScreen();

            // Again, use the showMenu() function to display difficulty levels to the player.
            showMenu();

            // In the validation method, receive the player's option (1, 2 or 3) and assign it to the selection variable.
            selection = validate();

            // The levels function receives the selection variable, enters a switch, evaluates the case depending on
            // the level selected by the player, and then executes the gameplay function again.
            levels(selection);
        }

        // Check with else if if the player enters N/n, then they want to return to the main menu where other games are.
        else if (continuePlaying == "N" || continuePlaying == "n")
        {
            cout << " Returning to the main menu... \n";

            // Return an exit.
            return;
        }

        // Using else, validate if none of the previous conditions are met. That means the player entered an invalid
        // value such as special characters, other numbers, or even text.
        else
        {
            cout << "Please enter a valid value: \n";
        }

        // Pause to display the message
        pause();

        cin.clear();
        // Clear the screen for a better player experience.
        clearScreen();

        // Repeat while the player hasn't chosen to exit
    } while (continuePlaying != "N" && continuePlaying != "n");
}

int main()
{

    // UTF-8 encoding is a type of encoding that converts special characters so they can be read by computers.
    // SetConsoleOutputCP is a function that allows displaying special characters, ASCII, UNICODE in the console using UTF-8 encoding.
    SetConsoleOutputCP(CP_UTF8);

    // Initialize the variable selection to 0 to ensure no previous values are stored.
    int selection = 0;

    // Call the clearScreen function to provide a better experience for the player.
    clearScreen();

    // Show the difficulty level menu to the player.
    showMenu();

    // Receive the player's option (1, 2, or 3).
    selection = validate();

    // Send the selection variable as a parameter.
    levels(selection);

    // Call the restartGame function to check if the player wants to continue playing or exit.
    restartGame();
}
