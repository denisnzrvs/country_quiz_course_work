#include <iostream>
#include <string>
#include "menu.h"
#include "questions.cpp"
#include <vector>
#include "printScores.cpp"

using namespace std;

void setDifficulty(string &level)
{
    if (level == "B" || level == "b")
    {
        level = "Beginner";
    }
    else if (level == "M" || level == "m")
    {
        level = "Middle";
    }
    else if (level == "H" || level == "h")
    {
        level = "Hard";
    }
}

void setWorld(string &worldPart)
{
    if (worldPart == "Eu" || worldPart == "eu")
    {
        worldPart = "Europe";
    }
    else if (worldPart == "E" || worldPart == "e")
    {
        worldPart = "East";
    }
    else if (worldPart == "Am" || worldPart == "am")
    {
        worldPart = "America";
    }
    else if (worldPart == "Af" || worldPart == "af")
    {
        worldPart = "Africa";
    }
    else if (worldPart == "A" || worldPart == "a")
    {
        worldPart = "Asia";
    }
    else if (worldPart == "All" || worldPart == "ALL")
    {
        worldPart = "All";
    }
}

void clearScreen()
{
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code for clearing screen
}

void playMenu()
{
    clearScreen();
    string level;
    string worldPart;

    cout << "Choose dificulty" << endl;
    cout << endl;
    cout << "B. Beginner" << endl;
    cout << "M. Middle" << endl;
    cout << "H. Hard" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cout << endl;
    cin >> level;
    if (level == "B" || level == "b" || level == "M" || level == "m" || level == "H" || level == "h")
    {
        clearScreen();
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
        if (worldPart == "Eu" || worldPart == "eu" || worldPart == "E" || worldPart == "e" || worldPart == "Am" || worldPart == "am" || worldPart == "Af" || worldPart == "af" || worldPart == "a" || worldPart == "A" || worldPart == "All" || worldPart == "ALL" || worldPart == "all")
        {
            clearScreen();
            setDifficulty(level);
            setWorld(worldPart);
            cout << "Game starts now" << endl;
            // timer for 5 secqs
            vector<Question> questions = setupVector();
            findQuestions(questions, level, worldPart);
        }
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
        printScores();
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