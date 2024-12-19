#include "AoCFunctions.h"
#include <iostream>
#include <string>

void dayNine() {
    // Used long long just in case
    std::cout << "This program only works if there is a blank space somewhere on the disk\n";
    vector<string> pInput = contentsOfInput();
    string input = pInput[0];
    // Create disk
    vector<int> disk; int id = 0;
    for (int c = 0; c < input.size(); NULL) { // Null character
        for (int i = 0; i < ((char) input[c]) - 48; i++) {
            disk.push_back(id);
        }
        id++, c++;
        for (int j = 0; j < ((char) input[c]) - 48; j++) {
            disk.push_back(-1);
        }
        c++;
    }
    vector<int> diskTwo = disk;

    // Create two markers for Part One
    int markerOne = 0;
    int markerTwo = disk.size() - 1;
    while (true) {
        // Set markerTwo to the next non blank disk space
        while (disk[markerTwo] == -1)  { 
            markerTwo--; 
        }
        
        // Set markerOne to the next blank disk space
        while (disk[markerOne] != -1) {
            markerOne++;
        }

        if (markerOne >= markerTwo) {break;}
        
        disk[markerOne] = disk[markerTwo];
        disk[markerTwo] = -1;
        markerOne++, markerTwo--;
    }

    // Create two markers for Part Two
    // markerOne = 0;
    // markerOne = 0;
    // markerTwo = disk.size() - 1;
    // int tempLen, tempSpace, tempID = -1, z;


    long long outputOne = 0;
    for (int x = 1;  x < disk.size(); x++) {
        if (disk[x] == -1) {continue;}
        outputOne += x * disk[x];
    }

    long long outputTwo = 0;
    for (int x = 1;  x < diskTwo.size(); x++) {
        if (diskTwo[x] == -1) {continue;}
        outputTwo += x * diskTwo[x];
    }

    std::cout << "Part 1: " << outputOne << std::endl;
    std::cout << "Part 2: " << outputTwo << std::endl;
    for (int x : diskTwo) {
        std::cout << x << ", ";
    }
    std::cout << "\n";
}