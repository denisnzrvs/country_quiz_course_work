#include "colors.h"
#include <iostream>
#include <string>
#include "menu.h"
#include "questions.cpp"
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>

using namespace std;

// Function to compare scores for sorting
bool compareScores(const string &a, const string &b)
{
    // Assuming scores are integers, use stoi to convert and compare
    return stoi(a.substr(a.find_last_of(' ') + 1)) > stoi(b.substr(b.find_last_of(' ') + 1));
}

// Prints the scores from file scores.txt sorted descending.
void printScores()
{
    string filename = "scores.txt";
    vector<string> scores;

    // Open the specified file for reading
    ifstream infile(filename);

    if (!infile)
    {
        cerr << "Error: Unable to open the file '" << filename << "'." << endl;
        return;
    }

    // Read lines from the file
    string line;
    while (getline(infile, line))
    {
        scores.push_back(line);
    }

    // Sort scores in descending order
    sort(scores.begin(), scores.end(), compareScores);

    // Display sorted scores
    cout << "Sorted Scores:\n"
         << endl;
    for (const auto &score : scores)
    {
        cout << score << endl;
    }
}

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
         << MAGENTA_TEXT << "Enter your choice: " << RESET_COLOR;
}

bool isValidWorldPart(const string &choice)
{
    const vector<string> validChoices = {"eu", "e", "am", "af", "a", "all"};
    string lowerChoice = choice;
    boost::to_lower(lowerChoice);
    return any_of(validChoices.begin(), validChoices.end(),
                  [&](const string &validChoice)
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
         << MAGENTA_TEXT << "Enter your choice: " << RESET_COLOR;
}

void printMainMenu()
{
    char choice;

    clearScreen();
    cout << MAGENTA_TEXT << "#### Country Quiz ####\n"
         << "Welcome to Country Quiz!" << RESET_COLOR << "\n"
         << "P. Play\n"
         << "S. Score\n"
         << "Q. Quit\n\n"
         << MAGENTA_TEXT << " Enter your choice: " << RESET_COLOR;

    cin >> choice;
    choice = tolower(choice);

    if (choice == 'p')
    {
        playMenu();
    }
    else if (choice == 's')
    {
        clearScreen();
        printScores();
    }
    else if (choice == 'q')
    {
        clearScreen();
        exit(0);
    }
    else
    {
        printMainMenu();
    }
}

void getWorldInput(string &worldPart, string &difficulty)
{
    clearScreen();
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
