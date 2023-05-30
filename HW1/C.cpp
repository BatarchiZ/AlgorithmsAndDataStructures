#include <vector>
#include <iostream>
#include <sstream>

std::vector<int> takeInput(char delimiter) {
    std::stringstream ss;
    std::string line;
    getline(std::cin, line);
    ss << line;
    std::vector<int> kaif;

    while (getline(ss, line, delimiter)) {
        int cycles = line.size() - 3;
        if (line[line.size() - 1] != '-') {
            cycles += 3;
        }
        bool negativeNombre = false;
        std::string strNumber;

        for (int i = 0; i < cycles; i++) {
            if (line[i] == '-') {
                negativeNombre = true;
            }
            else {
                strNumber += line[i];
            }
        }
        int nombre;
        if (strNumber.size() > 1) {
            nombre = std::stoi(strNumber);
        }
        else {
            nombre = strNumber[0] - '0';
        }
        if (negativeNombre) {
            nombre = nombre * (-1);
        }
        kaif.push_back(nombre);
    }
    return kaif;
}

#include <string>

bool flag = false;

void dig(std::vector<int> &v, int i, std::vector<int> pathV, int divisor) {
    pathV.push_back(v[i]);
    if (2 * i + 1 < v.size()) {
        dig(v, 2 * i + 1, pathV, divisor);
        dig(v, 2 * i + 2, pathV, divisor);
    }
    else {
        int sum = 0;
        for (int i: pathV) {
            sum += i;
        }
        if (sum % divisor == 0) {
            for (int i = 0; i < pathV.size(); i++) {
                if (i + 1 != pathV.size()) {
                    std::cout << pathV[i] << "--->";
                }
                else {
                    std::cout << pathV[i];
                }
            }
            std::cout << std::endl;
            flag = true;
        }
    }
}

int main() {
    int divisor;
    std::cin >> divisor;
    std::string dummy;
    getline(std::cin, dummy);
    std::vector<int> inputV = takeInput('|');
    std::vector<int> pathV;
    dig(inputV, 0, pathV, divisor);
    if (!flag) {
        std::cout << -1;
    }
    return 0;
}