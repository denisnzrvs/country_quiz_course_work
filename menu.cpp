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
    char level;
    char worldPart;

    cout << "Choose dificulty" << endl;
    cout << endl;
    cout << "B. Beginner" << endl;
    cout << "M. Middle" << endl;
    cout << "H. Hard" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cout << endl;
    cin >> level;
    if (level == 'B' || level == 'b' || level == 'M' || level == 'm' || level == 'H' || level == 'h')
    {
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