// Scratchcards.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string numSearch = "0123456789";

class Scratchcard {
private: 
    std::vector<int> winningNums{};
    std::vector<int> nums{};
    int amountOfWinningNumbers;
    int points;
    int id;
    void incrementWinningNumbers() { amountOfWinningNumbers++; }
    void setPoints(int number) { points = number; }
    int copies;

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
public:

    Scratchcard(int idNum) {
        id = idNum;
        amountOfWinningNumbers = 0;
        points = 0;
        copies = 1;
    }

    void calcPoints() {
        int points = 0;
        for (int i : winningNums) {
            for (int j : nums) {
                if (i == j) {
                    points = (points == 0) ? 1 : points * 2;
                    incrementWinningNumbers();
                    break;
                }
            }
        }
        setPoints(points);
    }

    void addWinningCardNums(std::string numsStr) {
        std::string buildNum = "";

        for (char i : numsStr) {
            if (charCompare(i, numSearch))
                buildNum += i;
            else if (buildNum != "") {
                winningNums.push_back(std::stoi(buildNum));
                buildNum = "";
            }
        }

        if (buildNum != "")
            winningNums.push_back(std::stoi(buildNum));
    }

    void addMyCardNums(std::string numsStr) {
        std::string buildNum = "";

        for (char i : numsStr) {
            if (charCompare(i, numSearch))
                buildNum += i;
            else if (buildNum != "") {
                nums.push_back(std::stoi(buildNum));
                buildNum = "";
            }
        }

        if (buildNum != "") {
            nums.push_back(std::stoi(buildNum));
        }
    }

    int getWinningNumbers() { return amountOfWinningNumbers; }
    int getWinningNumElement(int element) { return winningNums.at(element); }
    int getNumElement(int element) { return nums.at(element); }
    int getPoints() { return points; }
    int getID() { return id; }
    int getCopies() { return copies; }
    void adjustCopies(int num) { copies += num; }
};

bool inRange(int num, int beginRange, int endRange) {
    return (num > beginRange && num < endRange) ? true : false;
}

int main()
{
    int totalPoints = 0;
    int scratchcardID = 0;
    int totalScratchcards = 0;

    std::string input = "";
    std::vector<Scratchcard> cards{ };

    std::ifstream ScratchcardFile("Scratchcards.txt");

    while (std::getline(ScratchcardFile, input)) {
        scratchcardID++;
        Scratchcard newScratchCard = Scratchcard(scratchcardID);

        std::string winningNumsStr = input.substr(input.find_first_of(':')+1, (input.find_first_of('|') - (input.find_first_of(':')+1)));
        std::string myNumsStr = input.substr(input.find_first_of('|')+1, std::string::npos);

        newScratchCard.addWinningCardNums(winningNumsStr);
        newScratchCard.addMyCardNums(myNumsStr);
        newScratchCard.calcPoints();

        cards.push_back(newScratchCard);

        totalPoints += newScratchCard.getPoints();
    }

    for (int i = 0; i < cards.size(); i++) {
        totalScratchcards += cards[i].getCopies();

        if (cards[i].getWinningNumbers() == 0 && cards[i].getCopies() == 0)
            break;

        for (int j = i+1; j <= i + cards[i].getWinningNumbers(); j++)
            cards[j].adjustCopies(cards[i].getCopies());
    }

    std::cout << "The total points are worth " << totalPoints << "!\n";
    std::cout << "The total scratchcards are " << totalScratchcards << '!';
}

