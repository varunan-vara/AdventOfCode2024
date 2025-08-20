#include "AoCFunctions.h"
#include <iostream>
#include <sstream>

// Returns 1 if the unit cannot be moved into, Returns 0 if ithe unit can be moved into.
vector<int> moveRecursePartOne (vector<vector<char>> * floorPlan, char movement, int x, int y) {
    if ((*floorPlan)[y][x] == '.') {
        return vector<int>{0};
    } else if ((*floorPlan)[y][x] == '#') {
        return vector<int>{1};
    }
    int nextX = x, nextY = y;
    switch (movement) {
        case '<':
            nextX --;
            break;
        case '>':
            nextX ++;
            break;
        case '^':
            nextY --;
            break;
        case 'v':
            nextY ++;
            break;
    }
    vector<int> result = moveRecursePartOne(floorPlan, movement, nextX, nextY);
    if (result[0] == 0) {
        (*floorPlan)[nextY][nextX] = (*floorPlan)[y][x];
        (*floorPlan)[y][x] = '.';
    }
    return vector<int>{result[0], nextX, nextY};
}
// Returns 1 if the unit cannot be moved into, Returns 0 if ithe unit can be moved into.
vector<int> moveRecursePartTwo (vector<vector<char>> * floorPlan, char movement, int x, int y, bool checkOnly) {
    // If checkOnly is enabled do not move any peices.
    // Possible values: '#' . [ ] @
    if ((*floorPlan)[y][x] == '.') {
        return vector<int>{0};
    } else if ((*floorPlan)[y][x] == '#') {
        return vector<int>{1};
    }
    // Moving left or right - no change
    // Moving up and down, must check and do the units -> start another recursion
    int secondX = x, nextX = x, nextY = y;
    bool isVertical = false;
    switch (movement) {
        case '<':
            nextX --;
            break;
        case '>':
            nextX ++;
            break;
        case '^':
            nextY --;
            isVertical = true;
            break;
        case 'v':
            nextY ++;
            isVertical = true;
            break;
    }
    vector<int> result1 = moveRecursePartTwo(floorPlan, movement, nextX, nextY, true);
    vector<int> result2;
    if (isVertical) {
        if ((*floorPlan)[y][x] == '[') {
            secondX ++;
        } else if ((*floorPlan)[y][x] == ']') {
            secondX --;
        }
        result2 = moveRecursePartTwo(floorPlan, movement, secondX, nextY, true);
    } else {
        result2 = result1;
    }

    if (result1[0] == 0 && result2[0] == 0) {
        if (!checkOnly) {
            result1 = moveRecursePartTwo(floorPlan, movement, nextX, nextY, checkOnly);
            (*floorPlan)[nextY][nextX] = (*floorPlan)[y][x];
            (*floorPlan)[y][x] = '.';
            if (secondX != x) {
                result2 = moveRecursePartTwo(floorPlan, movement, secondX, nextY, checkOnly);
                (*floorPlan)[nextY][secondX] = (*floorPlan)[y][secondX];
                (*floorPlan)[y][secondX] = '.';
            }
        }
        return vector<int>{0, nextX, nextY};
    } else {
        return vector<int>{1};
    }

}

int getGPSForBoxes (vector<vector<char>> floorPlan) {
    int totalGPSScore = 0;
    for (int y = 0; y < floorPlan.size(); y++) {
        for (int x = 0; x < floorPlan[y].size(); x++) {
            if (floorPlan[y][x] == 'O') {
                totalGPSScore += ((100 * y) + x);
            }
            if (floorPlan[y][x] == '[') {
                totalGPSScore += ((100 * y) + x);
            }
        }
    }
    return totalGPSScore;
}

void printMap (vector<vector<char>> floorPlan) {
    for (int y = 0; y < floorPlan.size(); y++) {
        for (int x = 0; x < floorPlan[y].size(); x++) {
            std::cout << floorPlan[y][x];
        }
        std::cout << std::endl;
    }
}

void dayFifteen() {
    vector<string> input = contentsOfInput();
    vector<char> movementList;
    vector<vector<char>> floorPlan; // # means wall, O means box, . means air
    vector<vector<char>> floorPlanPartTwo;

    int xRobot = 0;
    int yRobot = 0;
    int x2Robot = 0;
    int y2Robot = 0;
    int y = 0;
    for (NULL; y < input.size(); y++) {
        if (input[y].size() <= 1) {
            y++;
            break;
        }
        floorPlan.push_back(vector<char>());
        floorPlanPartTwo.push_back(vector<char>());
        for (int x = 0; x < input[y].size(); x++) {
            // Part One
            if (input[y][x] == '@') {
                xRobot = x, yRobot = y;
                x2Robot = x * 2;
                y2Robot = y;
            }
            floorPlan[y].push_back(input[y][x]);
            // Part Two
            if (input[y][x] == '#') {
                floorPlanPartTwo[y].push_back('#');
                floorPlanPartTwo[y].push_back('#');
            } else if (input[y][x] == 'O') {
                floorPlanPartTwo[y].push_back('[');
                floorPlanPartTwo[y].push_back(']');
            } else if (input[y][x] == '.') {
                floorPlanPartTwo[y].push_back('.');
                floorPlanPartTwo[y].push_back('.');
            } else if (input[y][x] == '@') {
                floorPlanPartTwo[y].push_back('@');
                floorPlanPartTwo[y].push_back('.');
            }
        }
    }
    for (NULL; y < input.size(); y++) {
        for (char c : input[y]) {
            movementList.push_back(c);
        }
    }

    // printMap (floorPlan);
    vector<int> result;
    for (char movement: movementList) {
        result = moveRecursePartOne(&floorPlan, movement, xRobot, yRobot);
        // printMap(floorPlan);
        std::cout << std::endl;
        if (result[0] == 0) {
            xRobot = result[1], yRobot = result[2];
        }
    }

    int gpsCode = getGPSForBoxes(floorPlan);

    std::cout << "Part One: " << gpsCode << std::endl;

    printMap(floorPlanPartTwo);

    for (char movement: movementList) {
        result = moveRecursePartTwo(&floorPlanPartTwo, movement, x2Robot, y2Robot, false);
        printMap(floorPlanPartTwo);
        std::cout << std::endl;
        if (result[0] == 0) {
            x2Robot = result[1], y2Robot = result[2];
        }
    }

    gpsCode = getGPSForBoxes(floorPlanPartTwo);

    std::cout << "Part Two: " << gpsCode << std::endl;

}