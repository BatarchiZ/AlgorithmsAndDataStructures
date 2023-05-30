#include <string>
#include <iostream>
#include <unordered_map>

std::unordered_map<char, int> createMap() {
    std::unordered_map<char, int> letterOccMap;
    std::string str;
    getline(std::cin, str);
    for (char a: str) //Linear complexity
    {
        if (a == ' ') {
            continue;
        }
        a = tolower(a);
        const std::unordered_map<char, int>::iterator it = letterOccMap.find(a); //Const complexity
        if (it == letterOccMap.end()) {
            letterOccMap[a] = 1;
        }
        else {
            letterOccMap[a] += 1;
        }
    }
    return letterOccMap;
}


int main() {
    std::unordered_map<char, int> map1 = createMap();
    std::unordered_map<char, int> map2 = createMap();
    for (const std::pair<char, int> p: map1) //Linear Complexity
    {
        if (p.second != map2[p.first]) {
            std::cout << "No";
            return 0;
        }
    }
    std::cout << "Yes";
    return 0;
}

