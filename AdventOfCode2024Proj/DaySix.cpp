#include "../AdventOfCode2024Proj/AoCFunctions.h"
#include <iostream>

enum Direction {
	NORTH = 0,
	SOUTH = 2,
	EAST = 1,
	WEST = 3
};

class Guard {
public:
	int x, y;
	Direction direction;
	Guard(int inx, int iny, Direction indirection) {
		direction = indirection;
		x = inx, y = iny;
	}

	// Returns 0 if moved, 1 if object in way, 2 if out of bounds
	int moveForward(vector<vector<int>> floorPlan) {
		if (direction == SOUTH) {
			if (x < floorPlan.size() - 1) {
				if (floorPlan[x + 1][y] == 0) {
					x++;
					return 0;
				} else { return 1;}
			} else { return 2; }
		}

		if (direction == NORTH) {
			if (x > 0) {
				if (floorPlan[x - 1][y] == 0) {
					x--;
					return 0;
				} else { return 1;}
			} else { return 2; }
		}

		if (direction == EAST) {
			if (y < floorPlan[0].size() - 1) {
				if (floorPlan[x][y + 1] == 0) {
				y++;
					return 0;
				} else { return 1; }
			} else { return 2; }
		}

		if (direction == WEST) {
			if (y > 0) {
				if (floorPlan[x][y - 1] == 0) {
					y--;
					return 0;
				} else { return 1; }
			} else { return 2; }
		}
		
		return false;
	}

	void turnRight() {
		switch (direction) {
			case NORTH:
				direction = EAST;
				break;
			case EAST:
				direction = SOUTH;
				break;
			case SOUTH:
				direction = WEST;
				break;
			case WEST:
				direction = NORTH;
				break;
		}
	}
};

void daySix() {
	std::cout << "Enter Puzzle Input, followed by '.' to show the end: \n";
	vector<string> input = contentsOfInput();

	// Create floorplan and guard
	vector<vector<int>> floorPlan(input.size(), vector<int>(input[0].size(), 0));
	Guard* g = new Guard(0,0,NORTH); // G2 for Part 2
	int origx=0, origy=0;
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[i].size(); j++) {
			switch (input[i][j]) {
				case ('#'):
					floorPlan[i][j] = 1;
					break;
				case ('^'):
					g = new Guard(i,j,NORTH); 
					origx = i, origy = j;
					// Continue to next;
				case ('.'):
					floorPlan[i][j] = 0;
					break;
			}
		}
	}

	vector<vector<int>> visited(floorPlan.size(), vector<int>(floorPlan[0].size(), 0));
	visited[g->x][g->y] = 1;
	int outcome;

	while (true) {
		// Move the guard forward, if boolean is true, continue
		outcome = g->moveForward(floorPlan);
		
		if (outcome == 0) 
			visited[g->x][g->y] = 1;
		

		// Case 1: Item in front of it
		if (outcome == 1) 
			g->turnRight();
		
		// Case 2: Item behind it
		if (outcome == 2) 
			break;
		
	}

	int output = 0;
	for (vector<int> line : visited)
		for (int i : line)
			output += i;
	std::cout << "Part 1: " << output << std::endl;


	// For Part 2, going through each possibility makes no sense since only one object can be added, the path has to be broken
	// on values that have already been visited.
	// The most efficient way would be to calculate lines at which the security guard travels, where it intersects (even if the guard
	// hasn't used that part of the line, it can be used to create a loop), then check those.
	// Alternatively, easier to program, and still more efficient than checking each index, is doing each visited square.

	int i, j, r1; output = 0;
	vector<vector<int>> floorPlanDuplicate; vector<vector<vector<int>>> travelDir;
	for (i = 0; i < visited.size(); i++) {
		for (j = 0; j < visited[i].size(); j++) {
			if (visited[i][j] == 0) {
				continue;
			}
			std::cout << i << ", " << j << std::endl;


			g = new Guard(origx, origy, NORTH);
			travelDir = vector<vector<vector<int>>>(floorPlan.size(), vector<vector<int>>(floorPlan[0].size(), vector<int>(4, 0)));
			floorPlanDuplicate = floorPlan;
			floorPlanDuplicate[i][j] = 1;

			// Move g2 twice, and g once. After the first round, if they are in the same place, then there is a loop
			
			while (true) {
				r1 = g->moveForward(floorPlanDuplicate);
				if (r1 == 2) {
					break; // There is no loop
				}
				while (r1 == 1) { // if (r2 == 1)
					g->turnRight();
					r1 = g->moveForward(floorPlanDuplicate);
				}

				if (travelDir[g->x][g->y][g->direction] == 1) {
					output++;
					break;
				}
				else {
					travelDir[g->x][g->y][g->direction] = 1;
				}
				
			}
			
		}
	}

	std::cout << "Part 2: " << output << std::endl;

	
}