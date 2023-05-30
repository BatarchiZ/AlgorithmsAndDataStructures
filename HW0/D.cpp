//
// Created by Iskander Sergazin on 12/09/2022.
//
#include <iostream>
#include <string>
#include <map>
#include <set>

class ArtCollection {
public:
    void push(std::string);

    void like(std::string);

    void dislike(std::string);

    void top(int k);

private:
    std::map<std::string, int> _nameLikesMap;
    std::set<std::pair<int, std::string>> _likesNamesSet;
};

void ArtCollection::push(std::string s) {
    auto it = _likesNamesSet.find(std::make_pair(0, s)); //log(n) complexity
    if (it == _likesNamesSet.end()) {
        _likesNamesSet.insert(std::make_pair(0, s)); //log(n) complexity
        _nameLikesMap.insert(std::make_pair(s, 0)); //log(n) complexity
    }
}

void ArtCollection::like(std::string s) {
    int prevLikes = _nameLikesMap[s];
    _nameLikesMap[s] += 1;
    _likesNamesSet.erase({prevLikes, s}); //log(n) complexity
    _likesNamesSet.insert(std::make_pair(prevLikes + 1, s)); //log(n) complexity
}

void ArtCollection::dislike(std::string s) {
    int prevLikes = _nameLikesMap[s];
    _nameLikesMap[s] -= 1;
    _likesNamesSet.erase({prevLikes, s}); //log(n) complexity
    _likesNamesSet.insert(std::make_pair(prevLikes - 1, s)); //log(n) complexity
}


void ArtCollection::top(int k) {
    auto it = _likesNamesSet.end();
    it--;
    for (int i = 0; i < k; i++) //O(k) complexity
    {
        if (i == k - 1) {
            std::cout << it->second;
            break;
        }
        std::cout << it->second + ',';
        it--;
    }
    std::cout << std::endl;
}

int main() {
    ArtCollection obj;
    std::string a;
    getline(std::cin, a, ' ');

    while (a != "q") {
        if (a == "push") {
            getline(std::cin, a);
            obj.push(a);
        }
        else if (a == "like") {
            getline(std::cin, a);
            obj.like(a);
        }
        else if (a == "dislike") {
            getline(std::cin, a);
            obj.dislike(a);
        }
        else if (a == "top") {
            getline(std::cin, a);
            int b = std::stoi(a);
            obj.top(b);
        }

        getline(std::cin, a, ' ');
    }
    return 0;
}