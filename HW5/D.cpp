#include <vector>
#include <iostream>

struct Node {
    Node() : index(0) {};
    std::vector <std::pair<Node *, long long int>> vertices;
    size_t index;
};

struct Edge {
    long long int u = 0;
    long long int v = 0;
    long long int w = 0;
};

std::vector <Edge> readInput(size_t n, size_t e, std::vector <Node> &nodes) {
//    std::vector<Node> nodes(n);
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
//        edges[i].w = -(edges[i].w);
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

void printV(std::vector<int> v) {
    for (auto i: v) {
        std::cout << i << ' ';
    }
    std::cout << std::endl;
}

int main() {
    int n, e, s;
    std::cin >> n >> e >> s;
    s--;

    std::vector <Node> nodes(n);
    std::vector <Edge> edges = readInput(n, e, nodes);
    std::vector<long long int> d(n, INT64_MAX);
    d[s] = 0;

    //Bellman ford
    for (int i = 0; i < n - 1; ++i) {
        for (int k = 0; k < edges.size(); ++k) {
            if (d[edges[k].v] < INT64_MAX && d[edges[k].u] > d[edges[k].v] + edges[k].w) {
                d[edges[k].u] = d[edges[k].v] + edges[k].w;
            }
        }
    }
    std::vector<long long int> d2 = d;
    for (int k = 0; k < edges.size(); ++k) {
        if (d2[edges[k].v] < INT64_MAX && d2[edges[k].u] > d2[edges[k].v] + edges[k].w) {
            d2[edges[k].u] = d2[edges[k].v] + edges[k].w;
        }
    }
    std::vector<int> cycleNodes;
    for (int i = 0; i < d.size(); ++i) {
        if (d[i] != d2[i]) {
            cycleNodes.push_back(i);
        }
    }
    std::vector<bool> visited(nodes.size(), false);
    for (auto i: cycleNodes) {
        dfs(&nodes[i], visited);
    }
    for (int i = 0; i < d.size(); ++i) {
        if (d[i] == INT64_MAX) {
            std::cout << "*" << std::endl;
        }
        else if (visited[i]) {
            std::cout << '-' << std::endl;
        }
        else {
            std::cout << d[i] << std::endl;
        }
    }
    return 0;
}