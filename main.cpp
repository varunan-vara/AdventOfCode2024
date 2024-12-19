//
//  main.cpp
//  AdventOfCode2024
//
//  Created by Varunan Varathan on 2024-12-16.
//

#include "Solutions.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    // insert code here...
    int day = 0;
    std::cout << "Enter your file input as input.txt in this folder." << std::endl;
    std::cout << "Enter the puzzle day: ";
    std::cin >> day;
    std::cout << std::endl;

    switch (day) {
        case 1:
            dayOne();
            break;
        case 2:
            dayTwo();
            break;
        case 3:
            dayThree();
            break;
        case 4:
            dayFour();
            break;
        case 5:
            dayFive();
            break;
        case 6:
            daySix();
            break;
        case 7:
            daySeven();
            break;
        case 8:
            dayEight();
            break;
        case 9:
            dayNine();
            break;
        case 10:
            dayTen();
        default:
            NULL;
    }
    return 0;
}
