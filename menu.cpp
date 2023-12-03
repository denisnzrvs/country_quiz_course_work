#include <iostream>
#include <string>
#include "menu.h"

using namespace std;

void clearScreen()
{
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code for clearing screen
}

void playMenu()
{
    clearScreen();
    cout << "play menu selected!";
}

void scoreMenu()
{
    clearScreen();
    cout << "score menu selected!";
}

void quitGame()
{
    clearScreen();
    cout << "Thanks for playing! See you next time!";
    exit(0);
}

void mainMenu(const std::string &message)
{
    char choice;

    clearScreen();
    std::cout << "#### Country Quiz ####" << endl;
    std::cout << "Welcome to Country Quiz!" << endl;
    std::cout << endl;
    std::cout << "P. Play" << endl;
    std::cout << "S. Score" << endl;
    std::cout << "Q. Quit" << endl;
    std::cout << endl;
    std::cout << message << " Enter your choice: ";

    cin >> choice;

    if (choice == 'P' || choice == 'p')
    {
        playMenu();
    }
    else if (choice == 'S' || choice == 's')
    {
        scoreMenu();
    }
    else if (choice == 'Q' || choice == 'q')
    {
        quitGame();
    }
    else
    {
        mainMenu("Invalid choice!");
    }
}