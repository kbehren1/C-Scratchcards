// Scratchcards.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>

const std::string numSearch = "0123456789";

int main()
{
    int totalPoints = 0;
    std::string input = "";

    std::ifstream Scratchcard("Scratchcards.txt");

    while (std::getline(Scratchcard, input)) {
        int winningNums[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        int myNums[25] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        int points = 0;
        size_t arrayIterator = 0;

        size_t startPos = input.find_first_of(':');

        while (startPos < input.find_first_of('|')) {
            std::string buildNum = "";
            startPos = input.find_first_of(numSearch, startPos);
            while (input[startPos] != ' ') {
                buildNum += input[startPos];
                startPos++;
            }
            winningNums[arrayIterator] = std::stoi(buildNum);
            arrayIterator++;

            if (input.find_first_of('|', startPos) < input.find_first_of(numSearch, startPos))
                startPos = input.find_first_of('|', startPos);
        }

        arrayIterator = 0;

        while (startPos < input.size()) {
            std::string buildNum = "";
            startPos = input.find_first_of(numSearch, startPos);
            while (input[startPos] != ' ' && startPos < input.size()) {
                buildNum += input[startPos];
                startPos++;
            }
            myNums[arrayIterator] = std::stoi(buildNum);
            arrayIterator++;
        }

        for (int i = 0; i < sizeof(winningNums) / sizeof(int); i++) {
            for (int j = 0; j < sizeof(myNums) / sizeof(int); j++) {
                if (winningNums[i] == myNums[j]) {
                    if (points == 0) points = 1; else points *= 2;
                    break;
                }
            }
        }

        totalPoints += points;
    }

    std::cout << "The total points are worth " << totalPoints << '!';
}

