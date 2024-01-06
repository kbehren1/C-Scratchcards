// Scratchcards.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string numSearch = "0123456789";

bool charCompare(char character, std::string otherChars) {
    bool foundChar = false;

    for (char i : otherChars) {
        if (i == character) {
            foundChar = true;
            break;
        }
    }

    return foundChar;
}

void createNumArray(std::vector<int>& nums, std::string numsStr) {

    std::string buildNum = "";

    for (char i : numsStr) {
        if (charCompare(i, numSearch))
            buildNum += i;
        else if (buildNum != "") {
            nums.push_back(std::stoi(buildNum));
            buildNum = "";
        }
    }

    if (buildNum != "") nums.push_back(std::stoi(buildNum));
}

int calcPoints(std::vector<int> winningNums, std::vector<int> myNums) {
    int points = 0;
    for (int i : winningNums) {
        for (int j : myNums) {
            if (i == j) {
                points = (points == 0) ? 1 : points * 2;
                break;
            }
        }
    }
    return points;
}

int main()
{
    int totalPoints = 0;
    std::string input = "";

    std::ifstream Scratchcard("Scratchcards.txt");

    while (std::getline(Scratchcard, input)) {
        std::vector<int> winningNums { };
        std::vector<int> myNums { };

        int points = 0;

        std::string winningNumsStr = input.substr(input.find_first_of(':')+1, (input.find_first_of('|') - (input.find_first_of(':')+1)));
        std::string myNumsStr = input.substr(input.find_first_of('|')+1, std::string::npos);

        createNumArray(winningNums, winningNumsStr);
        createNumArray(myNums, myNumsStr);

        totalPoints += calcPoints(winningNums, myNums);
    }

    std::cout << "The total points are worth " << totalPoints << '!';
}

