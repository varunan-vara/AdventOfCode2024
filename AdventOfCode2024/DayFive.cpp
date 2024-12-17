#include "AoCFunctions.h"
#include <iostream>
#include <algorithm>


void dayFive() {
	// Seperate input for rules and page orders
	std::cout << "Enter Rules: \n";
	vector<string> input = contentsOfInput();
	int numOne, numTwo;
	vector<vector<int>> rules;

	// Formulate each input into a rule, ie vector of vectors, where index 0 is lower, 1 is higher
	for (int i = 0; i < input.size(); i++) {
		sscanf(input[i].c_str(), "%d|%d", &numOne, &numTwo);
		rules.push_back(vector<int>{numOne, numTwo});
	}

	std::cout << "Enter Page Orders: \n";
	input = contentsOfInput();

	// Add numbers that can't be higher - this is nono, then compare to this, add to it as proceeding
	vector<int> nono;
	int i, j, output = 0, outputTwo = 0;
	for (string in : input) {
		nono.clear();
		vector<int> inConvert = splitStringIntoInt(in, ",");
		for (i = 0; i < inConvert.size(); i++) {


			for (j = 0; j < nono.size(); j++) 
				if (inConvert[i] == nono[j])
					break;
			
			if (j < nono.size())
				break;

			for (j = 0; j < rules.size(); j++) {
				if (inConvert[i] == rules[j][1]) {
					nono.push_back(rules[j][0]);
				}
			}


		}
		if (i < inConvert.size()) {
			// Convert to a workable list
			vector<int> newic(inConvert);
			vector<vector<int>> newRules(rules);
			std::sort(newRules.begin(), newRules.end(), [](vector<int> a, vector<int> b) {
				return a[0] > b[0];
				});
			int x, y, z, l;
			for ( x = 0; x < inConvert.size(); x++) {
				for (vector<int> rule : newRules) {
					if (rule[1] == inConvert[x]) {
						for (y = 0; newic[y] != inConvert[x]; y++) { NULL; }
						for (z = y; z < newic.size(); z++) {
							if (newic[z] == rule[0]) {
								l = newic[z];
								newic.erase(newic.begin() + z);
								newic.insert(newic.begin() + y, l);
								y++;
							}
						}
					}
				}
			}
			outputTwo += newic[newic.size() / 2];
		}
		else {
			output += inConvert[inConvert.size() / 2];
		}
			

		
	}
	std::cout << "Part 1: " << output << std::endl;
	std::cout << "Part 2: " << outputTwo << std::endl;
}


// Attempted to use topological order - didn't work since it isn't acyclic
void dayFiveAttemptOne() {
	std::cout << "Enter Rules: \n";
	vector<string> input = contentsOfInput();
	int numOne, numTwo;
	vector<vector<int>> rules;
	
	for (int i = 0; i < input.size(); i++) {
		sscanf(input[i].c_str(), "%d|%d", &numOne, &numTwo);
		rules.push_back(vector<int>{numOne, numTwo});
	}

	std::cout << "Enter Page Orders: \n";
	input = contentsOfInput();


	vector<vector<int>> adjacencyList;
	int i,j,k;

	for (vector<int> rule : rules) {
		// Check if lower part of rule exists
		for (i = 0; i < adjacencyList.size(); i++)
			if (adjacencyList[i][0] == rule[0]) {
				adjacencyList[i].push_back(rule[1]);
				break;
			}

		// If lower was not in the list already, add it and the second value
		if (i >= adjacencyList.size()) {
			adjacencyList.push_back(rule);
		}

		// If higher is not in the list, add it
		for (i = 0; i < adjacencyList.size(); i++)
			if (adjacencyList[i][0] == rule[1])
				break;
		if (i >= adjacencyList.size())
			adjacencyList.push_back(vector<int>{rule[1]});
		
	}
	
	vector<int> orderedList;
	while (adjacencyList.size() > 0) {
		std::cout << "1" << std::endl;
		// Step One - find adj list with 0
		for (i = 0; i < adjacencyList.size(); i++) {
			if (adjacencyList[i].size() == 1) {
				// Step Two - add it to ordered list - it is the lowest in the adj list
				orderedList.push_back(adjacencyList[i][0]);
				adjacencyList.erase(adjacencyList.begin() + i);
				// Step Three - Remove all connections to it here: 
				for (j = 0; j < adjacencyList.size(); j++) 
					for (k = 0; k < adjacencyList[j].size(); k++) 
						if (adjacencyList[j][k] == orderedList[orderedList.size() - 1]) 
							adjacencyList[j].erase(adjacencyList[j].begin() + k);
				i--;
			}
		}
	}

	// The list is currently reversed, so undo that...
	std::reverse(orderedList.begin(), orderedList.end());

	int output = 0;

	// Now, go through each input: if they contain the order shown, its good!
	for (string in : input) {
		vector<int> inConvert = splitStringIntoInt(in, ",");
		j = 0;
		for (i = 0; i < inConvert.size(); NULL) {
			if (j >= orderedList.size())
				break;
			if (inConvert[i] == orderedList[j])
				i++;
			j++;
		}
		if (i < inConvert.size()) {
			// This is invalid
			continue;
		}

		output += inConvert[inConvert.size() / 2];

	}

	std::cout << "Part 1: " << output << std::endl;

}
