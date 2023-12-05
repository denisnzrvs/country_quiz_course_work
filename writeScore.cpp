#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void writeScore(string username, int score)
{

    std::ifstream infile("scores.txt");

    if (!infile)
    {
        std::ofstream outfile("scores.txt");
        outfile << username << " " << score << std::endl;
    }
    else
    {
        std::ofstream outfile("scores.txt", std::ios::app);
        outfile << username << " " << score << std::endl;
    }
}

