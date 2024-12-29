#include "AoCFunctions.h"
#include <iostream>
#include <math.h>



vector<long long> blink (long long stone, int blinks, vector<std::pair<long long, vector<long long>>> cache) {
    // Check cache
    for (std::pair<long long, vector<long long>> cacheItem : cache) {
        if (cacheItem.first == stone) {
            return cacheItem.second;
        }
    }


    vector<long long> result;

    // Calculate for stone
    if (stone == 0) {
        result.push_back(1);
    } else {
        int digits = 0; long long tStone = stone;
        while (tStone > 0) {
            digits++;
            tStone = tStone / 10;
        }

        if (digits % 2 == 0) {
            result.push_back(stone / (long long) pow(10, digits / 2));
            result.push_back(stone % (long long) pow(10, digits / 2));
        } else {
            result.push_back(stone * 2024);
        }
    }

    if (blinks <= 1) {
        cache.push_back(std::pair<long long, vector<long long>>{stone, result});
        return result;
    }

    vector<long long> tList, finalReturnList;
    for (int i = 0; i < result.size(); i++) {
        tList.clear();
        tList = blink(result[i], blinks - 1, cache);
        finalReturnList.insert(finalReturnList.end(), tList.begin(), tList.end());
    }

    cache.push_back(std::pair<long long, vector<long long>>{stone, finalReturnList});
    return finalReturnList;
}

void dayEleven() {
    vector<string> input = contentsOfInput();

    vector<long long> stones;
    size_t pos = 0;
    string temp;

    while((pos = input[0].find(" ")) != std::string::npos) {
        temp = input[0].substr(0,pos);
        stones.push_back(stoll(temp));
        input[0].erase(0, pos + 1);
    }

    stones.push_back(stoll(input[0]));

    vector<std::pair<long long, vector<long long>>> cache25;
    vector<std::pair<long long, vector<long long>>> cache75;
    vector<long long> tList;
    vector<long long> answer;


    for (int i = 0; i < stones.size(); i++) {
        tList.clear();
        tList = blink(stones[i], 25, cache25);
        answer.insert(answer.end(), tList.begin(), tList.end());
    }


    std::cout << "Part 1: " << answer.size() << std::endl;


    answer.clear();
    for (int i = 0; i < stones.size(); i++) {
        std::cout << stones[i] << std::endl;
        tList.clear();
        tList = blink(stones[i], 75, cache75);
        answer.insert(answer.end(), tList.begin(), tList.end());
    }

    std::cout << "Part 2: " << answer.size() << std::endl;

}