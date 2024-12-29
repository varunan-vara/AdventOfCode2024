#include "AoCFunctions.h"
#include <iostream>
#include <map>

string getCoordSting(int x, int y) {
    return (std::to_string(x) + "-" + std::to_string(y));
}

int findPerimeter(int x, int y, vector<vector<char>> regionMap) {
    int result = 0;
    result += (int) (x > 0 && regionMap[x-1][y] != regionMap[x][y]);
    result += (int) (x < regionMap.size() - 1 && regionMap[x+1][y] != regionMap[x][y]);
    result += (int) (y > 0 && regionMap[x][y-1] != regionMap[x][y]);
    result += (int) (y < regionMap[x].size() - 1 && regionMap[x][y+1] != regionMap[x][y]);
    return result;
}

class Region {
    public:
        int perimeter = 0;
        int area = 0;
        vector<int> homeCoords;

        Region() {}
        Region (int x, int y) {
            homeCoords.push_back(x);
            homeCoords.push_back(y);
        }

        string getCoords() {
            return getCoordSting(homeCoords[0], homeCoords[1]);
        }

        void addArea(int a) {
            area += a;
        }

        void addPerimeter(int p) {
            perimeter += p;
        }

        void mergeRegions(Region r) {
            perimeter += r.perimeter;
            area += r.area;
        }
        int price () {
            return area * perimeter;
        }
};

void dayFive() {
    vector<string> input = contentsOfInput();
    
    vector<vector<char>> regionMap;
    vector<char> temp;

    for (string line : input) {
        temp.clear();
        for (char c : line) {
            temp.push_back(c);
        }
        regionMap.push_back(temp);
    }

    vector<vector<string>> homeCoords;
    std::map<string, Region> regions;

    // Prefill all of the homeCoord locations
    std::fill(homeCoords.begin(), homeCoords.end(), vector<string>{});
    for (int u = 0; u < homeCoords.size(); u++) {
        std::fill(homeCoords[u].begin(), homeCoords[u].end(), "");
    }

    for (int i = 0; i < regionMap.size(); i++) {
        
        for (int j = 0; j < regionMap[i].size(); j++) {
            // Coords are i,j
            // Check each of the coords - runtime of O(n) given n is the number of spaces on the map
            // Points above and to the left of the coord have already been recorded. Check these points, if they 
            // have the same region char, then the current coord is part of that region.
            // 
            // Regions are based on their home coordinates, which is the first coordinate measured
            // If the above and left are not the same region char, then start a new region with the current coords.
            // If both above and left are part of the same region, but have different home coords, then merge the two.
            

            // Three cases
            bool isUpSame = (i > 0 && regionMap[i-1][j] == regionMap[i][j]);
            bool isLeftSame = (j > 0 && regionMap[i][j-1] == regionMap[i][j]);

            // If both are false
            if (!isUpSame && !isLeftSame) {
                Region rTemp = Region(i,j);
                rTemp.addArea(1);
                rTemp.addPerimeter(findPerimeter(i,j,regionMap));
                regions.insert({getCoordSting(i,j), rTemp});

                // Add to homeCoords
                homeCoords[i][j] = rTemp.getCoords();
            }

            // If both are true
            else if (isUpSame && isLeftSame) {
                // Always prefer the left over the top (j over i)
                if (homeCoords[i-1][j] != homeCoords[i][j-1]) {
                    if (regions.count(homeCoords[i-1][j])) {
                        regions[homeCoords[i][j-1]].mergeRegions(regions[homeCoords[i-1][j]]);
                        regions.erase(homeCoords[i-1][j]);
                    }
                }
                // If both have the same home, no need to merge, both should do the following
                regions[homeCoords[i][j-1]].addArea(1);
                regions[homeCoords[i][j-1]].addPerimeter(findPerimeter(i,j,regionMap));

                // Add to homeCoords
                homeCoords[i][j] = getCoordSting(i,j-1);
            }

            else if (isUpSame && !isLeftSame) {
                // This may mean the one above may be abandoned already, so this may mean creating a new region
                if (!regions.count(homeCoords[i-1][j])) {
                    Region rTemp = Region(i,j);
                    rTemp.addArea(1);
                    rTemp.addPerimeter(findPerimeter(i,j,regionMap));
                    regions.insert({getCoordSting(i,j), rTemp});

                    // Add to homeCoords
                    homeCoords[i][j] = rTemp.getCoords();
                }
                else {
                    regions[homeCoords[i-1][j]].addArea(1);
                    regions[homeCoords[i-1][j]].addPerimeter(findPerimeter(i,j,regionMap));
                }
                homeCoords[i][j] = getCoordSting(i-1,j);
            }
            else if (!isUpSame && isLeftSame) {
                regions[homeCoords[i][j-1]].addArea(1);
                regions[homeCoords[i][j-1]].addPerimeter(findPerimeter(i,j,regionMap));
                homeCoords[i][j] = getCoordSting(i,j-1);
            }
        }
    }


    int price = 0;
    for (auto l : regions) {
        price += l.second.price();
    }

    std::cout << "Part 1: " << price << std::endl; 
}