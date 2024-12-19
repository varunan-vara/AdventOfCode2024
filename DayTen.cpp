#include "AoCFunctions.h"
#include <iostream>
#include <string>

vector<std::pair<int,int>> paths (vector<std::pair<int,int>>** cache, vector<vector<int>> topoMap, int x, int y, int a) {
    // Default case for max
    if (a == 9) {
        return vector<std::pair<int,int>>{{x,y}};
    }

    // Cache
    if (cache[x][y].size() > 0) {
        return cache[x][y];
    }

    // Four cases - if they are greater than the current number by 1, return that
    if (x > 0 && topoMap[x-1][y] == topoMap[x][y] + 1) {
        cache[x-1][y] = paths(cache, topoMap, x-1, y, topoMap[x-1][y]);
    }
    if (x < topoMap.size() - 1 && topoMap[x+1][y] == topoMap[x][y] + 1) {
        cache[x+1][y] = paths(cache, topoMap, x+1, y, topoMap[x+1][y]);
    }
    if (y > 0 && topoMap[x][y-1] == topoMap[x][y] + 1) {
        cache[x][y-1] = paths(cache, topoMap, x, y-1, topoMap[x][y-1]);
    }
    if (y < topoMap[x].size() - 1 && topoMap[x][y+1] == topoMap[x][y] + 1) {
        cache[x][y+1] = paths(cache, topoMap, x, y+1, topoMap[x][y+1]);
    }

    // Combine these lists
    
    
    // Default case for general
    return vector<std::pair<int,int>>{};
}

void dayTen() {
    vector<string> pInput = contentsOfInput();
    vector<vector<int>> tMap;
    vector<int> temp;

    for (string line : pInput) {
        temp.clear();
        for (char c : line) {
            temp.push_back(atoi(&c));
        }
        tMap.push_back(temp);
    }

    // Strategy: Recursive function that checks up down left and right, and then continues until a 9 is reached
    // However, a cache is used to avoid repition.
    
    // std::pair will be used for coordinates, to reduce confusion with vectors
    vector<std::pair<int,int>> **cache = (vector<std::pair<int,int>> **) malloc(tMap.size() * sizeof(vector<std::pair<int,int>>*));
    for (int i = 0; i < tMap.size(); i++) {
        cache[i] = (vector<std::pair<int,int>> *) malloc(tMap[0].size() * sizeof(vector<std::pair<int,int>>{}));
    }



    
}