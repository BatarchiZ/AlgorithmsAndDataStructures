#include <iostream>
#include <vector>


struct Node {
    Node() : index(0) {};
    std::vector<Node *> vertices;
    size_t index;
    size_t component_number;
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

void dfs(std::vector<bool> &visited, Node *node, Node *prevNode, int componentNumber) {
    for (auto i: node->vertices) {
        if (i == prevNode) {
            continue;
        }
        if (!visited[i->index]) {
            visited[i->index] = true;
            i->component_number = componentNumber;
            dfs(visited, i, node, componentNumber);
        }
    }
}

int main() {
    int componentNumber = 1;
    std::vector <Node> nodes = readInput();
    std::vector<bool> visited(nodes.size(), false);
    for (int i = 0; i < nodes.size(); i++) {
        if (!visited[nodes[i].index]) {
            visited[nodes[i].index] = true;
            nodes[i].component_number = componentNumber;
            dfs(visited, &nodes[i], nullptr, componentNumber);
            componentNumber++;
        }
    }
    std::cout << componentNumber - 1 << std::endl;
    for (const auto &n: nodes) {
        std::cout << n.component_number << ' ';
    }
    return 0;
}
