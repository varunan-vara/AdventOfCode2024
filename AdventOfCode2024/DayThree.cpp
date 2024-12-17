#include "AoCFunctions.h"
#include <iostream>

void dayThree() {
	std::cout << "Enter puzzle input: ";
	vector<string> input = contentsOfInput();

	int multiplications = 0;

	// Go through each of the input contents
	for (string line : input) {
		for (int i = 0; i < line.size(); i++) {
			string numOne, numTwo;
			// Check if the character is m, if not, we can skip. Similarly, do u, l, and (
			// Given boolean logic, condition is broken immediately if one of them are not satisfied
			if (line[i] == 'm' && line[i+1] == 'u' && line[i+2] == 'l' && line[i+3] == '(') {
				// If i+5 -> i+7 aren't a comma, can skip.
				for (int j = i + 5; j < i + 8 && j < line.size(); j++) {
					if (line[j] == ',') {
						numOne = line.substr(i + 4, j - 4 - i);
						// If j+2 -> j+4 aren't a comma, can skip.
						int k;
						for (k = j + 2; k < j + 5 && k < line.size(); k++) {
							if (line[k] == ')') {
								numTwo = line.substr(j + 1, k - j - 1);
								multiplications += stoi(numOne) * stoi(numTwo);
								i = k - 1;
								break;
							}
						}
						if (k < j + 5) { break; }
					}
				}
			}
		}
	}
	std::cout << "Part 1: " << multiplications << std::endl;


	multiplications = 0;

	// Go through each of the input contents
	bool isEnabled = true;
	for (string line : input) {
		for (int i = 0; i < line.size(); i++) {
			// Check for do
			if (!isEnabled && line[i] == 'd' && line[i + 1] == 'o' && line[i + 2] == '(' && line[i + 3] == ')') {
				isEnabled = true;
				i = i + 3;
			}
			if (isEnabled && line[i] == 'd' && line[i + 1] == 'o' && line[i+2] == 'n' && line[i+3] == 39 && line[i+4] == 't' && line[i + 5] == '(' && line[i + 6] == ')') {
				isEnabled = false;
				i = i + 6;
			}

			if (!isEnabled)
				continue;
			string numOne, numTwo;
			// Check if the character is m, if not, we can skip. Similarly, do u, l, and (
			// Given boolean logic, condition is broken immediately if one of them are not satisfied
			if (line[i] == 'm' && line[i + 1] == 'u' && line[i + 2] == 'l' && line[i + 3] == '(') {
				// If i+5 -> i+7 aren't a comma, can skip.
				for (int j = i + 5; j < i + 8 && j < line.size(); j++) {
					if (line[j] == ',') {
						numOne = line.substr(i + 4, j - 4 - i);
						// If j+2 -> j+4 aren't a comma, can skip.
						int k;
						for (k = j + 2; k < j + 5 && k < line.size(); k++) {
							if (line[k] == ')') {
								numTwo = line.substr(j + 1, k - j - 1);
								multiplications += stoi(numOne) * stoi(numTwo);
								i = k - 1;
								break;
							}
						}
						if (k < j + 5) { break; }
					}
				}
			}
		}
	}
	std::cout << "Part 2: " << multiplications << std::endl;
}
