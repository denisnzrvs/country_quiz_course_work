#include "libs/rapidcsv.h"
#include <iostream>
#include <vector>
#include <string>

struct Question {
    std::string question;
    std::string answer;
    std::string category;
    std::string difficulty;
    std::string world;
};

int main() {
    std::string csv = "libs/country_questions.csv";

    rapidcsv::Document doc(csv);

    size_t numRows = doc.GetRowCount();

    std::vector<Question> questions;

    for (size_t i = 0; i < numRows; ++i) {
        Question q;
        q.question = doc.GetCell<std::string>("Question", i);
        q.answer = doc.GetCell<std::string>("Answer", i);
        q.category = doc.GetCell<std::string>("Category", i);
        q.difficulty = doc.GetCell<std::string>("Difficulty", i);
        q.world = doc.GetCell<std::string>("World", i);

        questions.push_back(q);
    }

    for (const auto& q : questions) {
        std::cout << "Question: " << q.question << std::endl;
        std::cout << "Answer: " << q.answer << std::endl;
        std::cout << "Category: " << q.category << std::endl;
        std::cout << "Difficulty: " << q.difficulty << std::endl;
        std::cout << "World: " << q.world << std::endl;
        std::cout << "---------------------------" << std::endl;
    }

    size_t questionIndex = 1; 
    if (questionIndex < questions.size()) {
        std::cout << "Answer to question " << questionIndex + 1 << ": " << questions[questionIndex].answer << std::endl;
    } else {
        std::cout << "Invalid question index." << std::endl;
    }
    
    return 0;
}

