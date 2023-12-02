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
    char level;
    char worldPart;
    
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
        cout << "Choose dificulty" << endl;
        cout << endl;
        cout << "B. Beginner" << endl;
        cout << "M. Middle" << endl;
        cout << "H. Hard" << endl;
        cout << endl;
        cout << "Enter your choice: ";
        cout << endl;
        cin >> level;
        if (level == 'B' || level == 'b' || level == 'M' || level == 'm' || level == 'H' || level == 'h' )
            {
            clearScreen();
            cout << "#### Country Quiz ####" << endl;
            cout << "Choose part of the World" << endl;
            cout << endl;
            cout << "Eu. Europe" << endl;
            cout << "E. East" << endl;
            cout << "Am. America" << endl;
            cout << "Af. Africa" << endl;
            cout << "A. Asia" << endl;
            cout << "All." << endl;
            cout << endl;
            cout << "Enter your choice: ";
            cout << endl;
            cin >> worldPart;
            }
    }
    return 0;
}