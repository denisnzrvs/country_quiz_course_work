#include "colors.h"
#include <iostream>
#include <string>
#include "menu.h"
#include "questions.cpp"
#include <vector>
#include "printScores.cpp"
#include <algorithm>
#include <map>

using namespace std;

// sets difficulty as string to filter questions in findQuestions() (questions.cpp). Runs after user has selected a difficulty.
void setDifficulty(string &level)
{
    static const map<string, string> difficultyMap = {{"B", "Beginner"}, {"M", "Middle"}, {"H", "Hard"}};
    auto it = difficultyMap.find(level);
    if (it != difficultyMap.end())
    {
        level = it->second;
    }
}

// Function to set the part of the world as a string to filter in findQuestions() (questions.cpp). Runs after user has selected a part of the world.
void setWorld(string &worldPart)
{
    static const map<string, string> worldMap = {
        {"Eu", "Europe"}, {"E", "East"}, {"Am", "America"}, {"Af", "Africa"}, {"A", "Asia"}, {"All", "All"}};
    auto it = worldMap.find(worldPart);
    if (it != worldMap.end())
    {
        worldPart = it->second;
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

bool isValidWorldPart(const string &choice)
{
    const vector<string> validChoices = {"Eu", "eu", "E", "e", "Am", "am", "Af", "af", "a", "A", "All", "ALL", "all"};

    return std::any_of(validChoices.begin(), validChoices.end(),
                       [&](const string &validChoice)
                       { return validChoice == choice; });
}

void printDifficultyMenu()
{
    cout << MAGENTA_TEXT << "Choose difficulty" << RESET_COLOR << "\n"
         << "B. Beginner\n"
         << "M. Middle\n"
         << "H. Hard\n\n"
         << MAGENTA_TEXT << "Enter your choice: " << RESET_COLOR << "\n\n";
}

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

bool isValidDifficulty(const string &choice)
{
    const vector<string> validDifficulties = {"B", "b", "M", "m", "H", "h"};
    return find(validDifficulties.begin(), validDifficulties.end(), choice) != validDifficulties.end();
}

// Function to get difficulty input from the user
string getDifficultyInput()
{
    string level;
    printDifficultyMenu();
    cin >> level;
    return level;
}

// Function to handle the play menu
void playMenu()
{
    clearScreen();
    string level = getDifficultyInput();

    if (isValidDifficulty(level))
    {
        string worldPart;
        getWorldInput(worldPart, level);
    }
    else
    {
        playMenu(); // If the input is invalid, recursively call playMenu again
    }
}