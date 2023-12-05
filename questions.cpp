#include "libs/rapidcsv.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>

struct Question
{
    std::string question;
    std::string answer;
    std::string category;
    std::string difficulty;
    std::string world;
    std::vector<std::string> answers;
};

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

    int index = 1;
    for (const auto &a : question.answers)
    {
        std::cout << index << ". " << a << std::endl;
        ++index;
    }
}

bool checkAnswer(const Question &question, int userChoice)
{
    return question.answer == question.answers[userChoice - 1];
}

std::vector<Question> findQuestions(const std::vector<Question> &questions, const std::string &category, const std::string &difficulty, const std::string &world)
{
    std::vector<Question> result;
    for (const auto &q : questions)
    {
        if (q.category == category && q.difficulty == difficulty && q.world == world)
        {
            result.push_back(q);
            // askQuestion(q);

            int userChoice;
            std::cout << "Enter the number of your answer: ";
            std::cin >> userChoice;

            if (checkAnswer(q, userChoice))
            {
                std::cout << "Correct! You earned 10 points." << std::endl;
                // userScore += 10; // Add a variable to keep track of the user's score
            }
            else
            {
                std::cout << "Incorrect. The correct answer is: " << q.answer << std::endl;
            }
        }
    }

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

    for (auto &q : questions)
    {
        addAnswers(q, questions);
    }

    for (auto &q : questions)
    {
        std::cout << "Question: " << q.question << std::endl;
        std::cout << "Answer: " << q.answer << std::endl;
        std::cout << "Category: " << q.category << std::endl;
        std::cout << "Difficulty: " << q.difficulty << std::endl;
        std::cout << "World: " << q.world << std::endl;
        std::cout << "Answers: " << q.answers.size() << std::endl;
        std::cout << "---------------------------" << std::endl;
    }

    return questions;
}
