#include <iostream>
#include <unordered_map>
#include <vector>

class DisjointSets {
public:
    DisjointSets() = default;

    std::unordered_map<int, int> depthMap;
    std::unordered_map<int, int> weights;
    std::vector<int> nodes;

    inline void makeSet() {
        nodes.push_back(nodes.size());
        weights[nodes.size() - 1] = 0;
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

    void unite(int left, int right, int weight) {
        if (find(left) == find(right)) {
            int root = find(left);
            auto it = weights.find(root);
            it->second += weight;
            return;
        }
        left = find(left);
        right = find(right);
        if (depthMap[left] == depthMap[right]) {
            depthMap[left] = depthMap[left] + 1;
            mergeWeightsUtil(right, left, weight);
            depthMapUtil(left, right);
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
            mergeWeightsUtil(shallow, deep, weight);
            depthMapUtil(deep, shallow);
        }
    }

    void mergeWeightsUtil(int shallow, int deep, int weight) {
        shallow = find(nodes[shallow]);
        deep = find(nodes[deep]);
        auto it_shallow = weights.find(shallow);
        auto it_deep = weights.find(deep);
        it_deep->second += it_shallow->second;
        weights.erase(it_shallow);
        it_deep->second += weight;
    }

    void depthMapUtil(int deep, int shallow) {
        auto it = depthMap.find(shallow);
        depthMap.erase(it);
        nodes[shallow] = deep; //Ptr to root
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    DisjointSets sets;

    for (int i = 0; i < n; ++i) {
        sets.makeSet();
    }
    int code;
    for (int i = 0; i < m; ++i) {
        std::cin >> code;
        if (code == 1) {
            int x, y, z;
            std::cin >> x >> y >> z;
            sets.unite(x, y, z);
        }
        else if (code == 2) {
            int node;
            std::cin >> node;
            int root = sets.find(node);

            auto it = sets.weights.find(root);
            int sum = it->second;
            std::cout << sum << std::endl;
        }
    }
    int a = 42;
    return 0;
}
