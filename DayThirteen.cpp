#include "AoCFunctions.h"
#include <iostream>
#include <sstream>

long gcd (long a, long b) {
    while (b != 0) {
        a = b;
        b = a % b;
    }
    return a;
}

class ClawMachine {
    public:
        long xA;
        long yA;
        long xB;
        long yB;
        long xPrize;
        long yPrize;
        int aToken = 3;
        int bToken = 1;
        int maxButtonPress = 100;

        ClawMachine (long xAInput, long yAInput, long xBInput, long yBInput, long xPrizeInput, long yPrizeInput) {
            xA = xAInput, yA = yAInput, xB = xBInput, yB = yBInput, xPrize = xPrizeInput, yPrize = yPrizeInput;
        }

        std::pair<long, long> move (std::pair<long,long> coord, char button) {
            if (button == 'a') {
                coord.first += xA, coord.second += yA;
            } else {
                coord.first += xB, coord.second += yB;
            }
            return coord;
        }

        int minimumNumberOfTokens () {
            // Strategy: brute force
            // If not possible, return 0
            if (gcd(xA, xB) % xPrize != 0 || gcd(yA, yB) % yPrize != 0) {
                return 0;
            }
            return 0;
        }

};

void dayThirteen() {
    
}