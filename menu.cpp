#include "colors.h"
#include <iostream>
#include <string>
#include "menu.h"
#include "questions.cpp"
#include <vector>
#include "printScores.cpp"

using namespace std;

// sets difficulty as string to filter questions in findQuestions() (questions.cpp). Runs after user has selected a difficulty.
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

// Function to set the part of the world as a string to filter in findQuestions() (questions.cpp). Runs after user has selected a part of the world.
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
    else if (worldPart == "All" || worldPart == "ALL" || worldPart == "all")
    {
        worldPart = "All";
    }
}

// Function to clear the screen
void clearScreen()
{
    cout << "\033[2J\033[1;1H"; // ANSI escape code for clearing screen
}

void printWorldMenu()
{
    cout << MAGENTA_TEXT << "Choose part of the World" << RESET_COLOR << "\n"
         << "Eu. Europe\n"
         << "E. East\n"
         << "Am. America\n"
         << "Af. Africa\n"
         << "A. Asia\n"
         << "All.\n\n"
         << MAGENTA_TEXT << "Enter your choice: " << RESET_COLOR << "\n\n";
}

// Function to validate world part input
bool isValidWorldPart(const string &choice)
{
    const vector<string> validChoices = {"Eu", "eu", "E", "e", "Am", "am", "Af", "af", "a", "A", "All", "ALL", "all"};
    return find(validChoices.begin(), validChoices.end(), choice) != validChoices.end();
}

// Function to print difficulty menu
void printDifficultyMenu()
{
    cout << MAGENTA_TEXT << "Choose difficulty" << RESET_COLOR << "\n"
         << "B. Beginner\n"
         << "M. Middle\n"
         << "H. Hard\n\n"
         << MAGENTA_TEXT << "Enter your choice: " << RESET_COLOR << "\n\n";
}

// Function to print main menu
void printMainMenu(const string &message)
{
    char choice;

    clearScreen();
    cout << MAGENTA_TEXT << "#### Country Quiz ####\n"
         << "Welcome to Country Quiz!" << RESET_COLOR << "\n"
         << "P. Play\n"
         << "S. Score\n"
         << "Q. Quit\n\n"
         << MAGENTA_TEXT << message << " Enter your choice: " << RESET_COLOR;

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
        exit(0);
    }
    else
    {
        printMainMenu("Invalid choice!");
    }
}

// Function to print world menu and get user input
void getWorldInput(string &worldPart, string &level)
{
    printWorldMenu();
    cin >> worldPart;
    if (isValidWorldPart(worldPart))
    {
        clearScreen();
        setDifficulty(level);
        setWorld(worldPart);
        cout << "Game starts now" << endl;
        // timer for 5 seconds
        vector<Question> questions = setupVector();
        findQuestions(questions, level, worldPart);
    }
    else
    {
        getWorldInput(worldPart, level);
    }
}

// Function to handle difficulty menu and world menu
void playMenu()
{
    clearScreen();
    string level;
    string worldPart;

    printDifficultyMenu();
    cin >> level;
    if (level == "B" || level == "b" || level == "M" || level == "m" || level == "H" || level == "h")
    {
        getWorldInput(worldPart, level);
    }
    else
    {
        playMenu();
    }
}