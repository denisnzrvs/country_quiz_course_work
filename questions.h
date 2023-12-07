#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <string>
#include <vector>
using namespace std;
struct Question
{
    string question;
    string answer;
    string category;
    string difficulty;
    string world;
    vector<string> answers;
};

void printSeparator();
void printWin();
void addAnswers(Question &question, const vector<Question> &allQuestions);
bool checkAnswer(const Question &question, const string &userAnswer);
bool allAdd(const vector<Question> &allQuestions, const vector<Question> &addedQuestions);
bool filterQuestion(const Question &question, const string &worldPart, const string &difficulty);
void findQuestions(const vector<Question> &allQuestions, vector<Question> &addedQuestions, const string &worldPart, const string &difficulty);
vector<Question> setupVector();
void printQuestion(const Question &question);
void writeScore(string username, int score);
#endif // QUESTIONS_H