#include <vector>
#include <iostream>

struct Node {
    Node() : index(0) {};
    std::vector <std::pair<Node *, int>> vertices;
    size_t index;
};

struct Edge {
    int u = 0;
    int v = 0;
    int w = 0;
};

std::vector <Edge> readInput(size_t n, size_t e, std::vector <Node> &nodes) {
    for (size_t i = 0; i < n; ++i) {
        nodes[i].index = i;
    }
    std::vector <Edge> edges(e);
    for (int i = 0; i < e; i++) {
        std::cin >> edges[i].v;
        std::cin >> edges[i].u;
        std::cin >> edges[i].w;
        edges[i].v--;
        edges[i].u--;
        edges[i].w = -(edges[i].w);
        nodes[edges[i].v].vertices.emplace_back(&nodes[edges[i].u], edges[i].w);
    }
    return edges;
}

//bool HAVEPATH = false;
void dfs(Node *node, std::vector<bool> &visited) {
    visited[node->index] = true;
    for (auto n: node->vertices) {
        if (!visited[n.first->index]) {
            dfs(n.first, visited);
        }
    }
}

int main() {
    int n, e;
    std::cin >> n >> e;

    std::vector <Node> nodes(n);
    std::vector <Edge> edges = readInput(n, e, nodes);
    std::vector<int> d(n, INT16_MAX);
    d[0] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (int k = 0; k < edges.size(); ++k) {
            if (d[edges[k].v] < INT16_MAX && d[edges[k].u] > d[edges[k].v] + edges[k].w) {
                d[edges[k].u] = d[edges[k].v] + edges[k].w;
            }
        }
    }

    std::vector<int> d2 = d;
    for (int k = 0; k < edges.size(); ++k) {
        if (d2[edges[k].v] < INT16_MAX && d2[edges[k].u] > d2[edges[k].v] + edges[k].w) {
            d2[edges[k].u] = d2[edges[k].v] + edges[k].w;
        }
    }

    if (d[n - 1] == INT16_MAX) {
        std::cout << ":(";
        return 0;
    }
    for (int i = 0; i < d.size(); ++i) {
        if (d[i] > d2[i]) {
            std::vector<bool> visited(nodes.size(), false);
            dfs(&nodes[i], visited);
            if (visited[nodes.size() - 1]) {
                std::cout << ":)";
                return 0;
            }
        }
    }
    std::cout << -d[n - 1];
    return 0;
}