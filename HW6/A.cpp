#include <iostream>
#include <unordered_map>
#include <vector>

class DisjointSets {
public:
    DisjointSets() = default;

    std::unordered_map<int, int> depthMap;
    std::vector<int> nodes;

    inline void makeSet() {
        nodes.push_back(nodes.size());
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
        int leftcopy = left, rightcopy = right;

        left = find(left);
        right = find(right);
        if (left == right) {
            std::cout << "ALREADY" << ' ' << leftcopy << ' ' << rightcopy << std::endl;
            return;
        }
        if (depthMap[left] == depthMap[right]) {
            depthMap[left] = depthMap[left] + 1;
            auto it = depthMap.find(right);
            depthMap.erase(it);
            nodes[right] = left;
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
        }
    }
};

int main() {
    std::string str = "DUMMY";
    DisjointSets sets;
    while (str != "") {
        getline(std::cin, str, ' ');
        if (str == "RESET") {
            int n;
            std::cin >> n;
            DisjointSets sets_reset;
            for (int i = 0; i < n; ++i) {
                sets_reset.makeSet();
            }
            std::swap(sets_reset, sets);
            std::cout << "RESET DONE" << std::endl;
        }
        else if (str == "JOIN") {
            int j, k;
            std::cin >> j >> k;
            sets.unite(j, k);
        }
        else if (str == "CHECK") {
            int j, k;
            std::cin >> j >> k;
            int left = sets.find(j);
            int right = sets.find(k);
            if (left == right) {
                std::cout << "YES" << std::endl;
            }
            else {
                std::cout << "NO" << std::endl;
            }

        }
        std::string dummy;
        getline(std::cin, dummy);
    }
}
