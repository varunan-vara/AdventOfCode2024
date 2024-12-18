#pragma once
#ifndef ADVENT_OF_CODE_FUNCTIONS
#define ADVENT_OF_CODE_FUNCTIONS

#include <string>
#include <vector>

using std::vector;
using std::string;

// int sizeOfFile(string fileName);

std::vector<string> contentsOfInput();

std::vector<int> splitStringIntoInt(string input, string delimiter);
std::vector<long long> splitStringIntoLongLong(string input, string delimiter);

void testContentsOfFile(string fileName);

#endif // ADVENT_OF_CODE_FUNCTIONS
