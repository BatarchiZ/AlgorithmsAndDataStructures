#include <iostream>
#include <unordered_map>
#include <vector>

class DisjointSets {
public:
    DisjointSets() = default;

    std::unordered_map<int, int> depthMap;
    std::unordered_map<int, int> numberOfElements;
    std::vector<int> nodes;

    inline void makeSet() {
        nodes.push_back(nodes.size());
        numberOfElements[nodes.size() - 1] = 1;
    }

    int find(int element) //find the root of the set
    {
        if (nodes[element] == element) {
            return element;
        }
        int topIndex = find(nodes[element]);
        nodes[element] = topIndex;
        return topIndex;
    }

    void unite(int left, int right) {
        left = find(left);
        right = find(right);
        if (left == right) {
            return;
        }
        if (depthMap[left] == depthMap[right]) {
            depthMap[left] = depthMap[left] + 1;
            auto it = depthMap.find(right);
            depthMap.erase(it);
            nodes[right] = left; //Ptr to root
            auto itt = numberOfElements.find(right);
            numberOfElements[left] += itt->second;
            numberOfElements.erase(itt);
        }
        else {
            int deep;
            int shallow;
            if (depthMap[left] < depthMap[right]) {
                deep = right;
                shallow = left;
            }
            else {
                deep = left;
                shallow = right;
            }
            auto it = depthMap.find(shallow);
            depthMap.erase(it);
            nodes[shallow] = deep;
            auto itt = numberOfElements.find(shallow);
            numberOfElements[deep] += itt->second;
            numberOfElements.erase(itt);
        }
    }

    bool getEl(int numberElm) {
        for (auto i: numberOfElements) {
            if (i.second == numberElm) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    DisjointSets oceania;
    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        oceania.makeSet();
    }
    int i, j;
    for (int k = 0; k < m; ++k) {
        std::cin >> i >> j;
        i--, j--;
        oceania.unite(i, j);
        if (oceania.getEl(n)) {
            std::cout << k + 1;
            return 0;
        }
    }
    std::cout << "HelloWorld" << std::endl;
    return 0;
}
