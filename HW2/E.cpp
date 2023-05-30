#include <vector>
#include <iostream>
#include <algorithm>

std::vector<int> takeInput() {
    std::vector<int> input;
    int cycles;
    std::cin >> cycles;
    int dummy;
    for (int i = 0; i < cycles; i++) {
        std::cin >> dummy;
        input.push_back(dummy);
    }
    std::sort(input.begin(), input.end());
    return input;
}

#include <math.h>

double calcAreaHeron(int a, int b, int c) {
    double perimeter = (a + b + c) / 2.0;
    double area = sqrt(perimeter * (perimeter - a) * (perimeter - b) * (perimeter - c));
    return area;
}

#include <iomanip>

int main() {
    double maxArea = 0;
    std::vector<int> vAns(3, 0);
    std::vector<int> input = takeInput();

    for (int i = 0; i < input.size() - 2; i++) {
        if ((input[i] + input[i + 1] > input[i + 2] && input[i] + input[i + 2] > input[i + 1] &&
             input[i + 1] + input[i + 2] > input[i])) {
            double a = input[i];
            double b = input[i + 1];
            double c = input[i + 2];
            double area = calcAreaHeron(a, b, c);
            if (area > maxArea) {
                maxArea = area;
                vAns[0] = a, vAns[1] = b, vAns[2] = c;
            }
        }
    }
    if (maxArea == 0) {
        std::cout << 0;
        return 0;
    }

    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    std::cout << maxArea << std::endl;
    std::cout << std::setprecision(0);
    for (int i: vAns) {
        std::cout << i << ' ';
    }

    return 0;
}