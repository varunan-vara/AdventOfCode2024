#include "AoCFunctions.h"
#include <iostream>
#include <sstream>

int FLOOR_WIDTH = 101;
int FLOOR_HEIGHT = 103;
int testNum = 5001;

std::vector<std::vector<std::vector<int>>> robotMaps(testNum,std::vector<std::vector<int>> (FLOOR_HEIGHT, std::vector<int>(FLOOR_WIDTH,0))); // Call value using y, x

void printFloorPlan(std::vector<std::vector<int>> floorPlan) {
    // For testing
    for (std::vector<int> row : floorPlan) {
        for (int pos : row) {
            std::cout <<  (pos != 0 ? "■" : " ");
        }
        std::cout << std::endl;
    }
}

int calculateSafetyFactor (std::vector<std::vector<int>> floorPlan) {
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

std::pair<int,int> simulate (int xPos, int yPos, int xVel, int yVel, int seconds) {
    // Simulate 100 seconds
    for (int i = 0; i < seconds; i++) {
        xPos += xVel;
        yPos += yVel;
        if (xPos >= FLOOR_WIDTH) {
            xPos -= FLOOR_WIDTH;
        } else if (xPos < 0) {
            xPos += FLOOR_WIDTH;
        }

        if (yPos >= FLOOR_HEIGHT) {
            yPos -= FLOOR_HEIGHT;
        } else if (yPos < 0) {
            yPos += FLOOR_HEIGHT;
        }
    }
    return std::pair<int,int>{xPos, yPos};
}

void dayFourteen() {
    vector<string> input = contentsOfInput();
    string pos, vel;
    int xPos, yPos, xVel, yVel;
    for (string line : input) {
        pos = line.substr(0,line.find(' '));
        vel = line.substr(line.find(' ') + 1);
        xPos = stoi(pos.substr(2,pos.find(',')));
        yPos = stoi(pos.substr(pos.find(',') + 1));
        xVel = stoi(vel.substr(2,vel.find(',')));
        yVel = stoi(vel.substr(vel.find(',') + 1));
        std::pair<int,int> simulation;
        for (int i = 0; i < robotMaps.size(); i ++) {
            simulation = simulate(xPos, yPos, xVel, yVel, i);
            robotMaps[i][simulation.second][simulation.first] += 1;
        }

    }
    std::cout << "Part One: " << calculateSafetyFactor(robotMaps[100]) << std::endl;

    for (int i = 0; i < robotMaps.size(); i++) {
        bool isBreak = false;
        for (int y = 0; y < robotMaps[i].size(); y++) {
            int counter = 0;
            int patternRec = 5;
            for (int x = 0; x < robotMaps[i][y].size(); x++) {
                if (robotMaps[i][y][x] != 0) {
                    counter ++;
                } else {
                    counter = 0;
                }
                if (counter >= patternRec ) {
                    std::cout << "......... Seconds: " << i << "........." << std::endl;
                    printFloorPlan(robotMaps[i]);
                    isBreak = true;
                    break;
                }
            }
            if (isBreak) {break; }
        }
    }
}