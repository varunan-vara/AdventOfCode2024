// AdventOfCode2024Proj.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "../AdventOfCode2024Sol/Solutions.h"

int main()
{
    int day;
    std::cout << "Enter challenge day: ";
    std::cin >> day;
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
            
        default: NULL;
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
