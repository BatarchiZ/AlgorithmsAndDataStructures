#include <iostream>
#include <vector>


struct Node {
    Node() : index(0) {};
    std::vector<Node *> vertices;
    size_t index;
};

std::vector <Node> readInput() {
    size_t n, e;
    std::cin >> n >> e;
    std::vector <Node> nodes(n);
    for (size_t i = 0; i < n; ++i) {
        nodes[i].index = i;
    }
//    while (true)
    for (int i = 0; i < e; i++) {
        size_t x, y;
        std::cin >> x >> y;
        nodes[x - 1].vertices.emplace_back(&nodes[y - 1]);
        nodes[y - 1].vertices.emplace_back(&nodes[x - 1]);
    }
    return nodes;
}

bool check = true;

void dfs(std::vector<bool> &visited, Node *node, Node *prevNode) {
    for (auto i: node->vertices) {
        if (i == prevNode) {
            continue;
        }
        if (visited[i->index]) {
            check = false;
            continue;
        }
        else {
            visited[i->index] = true;
            dfs(visited, i, node);
        }
    }
}

int main() {
    std::vector <Node> nodes = readInput();
    std::vector<bool> visited(nodes.size(), false);
    visited[0] = true;
    dfs(visited, &nodes[0], nullptr);
    for (auto i: visited) {
        if (!i) {
            std::cout << "NO";
            return 0;
        }
    }

    if (check) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
    return 0;
}
