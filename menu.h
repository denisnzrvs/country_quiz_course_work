#ifndef MENU_H
#define MENU_H

#include <string>
using namespace std;

void setDifficulty(string &level);
void setWorld(string &worldPart);
void clearScreen();
void printWorldMenu();
bool isValidWorldPart(const string &choice);
void printDifficultyMenu();
void printMainMenu();
void getWorldInput(string &worldPart, string &level);
bool isValidDifficulty(const string &choice);
string getDifficultyInput();
void playMenu();
void printScores();
#endif // MENU_H