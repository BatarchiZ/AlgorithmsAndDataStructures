#include <iostream>
#include <unordered_map>
#include <vector>

class DisjointSets {
public:
    DisjointSets() = default;

    std::unordered_map<long long int, long long int> depthMap;
    std::unordered_map<long long int, long long int> weights;
    std::vector<long long int> nodes;

    inline void makeSet() {
        nodes.push_back(nodes.size());
        weights[nodes.size() - 1] = 0;
    }

    int find(long long int element) //find the root of the set
    {
        if (nodes[element] == element) {
            return element;
        }
        long long int topIndex = find(nodes[element]);
        nodes[element] = topIndex;
        return topIndex;
    }

    void unite(long long int left, long long int right) {
        if (find(left) == find(right)) {
            return;
        }
        left = find(left);
        right = find(right);
        if (depthMap[left] == depthMap[right]) {
            depthMap[left] = depthMap[left] + 1;
            depthMapUtil(left, right);
        }
        else {
            long long int deep;
            long long int shallow;
            if (depthMap[left] < depthMap[right]) {
                deep = right;
                shallow = left;
            }
            else {
                deep = left;
                shallow = right;
            }
            depthMapUtil(deep, shallow);
        }
    }

    void depthMapUtil(long long int deep, long long int shallow) {
        auto it = depthMap.find(shallow);
        depthMap.erase(it);
        nodes[shallow] = deep; //Ptr to root
    }
};

#include <algorithm>
#include <string>
#include <algorithm>

int main() {
    size_t n, m, k;
    std::cin >> n >> m >> k;
    DisjointSets sets;
    for (size_t i = 0; i < n; ++i) {
        sets.makeSet();
    }
    for (size_t i = 0; i < m; ++i) {
        int u, v;
        std::cin >> u >> v;
    }
    std::vector <std::string> command(k);
    std::vector <std::pair<int, int>> u_vVector(k);
    std::string dummy;
    for (size_t i = 0; i < k; ++i) {
        getline(std::cin, dummy);
        getline(std::cin, dummy, ' ');
        std::cin >> u_vVector[i].first >> u_vVector[i].second;
        u_vVector[i].first--, u_vVector[i].second--;
        command[i] = dummy;
    }


    std::reverse(u_vVector.begin(), u_vVector.end());
    std::reverse(command.begin(), command.end());

    std::vector <std::string> answer;
    for (size_t i = 0; i < k; ++i) {
        if (command[i] == "ask") {
            if (sets.find(u_vVector[i].first) == sets.find(u_vVector[i].second)) {
                answer.push_back("YES");
            }
            else {
                answer.push_back("NO");
            }
        }
        else if (command[i] == "cut") {
            sets.unite(u_vVector[i].first, u_vVector[i].second);
        }
    }
    std::reverse(answer.begin(), answer.end());
    for (auto i: answer) {
        std::cout << i << std::endl;
    }
    return 0;
}
