#include "AoCFunctions.h"
#include <algorithm>
#include <iostream>

void dayOne() {
	// Returns an array of strings representing the lines of the input file
	vector<string> input = contentsOfInput();
	vector<int> col1, col2;
	for (int i = 0; i < input.size(); i++) {
		vector<int> line = splitStringIntoInt(input[i], "   ");
		col1.push_back(line[0]), col2.push_back(line[1]);
	}

	// Sort to make checking list easier
	std::sort(col1.begin(), col1.end());
	std::sort(col2.begin(), col2.end());

	// Part One: Iterate over each index, and compare numbers
	int output1 = 0, output2 = 0, temp;
	for (int j = 0; j < col1.size(); j++) {
		temp = col1[j] > col2[j] ? col1[j] - col2[j] : col2[j] - col1[j];
		output1 += temp;
	}

	std::cout << "Part One: " << output1 << std::endl;

	// Part Two: Iterate over Column 1, increment Column 2 until all equivalent values are accounted for
	int col2Counter = 0;
	for (int k = 0; k < col1.size(); k++) {
		if (k > 0 && col1[k] == col1[k - 1])
			continue;
		temp = 0;
		while (col2Counter < col2.size() && col2[col2Counter] < col1[k])
			col2Counter++;
		while (col2Counter < col2.size() && col2[col2Counter] == col1[k])
            temp++; col2Counter ++;
		output2 += temp * col1[k];
	}
	std::cout << "Part Two: " << output2 << std::endl;

}
