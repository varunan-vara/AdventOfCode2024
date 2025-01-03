#include "AoCFunctions.h"
#include <iostream>
#include <string>
#include <set>

vector<vector<int>> removeDuplicates(vector<vector<int>> inputList) {
    std::set<vector<int>> tempSet;
    std::vector<vector<int>> returnVector;
    for (int i = 0; i < inputList.size(); i++) {
        if (inputList[i].size() == 0) {continue;}
        tempSet.insert(inputList[i]);
    }
    returnVector.assign(tempSet.begin(), tempSet.end());
    return returnVector;
}

vector<vector<int>> recurseClimbTrail(int xPos, int yPos, vector<vector<int>> topoMap) {
    int a = topoMap[xPos][yPos];
    vector<vector<int>> returnCoordsList, upList, rightList, leftList, downList;

    if (a == 9) {
        return vector<vector<int>>{{xPos, yPos}};
    }    
    
    rightList = (yPos < topoMap[xPos].size() - 1 && topoMap[xPos][yPos + 1] == a + 1) ? recurseClimbTrail(xPos, yPos + 1, topoMap) : vector<vector<int>>{};
    downList = (xPos < topoMap.size() - 1 && topoMap[xPos + 1][yPos] == a + 1) ? recurseClimbTrail(xPos + 1, yPos, topoMap) : vector<vector<int>>{};
    leftList = (yPos > 0 && topoMap[xPos][yPos - 1] == a + 1) ? recurseClimbTrail(xPos, yPos - 1, topoMap) : vector<vector<int>>{};
    upList = (xPos > 0 && topoMap[xPos - 1][yPos] == a + 1) ? recurseClimbTrail(xPos - 1, yPos, topoMap) : vector<vector<int>>{};

    returnCoordsList.reserve(rightList.size() + downList.size() + leftList.size() + upList.size());
    returnCoordsList.insert(returnCoordsList.end(), rightList.begin(), rightList.end());
    returnCoordsList.insert(returnCoordsList.end(), downList.begin(), downList.end());
    returnCoordsList.insert(returnCoordsList.end(), leftList.begin(), leftList.end());
    returnCoordsList.insert(returnCoordsList.end(), upList.begin(), upList.end());

    return removeDuplicates(returnCoordsList);

}

int findTrailRating(int xPos, int yPos, vector<vector<int>> topoMap) {
    std::cout << xPos << ", " << yPos << std::endl;
    int a = topoMap[xPos][yPos];
    if (a == 9) {
        return 1;
    }

    int rightRating = (yPos < topoMap[xPos].size() - 1 && topoMap[xPos][yPos + 1] == a + 1) ? findTrailRating(xPos, yPos + 1, topoMap) : 0;
    int downRating = (xPos < topoMap.size() - 1 && topoMap[xPos + 1][yPos] == a + 1) ? findTrailRating(xPos + 1, yPos, topoMap) : 0;
    int leftRating = (yPos > 0 && topoMap[xPos][yPos - 1] == a + 1) ? findTrailRating(xPos, yPos - 1, topoMap) : 0;
    int upRating = (xPos > 0 && topoMap[xPos - 1][yPos] == a + 1) ? findTrailRating(xPos - 1, yPos, topoMap) : 0;

    return rightRating + downRating + leftRating + upRating;
}

void dayTen() {
    vector<string> pInput = contentsOfInput();
    vector<vector<int>> tMap;
    vector<int> temp;

    for (string line : pInput) {
        temp.clear();
        for (char c : line) {
            temp.push_back(atoi(&c));
        }
        tMap.push_back(temp);
    }

    vector<vector<int>> tempReturnList;
    int outputOne = 0;

    for (int j = 0; j < tMap.size(); j++) {
        for (int k = 0; k < tMap[j].size(); k++) {
                std::cout << "coord: " << j << ", " << k << std::endl;
            if (tMap[j][k] == 0) {
                tempReturnList = recurseClimbTrail(j,k,tMap);
                outputOne += tempReturnList.size();
                std::cout << tempReturnList.size() << std::endl;
                for (vector<int> a : tempReturnList) {
                    std::cout << a[0] << ", " << a[1] << std::endl;
                }
                tempReturnList.clear();
            }
        }
    } 

    int outputTwo = 0;

    for (int j = 0; j < tMap.size(); j++) {
        for (int k = 0; k < tMap[j].size(); k++) {
                std::cout << "coord: " << j << ", " << k << std::endl;
            if (tMap[j][k] == 0) {
                outputTwo += findTrailRating(j,k,tMap);
            }
        }
    } 

    std::cout << "Part 1: " << outputOne << std::endl; 
    std::cout << "Part 2: " << outputTwo << std::endl; 
}