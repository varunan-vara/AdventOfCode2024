#include "AoCFunctions.h"
#include <iostream>

int FLOOR_WIDTH = 101;
int FLOOR_HEIGHT = 103;
int testNum = 10000;

class Robot {
    public:
        int xPosition;
        int yPosition;
        int xVelocity;
        int yVelocity;

        Robot (int xPos, int yPos, int xVel, int yVel) {
            xPosition = xPos, yPosition = yPos, xVelocity =  xVel, yVelocity = yVel;
        }
        
        void move () {
            // Move Robot
            xPosition += xVelocity;
            yPosition += yVelocity;
            // Center robot in plane again as per challenge rules
            if (xPosition < 0) {
                xPosition += FLOOR_WIDTH;
            }
            if (yPosition < 0) {
                yPosition += FLOOR_HEIGHT;
            }
            xPosition = xPosition % FLOOR_WIDTH;
            yPosition = yPosition% FLOOR_HEIGHT;
        }
};

std::vector<std::vector<int>> convertRobotsToFloorPlan (std::vector<Robot> list) {
    std::vector<std::vector<int>> floorPlan (FLOOR_HEIGHT,std::vector<int>(FLOOR_WIDTH,0));
    for (Robot r : list) {
        floorPlan[r.yPosition][r.xPosition] += 1;
    }
    return floorPlan;
}

void printRobotMap (std::vector<Robot> list, int minPerRow) {
    std::vector<std::vector<int>> floorPlan = convertRobotsToFloorPlan(list);

    int counter;
    int foundPattern = false;
    for (int y = 0; y < floorPlan.size(); y++) {
        counter = 0;
        for (int x = 0; x < floorPlan[y].size(); x++) {
            if (counter >= minPerRow) {
                foundPattern = true;
                break;
            }
            if (floorPlan[y][x] == 0) {
                counter = 0;
            } else {
                counter ++;
            }
        }
        if (foundPattern) {break;}
    }

    if (!foundPattern) {return;}

    for (std::vector<int> row : floorPlan) {
        for (int value : row) {
            std::cout << (char) ((value != 0) ? '0' + value : '.');
        }
        std::cout << std::endl;
    }
}

int safetyFactor (std::vector<Robot> list) {
    std::vector<std::vector<int>> floorPlan = convertRobotsToFloorPlan(list);
    int quadrantOne = 0, quandrantTwo = 0, quadrantThree = 0, quadrantFour = 0;
    for (int y = 0; y < floorPlan.size(); y++) {
        for (int x = 0; x < floorPlan[y].size(); x++) {
            if (floorPlan[y][x] == 0) {continue;}
            if (y < FLOOR_HEIGHT / 2 && x < FLOOR_WIDTH / 2) {
                quadrantOne += floorPlan[y][x];
            } else if (y > FLOOR_HEIGHT / 2 && x < FLOOR_WIDTH / 2) {
                quandrantTwo += floorPlan[y][x];
            } else if (y < FLOOR_HEIGHT / 2 && x > FLOOR_WIDTH / 2) {
                quadrantThree += floorPlan[y][x];
            } else if (y > FLOOR_HEIGHT / 2 && x > FLOOR_WIDTH / 2) {
                quadrantFour += floorPlan[y][x];
            }
        }
    }
    return quadrantOne * quandrantTwo * quadrantThree * quadrantFour;
}

std::vector<Robot> robotList;
std::vector<Robot> robotListPartTwo;

void dayFourteen() {
    vector<string> input = contentsOfInput();
    string pos, vel;
    int xPos, yPos, xVel, yVel;
    for (string line : input) {
        pos = line.substr(0,line.find(' '));
        vel = line.substr(line.find(' ') + 1);
        xPos = stoi(pos.substr(2,pos.find(',') - 2));
        yPos = stoi(pos.substr(pos.find(',') + 1));
        xVel = stoi(vel.substr(2,vel.find(',') - 2));
        yVel = stoi(vel.substr(vel.find(',') + 1));
        robotList.push_back(Robot(xPos, yPos, xVel, yVel));
        robotListPartTwo.push_back(Robot(xPos, yPos, xVel, yVel));
    }

    std::cout << "Time: 0 seconds" << std::endl;
    printRobotMap(robotList, 0);
    for (int second = 0; second < 100; second++) {
        for (int i = 0; i < robotList.size(); i++) {
            robotList[i].move();
        }
    }

    std::cout << "Part One - Safety Score: " <<  safetyFactor(robotList) << std::endl;

    std::cout << "Part Two: " << std::endl;

    for (int z = 0; z < testNum; z ++) {
        for (int i = 0; i < robotListPartTwo.size(); i++) {
            robotListPartTwo[i].move();
        }
        std::cout << "Seconds: " << z + 1 << std::endl;
        printRobotMap(robotListPartTwo, 8);
    }

}