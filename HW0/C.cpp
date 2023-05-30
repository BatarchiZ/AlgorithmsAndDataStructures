//
// Created by Iskander Sergazin on 12/09/2022.
//

#include <iostream>
#include <unordered_map>


class LotteryBox {
public:
    bool insert(std::string &s);

    bool remove(std::string &s);

    std::string takeWinner();

private:
    std::unordered_map<int, std::string> _numNames;
    std::unordered_map<std::string, int> _nameNum;
    int _counter = 0;

};

bool LotteryBox::insert(std::string &s) {
    const auto it = _nameNum.find(s);
    if (it == _nameNum.end()) {
        _nameNum.insert(std::make_pair(s, _counter));
        _numNames.insert(std::make_pair(_counter, s));
        ++_counter;
        std::cout << "true" << std::endl;
        return true;
    }
    else {
        std::cout << "false" << std::endl;
        return false;
    }

}

bool LotteryBox::remove(std::string &s) //Const time compelxity
{
    auto it = _nameNum.find(s);
    if (it == _nameNum.end()) {
        std::cout << "false" << std::endl;
        return false;
    }
    else {
        int number = _nameNum[s];
        _nameNum.erase(it);
        _numNames.erase(number);

        auto it2 = _numNames.find(_counter - 1);
        if (it2 != _numNames.end()) {
            std::string name = it2->second;
            _numNames.erase(_counter - 1);
            _nameNum.erase(name);
            _nameNum.insert(std::make_pair(name, number));
            _numNames.insert(std::make_pair(number, name));
        }
        --_counter;
        std::cout << "true" << std::endl;
        return true;
    }
}

std::string LotteryBox::takeWinner() {
    int increment = 0;
    if (!_numNames.empty()) {
        return _numNames[increment];
    }
    else {
        return "0";
    }
}

int main() {
    LotteryBox object;
    char s;
    std::cin >> s;
    while (s != 'q') {
        if (s == '+') {
            std::string name;
            std::cin >> name;
            object.insert(name);
        }
        else if (s == '-') {
            std::string name;
            std::cin >> name;
            object.remove(name);
        }
        else if (s == '?') {
            std::string str = object.takeWinner();
            std::cout << str << std::endl;
        }
        std::cin >> s;
    }
    return 0;
}

