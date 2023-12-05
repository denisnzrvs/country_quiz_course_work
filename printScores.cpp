#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Function to compare scores for sorting
bool compareScores(const std::string &a, const std::string &b)
{
    // Assuming scores are integers, use stoi to convert and compare
    return std::stoi(a.substr(a.find_last_of(' ') + 1)) > std::stoi(b.substr(b.find_last_of(' ') + 1));
}

void printScores()
{
    string filename = "scores.txt";
    std::vector<std::string> scores;

    // Open the specified file for reading
    std::ifstream infile(filename);

    if (!infile)
    {
        std::cerr << "Error: Unable to open the file '" << filename << "'." << std::endl;
        return;
    }

    // Read lines from the file
    std::string line;
    while (std::getline(infile, line))
    {
        scores.push_back(line);
    }

    // Sort scores in descending order
    std::sort(scores.begin(), scores.end(), compareScores);

    // Display sorted scores
    std::cout << "Sorted Scores:" << std::endl;
    for (const auto &score : scores)
    {
        std::cout << score << std::endl;
    }
}
