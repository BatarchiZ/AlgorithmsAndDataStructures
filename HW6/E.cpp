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

    void unite(long long int left, long long int right, long long int weight) {
        if (find(left) == find(right)) {
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
            mergeWeightsUtil(shallow, deep, weight);
            depthMapUtil(deep, shallow);
        }
    }

    void mergeWeightsUtil(long long int shallow, long long int deep, long long int weight) {
        shallow = find(nodes[shallow]);
        deep = find(nodes[deep]);
        auto it_shallow = weights.find(shallow);
        auto it_deep = weights.find(deep);
        it_deep->second += it_shallow->second;
        weights.erase(it_shallow);
        it_deep->second += weight;
    }

    void depthMapUtil(long long int deep, long long int shallow) {
        auto it = depthMap.find(shallow);
        depthMap.erase(it);
        nodes[shallow] = deep; //Ptr to root
    }
};

struct Edge {
    long long int u;
    long long int v;
    long long int w;
};

bool comp(const Edge &left, const Edge &right) {
    return left.w < right.w;
}

#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector <Edge> edges(m);
    for (size_t i = 0; i < m; ++i) {
        std::cin >> edges[i].u;
        std::cin >> edges[i].v;
        std::cin >> edges[i].w;
    }
    std::sort(edges.begin(), edges.end(), comp);

    DisjointSets sets;
    for (size_t i = 0; i < n; ++i) {
        sets.makeSet();
    }

    for (size_t i = 0; i < m; ++i) {
        if (sets.find(edges[i].u) != sets.find(edges[i].v)) {
            sets.unite(edges[i].u, edges[i].v, edges[i].w);
        }
    }
    if (sets.weights.size() > 1) {
        std::cout << "NON-CONNECTED";
        return 0;
    }
    auto it = sets.weights.begin();
    std::cout << it->second << std::endl;
    int a = 42;
    return 0;
}
