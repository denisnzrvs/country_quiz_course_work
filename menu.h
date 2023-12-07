#ifndef MENU_H
#define MENU_H

#include <string>

// Function to set difficulty
void setDifficulty(std::string &level);

// Function to set world
void setWorld(std::string &worldPart);

// Function to clear the screen
void clearScreen();

// Function to print world menu
void printWorldMenu();

// Function to validate world part input
bool isValidWorldPart(const std::string &choice);

// Function to print difficulty menu
void printDifficultyMenu();

// Function to print main menu
void printMainMenu(const std::string &message);

// Function to print world menu and get user input
void getWorldInput(std::string &worldPart, std::string &level);

// Function to validate difficulty input
bool isValidDifficulty(const std::string &choice);

// Function to get difficulty input from the user
std::string getDifficultyInput();

// Function to handle difficulty menu and world menu
void playMenu();

#endif // MENU_H