#include "AoCFunctions.h"
#include <iostream>
#include <map>

string coordStr(int x, int y) {
    return std::to_string(x) + "-" + std::to_string(y);
}


void dayTwelve() {
    vector<string> input = contentsOfInput();
    
    vector<vector<char>> regionMap;
    vector<char> temp;

    for (string line : input) {
        temp.clear();
        for (char c : line) {
            temp.push_back(c);
        }
        regionMap.push_back(temp);
    }

    // Iterate over each coordinate, assign a perimeter value (if the area to the sides are different)
    vector<vector<int>> perimeterMap;
    for (int i = 0; i < regionMap.size(); i++) {
        vector<int> tempLine;
        for (int j = 0; j < regionMap[i].size(); j++) {
            int tempPerimeter = 0;
            tempPerimeter += (bool) (i == 0 || regionMap[i-1][j] != regionMap[i][j]);
            tempPerimeter += (bool) (j == 0 || regionMap[i][j-1] != regionMap[i][j]);
            tempPerimeter += (bool) (i == regionMap.size() - 1 || regionMap[i+1][j] != regionMap[i][j]);
            tempPerimeter += (bool) (j == regionMap[i].size() - 1 || regionMap[i][j+1] != regionMap[i][j]);
            tempLine.push_back(tempPerimeter);
        }
        perimeterMap.push_back(tempLine);
    }

    std::map<string, int> regionAreas;
    std::map<string, int> regionPerimeters;
    std::map<string, int> regionSides;
    std::map<string, char> regionChar;
    std::map<string, string> coordinateRegionAssignments;

    // Iterate over each coordinate, and check with coordinates to the upper or left side of the value
    // If ONE of these values is the same as the current, then we add to that coordinates region
    // If NONE of these values is the same as the current, we create a new region
    // If BOTH of these values is the same as the current, we merge the two regions.

    for (int i = 0; i < regionMap.size(); i++) {
        for (int j = 0; j < regionMap[i].size(); j++) {
            // Coord: i-j
            bool up = (i > 0 && regionMap[i-1][j] == regionMap[i][j]);
            bool left = (j > 0 && regionMap[i][j-1] == regionMap[i][j]);

            if (!up && !left) {
                // Create
                regionAreas.insert({coordStr(i,j), 1});
                regionPerimeters.insert({coordStr(i,j), perimeterMap[i][j]});
                // Sides is equal to the perimeter at this point
                regionSides.insert({coordStr(i,j), perimeterMap[i][j]});
                coordinateRegionAssignments.insert({coordStr(i,j), coordStr(i,j)});
                regionChar.insert({coordStr(i,j), regionMap[i][j]});
                continue;
            }
            else if (up && left) {
                // Merge
                if (coordinateRegionAssignments[coordStr(i-1,j)] != coordinateRegionAssignments[coordStr(i,j-1)]) {
                    regionAreas[coordinateRegionAssignments[coordStr(i,j-1)]] += regionAreas[coordinateRegionAssignments[coordStr(i-1,j)]];
                    regionAreas.erase(coordinateRegionAssignments[coordStr(i-1,j)]);
                    regionPerimeters[coordinateRegionAssignments[coordStr(i,j-1)]] += regionPerimeters[coordinateRegionAssignments[coordStr(i-1,j)]];
                    regionPerimeters.erase(coordinateRegionAssignments[coordStr(i-1,j)]);
                    regionSides[coordinateRegionAssignments[coordStr(i,j-1)]] += regionSides[coordinateRegionAssignments[coordStr(i-1,j)]];
                    regionSides.erase(coordinateRegionAssignments[coordStr(i-1,j)]);
                    string toDelete = coordinateRegionAssignments[coordStr(i-1,j)];
                    for (auto k : coordinateRegionAssignments) {
                        if (k.second == toDelete) {
                            coordinateRegionAssignments[k.first] = coordinateRegionAssignments[coordStr(i,j-1)];
                        }
                    }
                }
            }
            
            // When merging, left is given priority, so left check, then up check...
            if (left) {
                regionAreas[coordinateRegionAssignments[coordStr(i,j-1)]] += 1;
                regionPerimeters[coordinateRegionAssignments[coordStr(i,j-1)]] += perimeterMap[i][j];
                coordinateRegionAssignments.insert({coordStr(i,j), coordinateRegionAssignments[coordStr(i,j-1)]});
            }
            else if (up) {
                regionAreas[coordinateRegionAssignments[coordStr(i-1,j)]] += 1;
                regionPerimeters[coordinateRegionAssignments[coordStr(i-1,j)]] += perimeterMap[i][j];
                coordinateRegionAssignments.insert({coordStr(i,j), coordinateRegionAssignments[coordStr(i-1,j)]});
            }

            int tSides = perimeterMap[i][j];
            // For region sides, we have to check if left/right perimeters were already accounted for up, and up/down on the left
            if (left) {
                // Up
                if (i == 0 || (regionMap[i][j] != regionMap[i-1][j] && regionMap[i][j-1] != regionMap[i-1][j-1])) {
                    tSides -= 1;
                }
                // Down
                if (i == regionMap.size() - 1 || (regionMap[i][j] != regionMap[i+1][j] && regionMap[i][j-1] != regionMap[i+1][j-1])) {
                    tSides -= 1;
                }
            }
            if (up) {
                // Left
                if (j == 0 || (regionMap[i][j] != regionMap[i][j-1] && regionMap[i-1][j] != regionMap[i-1][j-1])) {
                    tSides -= 1;
                }
                // Right
                if (j == regionMap[i].size() - 1 || (regionMap[i][j] != regionMap[i][j+1] && regionMap[i-1][j] != regionMap[i-1][j+1])) {
                    tSides -= 1;
                }
            }
            regionSides[coordinateRegionAssignments[coordStr(i,j)]] += tSides;
        }
    }

    // Price:
    int price = 0;
    int bulkDiscountPrice = 0;
    for (auto k : regionAreas) {
        price += regionAreas[k.first] * regionPerimeters[k.first];
        bulkDiscountPrice += regionAreas[k.first] * regionSides[k.first];
        // std::cout << regionChar[k.first] << " - Area: " << regionAreas[k.first] << ", Perimeter: " << regionPerimeters[k.first] << ", Sides: " << regionSides[k.first] << std::endl;
    }

    std::cout << "Part 1: " << price << std::endl;
    std::cout << "Part 2: " << bulkDiscountPrice << std::endl;
}