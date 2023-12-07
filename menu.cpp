#include "colors.h"
#include <iostream>
#include <string>
#include "menu.h"
#include "questions.cpp"
#include <vector>
#include "printScores.cpp"
#include <algorithm>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

// sets difficulty as string to filter questions in findQuestions() (questions.cpp). Runs after user has selected a difficulty.
void setDifficulty(string &difficulty)
{
    static const map<string, string> difficultyMap = {{"b", "Beginner"}, {"m", "Middle"}, {"h", "Hard"}};
    auto it = difficultyMap.find(difficulty);
    if (it != difficultyMap.end())
    {
        difficulty = it->second;
    }
}

// Function to set the part of the world as a string to filter in findQuestions() (questions.cpp). Runs after user has selected a part of the world.
void setWorld(string &worldPart)
{
    static const map<string, string> worldMap = {
        {"eu", "Europe"}, {"e", "East"}, {"am", "America"}, {"af", "Africa"}, {"a", "Asia"}, {"all", "All"}};
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
    const vector<string> validChoices = {"eu", "e", "am", "af", "a", "all"};
    string lowerChoice = choice;
    boost::to_lower(lowerChoice);
    return std::any_of(validChoices.begin(), validChoices.end(),
                       [&](const std::string &validChoice)
                       {
                           return boost::iequals(validChoice, lowerChoice);
                       });
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
    choice = tolower(choice);

    if (choice == 'p')
    {
        playMenu();
    }
    else if (choice == 's')
    {
        printScores();
    }
    else if (choice == 'q')
    {
        exit(0);
    }
    else
    {
        printMainMenu("Invalid choice!");
    }
}

void getWorldInput(string &worldPart, string &difficulty)
{
    printWorldMenu();
    cin >> worldPart;
    boost::to_lower(worldPart);
    if (isValidWorldPart(worldPart))
    {
        clearScreen();
        setDifficulty(difficulty);
        setWorld(worldPart);
        cout << "Game starts now" << endl;
        // timer for 5 seconds
        vector<Question> questions = setupVector();
        findQuestions(questions, difficulty, worldPart);
    }
    else
    {
        getWorldInput(worldPart, difficulty);
    }
}

bool isValidDifficulty(const string &choice)
{
    const vector<string> validDifficulties = {"b", "m", "h"};
    string lowerChoice = choice;
    boost::to_lower(lowerChoice);
    return find(validDifficulties.begin(), validDifficulties.end(), lowerChoice) != validDifficulties.end();
}

// Function to get difficulty input from the user
string getDifficultyInput()
{
    string difficulty;
    printDifficultyMenu();
    cin >> difficulty;
    boost::to_lower(difficulty);
    clearScreen();
    return difficulty;
}

// Function to handle the play menu
void playMenu()
{
    clearScreen();
    string difficulty = getDifficultyInput();

    if (isValidDifficulty(difficulty))
    {
        string worldPart;
        getWorldInput(worldPart, difficulty);
    }
    else
    {
        playMenu(); // If the input is invalid, recursively call playMenu again
    }
}