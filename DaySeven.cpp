#include "AoCFunctions.h"
#include <iostream>
#include <math.h>

void daySeven() {
    vector<string> input = contentsOfInput();
    long long sumNum, colonIndex, numSymbols, temp, test, partOne = 0, partTwo = 0, j;
    vector<long long> equationNums;
    unsigned int bits;
    
    for (string line : input) {
        // Get numbers for operation
        equationNums.clear(); colonIndex = line.find(":");
        sumNum = stoll(line.substr(0,colonIndex));
        line = line.erase(0,colonIndex + 2);
        equationNums = splitStringIntoLongLong(line, " ");
        numSymbols = equationNums.size() - 1;

        // Part One:
        for (bits = 0; bits < pow(2, numSymbols); bits++) {
            j = 0, test = equationNums[0], temp = bits;
            while (temp > 0) {
                if (temp % 2 == 0 )
                    test += equationNums[j+1];
                if (temp % 2 == 1) 
                    test = test * equationNums[j+1];
                
                temp = temp >> 1; j++;
            }
            for (NULL; j < equationNums.size() - 1; j++) {
                test += equationNums[j+1];
            }
            if (test == sumNum) {
                partOne += sumNum;
                break;
            }
        }

        // Part Two:
        for (bits = 0; bits < pow(4, numSymbols); bits++) {
            j = 0, test = equationNums[0], temp = bits;
            while (temp > 0) {
                if (temp % 4 == 0 )
                    test += equationNums[j+1];
                if (temp % 4 == 1) 
                    test = test * equationNums[j+1];
                if (temp % 4 == 2) 
                    test = stoll(std::to_string(test) + std::to_string(equationNums[j+1]));
                if (temp % 4 == 3 )
                    break; 
                
                
                temp = temp >> 2; j++;
            }
            if (temp % 4 == 3) 
                continue;
            for (NULL; j < equationNums.size() - 1; j++) {
                test += equationNums[j+1];
            }
            if (test == sumNum) {
                partTwo += sumNum;
                break;
            }
        }

    }

    std::cout << "Part 1: " << partOne << std::endl;
    std::cout << "Part 2: " << partTwo << std::endl; 
}