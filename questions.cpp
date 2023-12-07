#include "colors.h"
#include "libs/rapidcsv.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include "writeScore.cpp"
#include <thread>

int score = 0;

struct Question
{
    string question;
    string answer;
    string category;
    string difficulty;
    string world;
    vector<string> answers;
};

void printSeparator()
{
    cout << "<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>:<:>" << endl;
}

void printWin()
{
    cout << R"(
      ....           ....           ....           ....
     ||             ||             ||             ||
 /'''l|\        /'''l|\        /'''l|\        /'''l|\
/_______\      /_______\      /_______\      /_______\
|  .-.  |------|  .-.  |------|  .-.  |------|  .-.  |------
 __|L|__| .--. |__|L|__| .--. |__|L|__| .--. |__|L|__| .--.
_\  \\p__`o-o'__\  \\p__`o-o'__\  \\p__`o-o'__\  \\p__`o-o'_
------------------------------------------------------------
------------------------------------------------------------
)" << endl;
}

// Every question contains the correct answer for it. This function adds two random answers and the correct answer to the Question object's answers vector.
void addAnswers(Question &question, const vector<Question> &allQuestions)
{
    // adds the correct answer to the answers vector
    question.answers.push_back(question.answer);

    // filters all the other (non-correct) answers
    vector<string> otherAnswers;
    for (const auto &q : allQuestions)
    {
        if (q.answer != question.answer)
        {
            otherAnswers.push_back(q.answer);
        }
    }
    // randomises the vector of non-correct answers
    random_device rd;
    mt19937 g(rd());
    shuffle(otherAnswers.begin(), otherAnswers.end(), g);

    // adds the first two answers from the randomised vector to the answers vector of the question.
    for (size_t i = 0; i < 2; ++i)
    {
        question.answers.push_back(otherAnswers[i]);
    }
    // shuffles all the answers of the question iself.
    shuffle(question.answers.begin(), question.answers.end(), g);
}

// checks if the user's answer to the question is valid. If not, ignores the input.
bool checkAnswer(const Question &question, int userChoice)
{
    if (userChoice != 1 && userChoice != 2 && userChoice != 3)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return question.answer == question.answers[userChoice - 1];
}

bool filter(const Question &question, const std::string &difficulty, const std::string &world)
{
    // Check if the world matches or if "All" is selected. If not, exclude the question.
    if (world != question.world && world != "All")
        return false;

    // Include questions based on difficulty selection.
    if (difficulty == "Hard" || (difficulty == "Middle" && (question.difficulty == "Middle" || question.difficulty == "Beginner")) || (difficulty == "Beginner" && question.difficulty == "Beginner"))
        return true;

    return false; // Exclude the question if no conditions are met.
}

void finish(const int score)
{
    std::cout << std::endl;
    std::cout << "End of game! Your score is: " << score << std::endl;
    std::cout << "Let's save your game. Enter your name: ";
    std::string username;
    std::cin >> username;
    writeScore(username, score);
    cout << "Thanks for playing!";
    printWin();
}

void randomize(std::vector<Question> &questions)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(questions.begin(), questions.end(), g);
}

void printQuestions(std::vector<Question> questions)
{
    for (int i = 0; i < questions.size(); i++)
    {
        Question q = questions[i];
        printSeparator();
        this_thread::sleep_for(chrono::milliseconds(3000));
        clearScreen();
        printSeparator();
        cout << q.question << "\n\n";
        addAnswers(q, questions);

        for (int i = 0; i < q.answers.size(); i++)
        {
            cout << i + 1 << ". " << q.answers[i] << endl;
        }
        cout << endl;

        int userChoice;
        cout << "Enter the number of your answer: ";
        cin >> userChoice;

        if (checkAnswer(q, userChoice))
        {
            cout << GREEN_TEXT << "Correct! You earned 10 points." << RESET_COLOR << endl;
            score += 10;
        }
        else
        {
            cout << RED_TEXT << "Incorrect. The correct answer is: " << q.answer << RESET_COLOR << endl;
        }
    }
    finish(score);
}

void findQuestions(std::vector<Question> questions, const std::string &difficulty, const std::string &world)
{
    randomize(questions);
    int questionCount = 0;
    cout << "Enter only the number of the answer you choose\n"
         << endl;
    cout << "Difficulty: " << difficulty << endl;
    cout << "World: " << world << endl;

    vector<Question> result;
    for (auto &q : questions)
    {
        if (filter(q, difficulty, world))
        {
            result.push_back(q);
            questionCount++;
            if (questionCount == 5)
            {
                break;
            }
        }
    }
    printQuestions(result);
}

vector<Question> setupVector()
{
    string csv = "libs/country_questions.csv";

    rapidcsv::Document doc(csv);

    size_t numRows = doc.GetRowCount();
    vector<Question> questions;

    for (size_t i = 0; i < numRows; ++i)
    {
        Question q;
        q.question = doc.GetCell<string>("Question", i);
        q.answer = doc.GetCell<string>("Answer", i);
        q.category = doc.GetCell<string>("Category", i);
        q.difficulty = doc.GetCell<string>("Difficulty", i);
        q.world = doc.GetCell<string>("World", i);

        questions.push_back(q);
    }

    return questions;
}