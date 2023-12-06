#include "libs/rapidcsv.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include "writeScore.cpp"
int score = 0;
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define RESET_COLOR "\033[0m"



struct Question
{
    std::string question;
    std::string answer;
    std::string category;
    std::string difficulty;
    std::string world;
    std::vector<std::string> answers;
};

void printSeparator() {
    std::cout << "<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>" << std::endl;
}

void printWin() {
    std::cout << R"(
      ....           ....           ....           ....
     ||             ||             ||             ||
 /'''l|\        /'''l|\        /'''l|\        /'''l|\
/_______\      /_______\      /_______\      /_______\
|  .-.  |------|  .-.  |------|  .-.  |------|  .-.  |------
 __|L|__| .--. |__|L|__| .--. |__|L|__| .--. |__|L|__| .--.
_\  \\p__`o-o'__\  \\p__`o-o'__\  \\p__`o-o'__\  \\p__`o-o'_
------------------------------------------------------------
------------------------------------------------------------
)" << std::endl;
}

void addAnswers(Question &question, const std::vector<Question> &allQuestions)
{
    question.answers.push_back(question.answer);

    std::vector<std::string> otherAnswers;
    for (const auto &q : allQuestions)
    {
        if (q.answer != question.answer)
        {
            otherAnswers.push_back(q.answer);
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(otherAnswers.begin(), otherAnswers.end(), g);

    for (size_t i = 0; i < 2; ++i)
    {
        question.answers.push_back(otherAnswers[i]);
    }

    std::shuffle(question.answers.begin(), question.answers.end(), g);
}

bool checkAnswer(const Question &question, int userChoice)
{
    if (userChoice != 1 && userChoice != 2 && userChoice != 3)
    {
        std::cin.clear();  // Clear the error state
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore invalid input
        return false;
    }
    return question.answer == question.answers[userChoice - 1];
}

bool allAdd(const Question &question, const std::string &difficulty)
{
    if (difficulty == "Hard" && (question.difficulty == "Hard" || question.difficulty == "Middle" || question.difficulty == "Beginner"))
    {
        return true;
    }
    else if (difficulty == "Middle" && (question.difficulty == "Middle" || question.difficulty == "Beginner"))
    {
        return true;
    }
    else if (difficulty == "Beginner" && question.difficulty == "Beginner")
    {
        return true;
    }
    return false;
}
bool filter(const Question &question, const std::string &difficulty, const std::string &world)
{ 
    if (world == "All"){
        return allAdd(question, difficulty);
    }
    if (difficulty == "Hard" && question.difficulty == difficulty && world == question.world)
    {
        if (question.difficulty == "Middle" || question.difficulty == "Beginner" || question.difficulty == "Hard")
        {
            return true;
        }
    }
    else if (difficulty == "Middle" && world == question.world)
    {
        if (question.difficulty == "Middle" || question.difficulty == "Beginner")
        {
            return true;
        }
        
    } else if (difficulty == "Beginner" && world == question.world && question.difficulty == difficulty)
    {
        return true;
    }
    return false;
}

std::vector<Question> findQuestions(std::vector<Question> questions, const std::string &difficulty, const std::string &world)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);
    int questionCount = 0;

    cout << "Enter only number of the number you choose >>" << endl;
    cout << " " << endl;
    cout << "You have 30 seconds to complete the quiz " << endl;
    cout << "Difficulty: " << difficulty << endl;
    cout << "World: " << world << endl;

    std::vector<Question> result;
    for (auto &q : questions)
    {
        if (filter(q, difficulty, world))
        {
            questionCount++;
            if (questionCount > 5)
            {
                break;
            }
            result.push_back(q);
            printSeparator();
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
            clearScreen();
            printSeparator();
            std::cout << q.question << endl;
            cout << endl;
            addAnswers(q, questions);

            for (int i = 0; i < q.answers.size(); i++)
            {
                cout << i + 1 << ". " << q.answers[i] << endl;
            }
            cout << endl;

            int userChoice;
            std::cout << "Enter the number of your answer: ";
            std::cin >> userChoice;


            if (checkAnswer(q, userChoice))
            {
                std::cout << GREEN_TEXT << "Correct! You earned 10 points." << RESET_COLOR << std::endl;
                score += 10;
            }
            else
            {
                std::cout << RED_TEXT << "Incorrect. The correct answer is: " << q.answer << RESET_COLOR << std::endl;
            }
        }
    }

    cout << endl;
    cout << "End of game! Your score is: " << score << endl;
    cout << "Let's save your game. Enter your name: ";
    string username;
    cin >> username;
    writeScore(username, score);
    cout << "Thanks for playing!";
    printWin();

    return result;
}

vector<Question> setupVector()
{
    std::string csv = "libs/country_questions.csv";

    rapidcsv::Document doc(csv);

    size_t numRows = doc.GetRowCount();
    std::vector<Question> questions;

    for (size_t i = 0; i < numRows; ++i)
    {
        Question q;
        q.question = doc.GetCell<std::string>("Question", i);
        q.answer = doc.GetCell<std::string>("Answer", i);
        q.category = doc.GetCell<std::string>("Category", i);
        q.difficulty = doc.GetCell<std::string>("Difficulty", i);
        q.world = doc.GetCell<std::string>("World", i);

        questions.push_back(q);
    }

    return questions;
}
