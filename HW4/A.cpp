//
// Created by Iskander Sergazin on 17/03/2023.
// ааа
#include <iostream>
#include <vector>
#include <algorithm>
// CHECKED


void recursive(const std::vector<int> &nodes, int &counter, int i) {
    if (nodes[i] == -1) {
        return;
    }
    else {
        counter++;
        recursive(nodes, counter, nodes[i]);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nodes(n, -1);
    for (int i = 1; i < n; ++i) {
        int a;
        std::cin >> a;
        nodes[i] = a - 1;
    }

    int heightMax = 0;
    std::vector<int> heights(n, 0);
    for (int i = 1; i < n; ++i) {
        int height = 0;
        recursive(nodes, height, i);
        heights[i] = height;
        heightMax = std::max(height, heightMax);
    }
    int count = 0;
    count = std::count(heights.begin(), heights.end(), heightMax);
    std::cout << heightMax << std::endl << count << std::endl;
    for (int i = 0; i < heights.size(); ++i) {
        if (heights[i] == heightMax) {
            std::cout << i + 1 << ' ';
        }
    }
    return 0;
}
