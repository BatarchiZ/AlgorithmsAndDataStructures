//
// Created by Iskander Sergazin on 11/09/2022.
//

#include <iostream>
#include <vector>

std::vector<int> takeInput() {
    int c;
    std::cin >> c;
    std::vector<int> v;
    for (int i = 0; i < c; i++) {
        int n;
        std::cin >> n;
        v.push_back(n);
    }
    return v;
}


int binarySearchLeftPos(std::vector<int> &v, int l, int r, int target) //O(log(n))
{
    int c = l + (r - l) / 2;
    if (l >= r) {
        return -1;
    }
    if (v[c] != target) {
        if (v[c] > target) {
            binarySearchLeftPos(v, l, c - 1, target);
        }
        if (v[c] < target) {
            binarySearchLeftPos(v, c + 1, r, target);
        }
    }
    if ((v[c] == target) && (v[c - 1] == target)) {
        return binarySearchLeftPos(v, l, c - 1, target);
    }
    else {
        return c;
    }
}

int binarySearchRightPos(std::vector<int> &v, int l, int r, int target) //O(log(n))
{
    int c = l + (r - l) / 2;
    if (l > r) {
        return -1;
    }
    if (v[c] != target) {
        if (v[c] > target) {
            binarySearchRightPos(v, l, c - 1, target);
        }
        if (v[c] < target) {
            binarySearchRightPos(v, c + 1, r, target);
        }
    }
    if ((v[c] == target) && (v[c + 1] == target)) {
        return binarySearchRightPos(v, c + 1, r, target);
    }
    else {
        return c;
    }
}


int main() {
    std::vector<int> ansV = takeInput();
    int target;
    std::cin >> target;
    int leftPos = binarySearchLeftPos(ansV, 0, ansV.size(), target);
    int rightPos = binarySearchRightPos(ansV, 0, ansV.size(), target);
    std::cout << leftPos << ' ' << rightPos;
    return 0;
}
