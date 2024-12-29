#include "AoCFunctions.h"
#include <iostream>
#include <sstream>

class ClawMachine {
    public:
        long xA;
        long yA;
        long xB;
        long yB;
        long xPrize;
        long yPrize;
};

void dayThirteen() {
    vector<string> input = contentsOfInput();
    vector<ClawMachine> clawMachines;

    string word;
    for (int i = 0; i < input.size(); i += 4) {
        ClawMachine temp;

        std::stringstream sA(input[i]);
        sA >> word; sA >> word; sA >> word;
        temp.xA = stoi(word.substr(2,word.size()-3));
        sA >> word;
        temp.yA = stoi(word.substr(2,word.size()-2));

        std::stringstream sB(input[i+1]);
        sB >> word; sB >> word; sB >> word;
        temp.xB = stoi(word.substr(2,word.size()-3));
        sB >> word;
        temp.yB = stoi(word.substr(2,word.size()-2));

        std::stringstream sP(input[i+2]);
        sP >> word; sP >> word;
        temp.xPrize = stoi(word.substr(2,word.size()-3));
        sP >> word;
        temp.yPrize = stoi(word.substr(2,word.size()-2));
        clawMachines.push_back(temp);
    }

    // The cheapest will be to use as many B button presses, and as few A button presses
    int tokens = 0;
    for (ClawMachine c : clawMachines) {
        
        for (int aPress = 0; c.xA * aPress <= c.xPrize || c.yA * aPress <= c.yPrize; aPress++) {
            int bPress = 0;
            int currentXDist = c.xA * aPress, currentYDist = c.yA * aPress;

            while (currentXDist < c.xPrize && currentYDist < c.yPrize) {
                bPress ++;
                currentXDist += c.xB, currentYDist += c.yB;
            }

            if (currentXDist == c.xPrize && currentYDist == c.yPrize) {
                // Found a formula that works
                tokens += aPress * 3; tokens += bPress;
                break;
            }
        }
    }

    std::cout << "Part 1: " << tokens << std::endl;

    // For part 2, I used substitution:
    // Xa*A + Xb*B = X
    // Ya*A + Yb*B = Y
    // Therefore, A = (X - Y - Xb*B + Yb*B) / (Xa - Ya) or B = (X - Y - Xa*A + Ya*A) / (Xb - Yb)
    // Should find the lowest value of A where both A and B are integers
    long tokens2 = 0;
    for (ClawMachine c : clawMachines) {
        c.xPrize += 10000000000000;
        c.yPrize += 10000000000000;
        long pressA = 0; double pressB;
        do {
            pressB = ((double)c.xPrize - (double)c.yPrize - (double)c.xA*pressA + (double)c.xA*pressA) / ((double)c.xB - (double)c.yB);
            if (trunc(pressB) == pressB) {
                tokens2 += pressA * 3 + trunc(pressB);
            }
        } while (pressB > 0);
    }
    std::cout << "Part 2: " << tokens2 << std::endl;
}