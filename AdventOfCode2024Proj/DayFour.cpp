#include "../AdventOfCode2024Proj/AoCFunctions.h"
#include <iostream>

void dayFour() {
	vector<string> input = contentsOfFile("DayFour.txt");
	std::cout << input.size() << std::endl;
	
	int numXMAS = 0;

	for (int x = 0; x < input.size(); x++) 
		for (int y = 0; y < input[x].size(); y++) {
			if (input[x][y] == 'X') {
				std::cout << 'HI' << std::endl;
				// Top
				if (x > 2 && input[x - 1][y] == 'M' && input[x - 2][y] == 'A' && input[x - 3][y] == 'S')
					numXMAS++;
				// Bottom
				if (x < input.size() - 3 && input[x + 1][y] == 'M' && input[x + 2][y] == 'A' && input[x + 3][y] == 'S')
					numXMAS++;
				// Left
				if (y > 2 && input[x][y - 1] == 'M' && input[x][y - 2] == 'A' && input[x][y - 3] == 'S')
					numXMAS++;
				// Right
				if (y < input[x].size() - 3 && input[x][y + 1] == 'M' && input[x][y + 2] == 'A' && input[x][y + 3] == 'S')
					numXMAS++;
				// Top Left
				if (x > 2 && y > 2 && input[x - 1][y - 1] == 'M' && input[x - 2][y - 2] == 'A' && input[x - 3][y - 3] == 'S')
					numXMAS++;
				// Top Right
				if (x > 2 && y < input[x].size() - 3 && input[x - 1][y + 1] == 'M' && input[x - 2][y + 2] == 'A' && input[x - 3][y + 3] == 'S')
					numXMAS++;
				// Bottom Left
				if (x < input.size() - 3 && y > 2 && input[x + 1][y - 1] == 'M' && input[x + 2][y - 2] == 'A' && input[x + 3][y - 3] == 'S')
					numXMAS++;
				// Top Left
				if (x < input.size() - 3 && y < input[x].size() - 3 && input[x + 1][y + 1] == 'M' && input[x + 2][y + 2] == 'A' && input[x + 3][y + 3] == 'S')
					numXMAS++;
			}
		}

	std::cout << "Part 1: " << numXMAS << std::endl;
}