//
// Created by Iskander Sergazin on 27/10/2022.
// I will clean it up I promise -> Functions can be condensed -> less code = better code
#include <vector>
#include <string>
#include <iostream>

int maxNumberOfElements = 0;

std::vector<char> takeSingleInput() {
    std::vector<char> ansV;
    std::string str;
    getline(std::cin, str);
    if (str.length() > maxNumberOfElements) {
        maxNumberOfElements = str.length();
    }
    for (char i: str) {
        ansV.push_back(i);
    }
    return ansV;
}

std::vector<std::vector<char>> takeAllInput() {
    std::vector<std::vector<char>> ansV;
    std::string dummy;
    getline(std::cin, dummy);
    int cycles = stoi(dummy);
    for (int i = 0; i < cycles; i++) {
        std::vector<char> oneGuyORWOMAN = takeSingleInput();
        ansV.push_back(oneGuyORWOMAN);
    }
    for (std::vector<char> &v: ansV) {
        while (v.size() != maxNumberOfElements) {
            v.push_back('@');
        }
    }
    return ansV;
}

#include <map>

std::vector<std::vector<char>> sortCard(std::vector<std::vector<char>> &inputV) {
    std::vector<std::vector<char>> outputV;
    std::map<char, std::vector<std::vector<char>>> mapa;
    for (std::vector<char> v: inputV) {
        mapa[v[1]].push_back(v);
    }
    outputV.clear();
    char card = 'B';
    for (auto v: mapa[card]) {
        outputV.push_back(v);
    }
    card = 'P';
    for (auto v: mapa[card]) {
        outputV.push_back(v);
    }
    card = 'G';
    for (auto v: mapa[card]) {
        outputV.push_back(v);
    }
    card = 'S';
    for (auto v: mapa[card]) {
        outputV.push_back(v);
    }
    inputV = outputV;
    return outputV;
}


std::vector<std::vector<char>> sortPriority(std::vector<std::vector<char>> &inputV) {
    std::vector<std::vector<char>> outputV;
    std::map<char, std::vector<std::vector<char>>> mapa;
    for (std::vector<char> v: inputV) {
        mapa[v[0]].push_back(v);
    }
    outputV.clear();
    for (auto p: mapa) {
        for (auto v: p.second) {
            outputV.push_back(v);
        }
    }
    return outputV;
}


std::vector<std::vector<char>> sortSurname(std::vector<std::vector<char>> &inputV) {
    std::vector<std::vector<char>> outputV;
    for (int i = inputV[0].size() - 1; i > 5; i--) {
        std::map<char, std::vector<std::vector<char>>> mapa;
        for (std::vector<char> v: inputV) {
            mapa[v[i]].push_back(v);
        }
        outputV.clear();
        for (auto p: mapa) {
            for (auto v: p.second) {
                outputV.push_back(v);
            }
        }
        inputV = outputV;
    }
    return outputV;
}

std::vector<std::vector<char>> sortTime(std::vector<std::vector<char>> &inputV) {
    std::vector<std::vector<char>> outputV;
    for (int i = 5; i > 1; i--) {
        std::map<char, std::vector<std::vector<char>>> mapa;
        for (std::vector<char> v: inputV) {
            mapa[v[i]].push_back(v);
        }
        outputV.clear();
        for (auto p: mapa) {
            for (auto v: p.second) {
                outputV.push_back(v);
            }
        }
        inputV = outputV;
    }
    return outputV;
}

int main() {
    std::vector<std::vector<char>> inputV = takeAllInput();
    std::vector<std::vector<char>> vSorted = sortSurname(inputV);
    vSorted = sortTime(vSorted);
    vSorted = sortCard(vSorted);
    vSorted = sortPriority(vSorted);
    for (auto v: vSorted) {
        for (char i: v) {
            if (i != '@') {
                std::cout << i;
            }
        }
        std::cout << std::endl;
    }
    return 0;
}
