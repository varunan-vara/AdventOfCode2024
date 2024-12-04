#include <string>
#include <vector>
#include <iostream>
using std::string;

/*
Param: fileName (string)

Returns the contents of file as array of strings, each of which is a seperate line. Path is determined from 'AdventOfCode2024Sol' folder
*/
std::vector<string> contentsOfInput() {
	std::vector<string> returnObj;
	string temp;

	std::cout << "Enter puzzle input: ";
	std::cin >> temp;
	while (temp != ".") {
		std::cout << "----" << temp << std::endl;
		returnObj.push_back(temp);
		std::cin >> temp;
	}

	return returnObj;
}

// Copied from https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
/*
Param: input (string), delimiter (string)\

Returns an array of ints from a string containing multiple numbers seperated by the delimiter
*/
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
