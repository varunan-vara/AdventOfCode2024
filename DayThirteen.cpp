#include "AoCFunctions.h"
#include <iostream>

class ClawMachine {
    public:
        long long xA;
        long long yA;
        long long xB;
        long long yB;
        long long xPrize;
        long long yPrize;
        int aToken = 3;
        int bToken = 1;
        int maxButtonPress = 100; // Relevant for Part One only

        ClawMachine (long long xAInput, long long yAInput, long long xBInput, long long yBInput, long long xPrizeInput, long long yPrizeInput) {
            xA = xAInput, yA = yAInput, xB = xBInput, yB = yBInput, xPrize = xPrizeInput, yPrize = yPrizeInput;
        }

        long long minimumNumberOfTokensPartOne () {
            // Strategy: brute force
            // If not possible, return 0
            std::vector<long long> possibleTokens;
            for (long long a = 0; a <= maxButtonPress; a++) {
                for (long long b = 0; b <= maxButtonPress; b++) {
                    if (((a * xA) + (b * xB)) == xPrize && ((a * yA) + (b * yB)) == yPrize) {
                        possibleTokens.push_back((a * aToken) + (b * bToken));
                        break;
                    }
                }
            }
            
            if (possibleTokens.size() == 0) {return 0;}
            else {return * std::min_element(possibleTokens.begin(), possibleTokens.end());}
        }
        long long minimumNumberOfTokens (long long modifier) {
            // Strategy: Linear Algebra
            // Based on amnorm's post
            long long txPrize = xPrize + modifier, tyPrize = yPrize + modifier;
            long long determinant = ((xA * yB) - (xB * yA));
            if (determinant == 0) { return 0; }
            long long dA = txPrize * yB - xB * tyPrize;
            long long dB = xA * tyPrize - yA * txPrize;
            if (dA % determinant == 0 && dB % determinant == 0) {
                long long a = dA / determinant;
                long long b = dB / determinant;
                return (a * (long long) aToken) + (b * (long long) bToken);
            }
            return 0;
        }

};

void dayThirteen() {
    vector<string> input = contentsOfInput();
    vector<ClawMachine> cmList;

    long long xA, xB, yA, yB, xPrize, yPrize;
    for (int i = 0; i < input.size(); NULL) {
        xA = stoll(input[i].substr(11, input[i].find(',') - 11));
        yA = stoll(input[i].substr(input[i].find(',') + 4));
        i++;
        xB = stoll(input[i].substr(11, input[i].find(',') - 11));
        yB = stoll(input[i].substr(input[i].find(',') + 4));
        i++;
        xPrize = stoll(input[i].substr(9, input[i].find(',') - 9));
        yPrize = stoll(input[i].substr(input[i].find(',') + 4));
        i += 2;
        cmList.push_back(ClawMachine(xA,yA,xB,yB,xPrize,yPrize));
    }
    long long tokens = 0;
    for (ClawMachine cm : cmList) {
        tokens += cm.minimumNumberOfTokens(0);
    }
    std::cout << "Part One: " << tokens << std::endl;
    tokens = 0;
    for (ClawMachine cm : cmList) {
        tokens += cm.minimumNumberOfTokens(10000000000000);
    }
    std::cout << "Part Two: " << tokens << std::endl;
}