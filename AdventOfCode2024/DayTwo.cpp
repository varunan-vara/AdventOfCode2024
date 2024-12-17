#include "AoCFunctions.h"
#include <iostream>

// 1 if safe, 0 if unsafe
int checkReport(vector<int> report, int numErrors) {
	vector<int> newReport;
	for (int i = 1; i < report.size(); i++)
		if ( // This if case looks for an error, if this statement is never triggered, the function returns 1
            ((report[i] - report[i - 1] < 1 || report[i] - report[i - 1] > 3) && (report[1] > report[0])) || // Increasing Numbers in Report
            ((report[i - 1] - report[i] < 1 || report[i - 1] - report[i] > 3) && (report[1] < report[0])) || // Decreasing Numbers in Report
			report [1] == report[0]																		   // Same numbers, meaning error
			) {
			if (!numErrors) 
				return 0;
			else {
				// If there is an error at the first two numbers (i = 1), then we can choose between getting the first or second
				// 
				// In the off chance the first two numbers' pattern is the opposite of all the others, we will run into an error at i = 2
				// We can rectify this by removing the first value.
				if (i == 1 || i == 2) {
					newReport = report; newReport.erase(newReport.begin());
					if (checkReport(newReport, numErrors - 1)) {
						return 1;
					}
				}

				newReport = report; newReport.erase(newReport.begin() + i);
				return checkReport(newReport, numErrors - 1);
			}
		}
	return 1;
}

void dayTwo() {
	std::cout << "Enter puzzle input: ";
	// Returns an array of strings representing the lines of the input file
	vector<string> input = contentsOfInput();
	vector<vector<int>> reports;
	vector<int> line;
	for (int i = 0; i < input.size(); i++) {
		line = splitStringIntoInt(input[i], " ");
		reports.push_back(line);
	}

	// Iterate over each report, and go down the list until the end or until an error is found
	int safe = 0;
	for (vector<int> report : reports) {
		safe += checkReport(report, 0);
	}

	std::cout << "Part One : " << safe << std::endl;

	safe = 0;
	for (vector<int> report : reports) {
		safe += checkReport(report, 1);
	}

	std::cout << "Part Two : " << safe << std::endl;

}
