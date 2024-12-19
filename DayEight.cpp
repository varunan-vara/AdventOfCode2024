#include "AoCFunctions.h"
#include <iostream>
#include <map>
#include <math.h>

void dayEight() {
    vector<string> input = contentsOfInput();
    std::map<char, vector<vector<int>>> coordinates;

    // Length and width of the coordinates system
    int xLength = input.size(), yLength = input[0].size();

    int x, y;
    // Index each coordinate in map
    for (x = 0; x < xLength; x++) {
        for (y = 0; y < yLength; y++) {
            if (input[x][y] == '.') {
                continue;
            }

            coordinates[input[x][y]].push_back(vector<int>{x,y});
        }
    }

    // Create an empty coordinates system, assign 0, change to 1 if antinode exists
    vector<vector<int>> antinodes(input.size(), std::vector<int>(input[0].size()));
    vector<vector<int>> antinodesTwo(input.size(), std::vector<int>(input[0].size()));


    // Iterate over each antenna pair, check both sides of the antennas for antinodes
    std::map<char, vector<vector<int>>>::iterator coordinatesIterator = coordinates.begin();
    int xDist, yDist, xDisp, yDisp, tempX, tempY, antinodeOneX, antinodeOneY, antinodeTwoX, antinodeTwoY, i, j;
    

    while (coordinatesIterator != coordinates.end()) {
        std::cout << "Checking: " << coordinatesIterator->first << std::endl;
        vector<vector<int>> coords = coordinatesIterator->second;
        for (i = 0; i < coords.size(); i++) {
            for (j = i + 1; j < coords.size(); j++) {
                xDist = abs(coords[i][0] - coords[j][0]);
                yDist = abs(coords[i][1] - coords[j][1]);

                // Find antinode located closer to 'i'
                antinodeOneX = (coords[i][0] > coords[j][0]) ? coords[i][0] + xDist : coords[i][0] - xDist;
                antinodeOneY = (coords[i][1] > coords[j][1]) ? coords[i][1] + yDist : coords[i][1] - yDist;

                if (antinodeOneX < xLength && antinodeOneX >= 0 && antinodeOneY < yLength && antinodeOneY >= 0) {
                    antinodes[antinodeOneX][antinodeOneY] = 1;
                }

                // Find antinode located closer to 'j'
                antinodeTwoX = (coords[j][0] > coords[i][0]) ? coords[j][0] + xDist : coords[j][0] - xDist;
                antinodeTwoY = (coords[j][1] > coords[i][1]) ? coords[j][1] + yDist : coords[j][1] - yDist;

                if (antinodeTwoX < xLength && antinodeTwoX >= 0 && antinodeTwoY < yLength && antinodeTwoY >= 0) {
                    antinodes[antinodeTwoX][antinodeTwoY] = 1;
                }

                // For Part 2, just use the first antinode and while loop, use directionality
                xDisp = antinodeOneX - coords[i][0];
                yDisp = antinodeOneY - coords[i][1];

                for (tempX = coords[i][0], tempY = coords[i][1]; tempX < xLength && tempX >= 0 && tempY < yLength && tempY >= 0; tempX = tempX + xDisp, tempY = tempY + yDisp) {
                    antinodesTwo[tempX][tempY] = 1;
                }

                for (tempX = coords[i][0], tempY = coords[i][1]; tempX < xLength && tempX >= 0 && tempY < yLength && tempY >= 0; tempX = tempX - xDisp, tempY = tempY - yDisp) {
                    antinodesTwo[tempX][tempY] = 1;
                }

            }
        }
        coordinatesIterator++;
    }

    int outputOne = 0;
    for (vector<int> row : antinodes) {
        for ( int item : row) {
            outputOne += item;
        }
    }

    int outputTwo = 0;
    for (vector<int> row : antinodesTwo) {
        for ( int item : row) {
            outputTwo += item;
        }
    }

    std::cout << "Part 1: " << outputOne << std::endl;
    std::cout << "Part 2: " << outputTwo << std::endl;
}