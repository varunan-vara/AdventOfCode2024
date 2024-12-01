#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using std::string;

// Used by all solutions to get the basic outputs of the puzzle input
std::vector<string> contentsOfFile(string fileName) {
	fileName = "../AdventOfCode2024Sol/" + fileName;

	std::vector<string> returnObj;

	string temp;
	std::ifstream readFile(fileName);
	while (std::getline(readFile, temp)) {
		returnObj.push_back(temp);
	}

	return returnObj;
}

void testContentsOfFile(string fileName) {
	std::vector<string> result = contentsOfFile(fileName);
	for (int i = 0; i < result.size(); i++) {
		std::cout << i << " : " << result[i] << std::endl;
	}
}

// Copied from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
std::vector<int> splitStringIntoInt(string input, string delimiter) {
	std::vector<int> output;
	size_t pos = 0;
	std::string i;
	while ((pos = input.find(delimiter)) != std::string::npos) {
		i = input.substr(0, pos);
		output.push_back(stoi(i));
		input.erase(0, pos + delimiter.length());
	}
	output.push_back(stoi(input));
	return output;
}
