#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using std::string;

// Used by all solutions to get the basic outputs of the puzzle input
std::vector<string> contentsOfFile(string fileName) {

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

