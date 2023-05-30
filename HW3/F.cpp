#include <iostream>
#include <vector>
#include <algorithm>

struct Node {
    Node() : index(0) {};
    std::vector<Node *> vertices;
    size_t index;
};

std::vector <Node> readInput() {
    size_t n;
    std::cin >> n;
    std::vector <Node> nodes(n);
    for (size_t i = 0; i < n; ++i) {
        nodes[i].index = i;
    }
    for (int i = 0; i < n - 1; ++i) {
        size_t x, y;
        std::cin >> x >> y;
        nodes[x - 1].vertices.emplace_back(&nodes[y - 1]);
        nodes[y - 1].vertices.emplace_back(&nodes[x - 1]);
    }
    return nodes;
}

int maxChain = 0;

void dfs(Node *node, int counter, std::vector<bool> &visited) {
    for (auto v: node->vertices) {
        if (!visited[v->index]) {
            visited[v->index] = true;
            dfs(v, counter + 1, visited);
        }
    }
    if (maxChain < counter) {
        maxChain = counter;
    }
}

int main() {
    std::vector <Node> nodes = readInput();
    for (int i = 0; i < nodes.size(); ++i) {
        std::vector<bool> visited(nodes.size(), false);
        visited[nodes[i].index] = true;
        dfs(&nodes[i], 1, visited);
    }
    std::cout << maxChain;
    return 0;
}
