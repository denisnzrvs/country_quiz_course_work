#include <iostream>
#include <string>
#include <ctime>

void clearScreen()
{
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code for clearing screen
}
using namespace std;
int main()
{

    clearScreen();

    cout << "#### Country Quiz ####" << endl;
    char choice;
    cout
        << "Welcome to Country Quiz!" << endl;
    cout << endl;
    cout << "P. Play" << endl;
    cout << "S. Score" << endl;
    cout << "Q. Quit" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    if (choice == 'Q' || choice == 'q')
    {
        clearScreen();
        cout << "#### Country Quiz ####" << endl;
        cout << "Thanks for playing!" << endl;
    }

    if (choice == 'S' || choice == 's')
    {
        clearScreen();
        cout << "#### Country Quiz Scoreboard ####" << endl;
        cout << "1. " << endl;
        cout << "2. " << endl;
        cout << "Q. Quit" << endl;
        cin >> choice;
        if (choice == 'Q' || choice == 'q')
        {
            clearScreen();
            cout << "#### Country Quiz ####" << endl;
            cout << "Thanks for playing!" << endl;
        }
    }

    if (choice == 'P' || choice == 'p')
    {
        clearScreen();
        cout << "#### Country Quiz ####" << endl;
        cout << "this is where the game should be, but it is currently on vacation." << endl;
        cout << "Q. Quit" << endl;
        cin >> choice;
        if (choice == 'Q' || choice == 'q')
        {
            clearScreen();
            cout << "#### Country Quiz ####" << endl;
            cout << "Thanks for playing!" << endl;
        }
    }
    return 0;
}