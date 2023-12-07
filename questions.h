#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <string>
#include <vector>

struct Question
{
    std::string question;
    std::string answer;
    std::string category;
    std::string difficulty;
    std::string world;
    std::vector<std::string> answers;
};

void printSeparator();
void printWin();
void addAnswers(Question &question, const std::vector<Question> &allQuestions);
bool checkAnswer(const Question &question, const std::string &userAnswer);
bool allAdd(const std::vector<Question> &allQuestions, const std::vector<Question> &addedQuestions);
bool filterQuestion(const Question &question, const std::string &worldPart, const std::string &difficulty);
void findQuestions(const std::vector<Question> &allQuestions, std::vector<Question> &addedQuestions, const std::string &worldPart, const std::string &difficulty);
std::vector<Question> setupVector();
#endif // QUESTIONS_H