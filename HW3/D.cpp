#include <iostream>
#include <vector>
#include <algorithm>

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
    for (int i = 0; i < e; i++) {
        size_t x, y;
        std::cin >> x >> y;
        if (std::find(nodes[x - 1].vertices.begin(), nodes[x - 1].vertices.end(), &nodes[y - 1]) ==
            nodes[x - 1].vertices.end()) {
            nodes[x - 1].vertices.emplace_back(&nodes[y - 1]);
        }
    }
    return nodes;
}

Node *CYCLENODE = nullptr;
bool BOOLCYCLE = false;

void findCycle(std::vector<bool> &visited, Node *node, std::vector<bool> &path) {
    for (auto i: node->vertices) {
        if (CYCLENODE) {
            return;
        }
        if (path[i->index]) {
            CYCLENODE = i;
            return;
        }
        else if (!visited[i->index]) {
            visited[i->index] = true;
            path[i->index] = true;
            findCycle(visited, i, path);
            path[i->index] = false;
        }
    }
}

std::vector<Node *> PATH;

void dfs(std::vector<bool> &visited, Node *node, std::vector<Node *> &path) {
    for (auto i: node->vertices) {
        if (!visited[i->index]) {
            visited[i->index] = true;
            path.push_back(i);
            dfs(visited, i, path);
        }
        else if (PATH.empty()) {
            PATH = path;
        }
    }
}

int main() {
    std::vector <Node> nodes = readInput();
    for (const auto &n: nodes) {
        std::vector<bool> visited(nodes.size(), false);
        std::vector<bool> path(nodes.size(), false);
        findCycle(visited, &nodes[n.index], path);
    }

    if (!CYCLENODE) {
        std::cout << "NO";
        return 0;
    }
    else {
        std::vector<bool> visited(nodes.size(), false);
        visited[CYCLENODE->index] = true;
        std::vector < Node * > path;
        path.push_back(CYCLENODE);
        dfs(visited, CYCLENODE, path);

        if (path.empty()) {
            std::cout << "NO";
            return 0;
        }
        std::cout << "YES" << std::endl;
        for (auto c: PATH) {
            std::cout << c->index + 1 << ' ';
        }
    }
    return 0;
}