#include <iostream>
#include <vector>

struct Edge_ExchangePoint {
    size_t cur1_U;
    size_t cur2_V;
    double exch_UV;
    double comm_UV;
};

std::vector<double>
BellmanFord(int n, const std::vector <Edge_ExchangePoint> &edges, size_t curSource, double amount, size_t cycles) {
    std::vector<double> d(n, INT32_MAX);
    d[curSource] = amount;
    for (int i = 0; i < 5000; ++i) {
        for (int k = 0; k < edges.size(); ++k) {
            if (d[edges[k].cur1_U] < INT64_MAX &&
                d[edges[k].cur2_V] > (d[edges[k].cur1_U] - edges[k].comm_UV) * edges[k].exch_UV &&
                (d[edges[k].cur1_U] - edges[k].comm_UV) * edges[k].exch_UV < 0) {
                d[edges[k].cur2_V] = (d[edges[k].cur1_U] - edges[k].comm_UV) * edges[k].exch_UV;
            }
        }
    }
    return d;
}

struct Node {
    Node() : index(0) {};
    std::vector <std::pair<Node *, long long int>> vertices;
    size_t index;
};

void dfs(Node *node, std::vector<bool> &visited) {
    visited[node->index] = true;
    for (auto n: node->vertices) {
        if (!visited[n.first->index]) {
            dfs(n.first, visited);
        }
    }
}


int main() {
    double n, m, curSource, amount;
    std::cin >> n >> m >> curSource >> amount;
    curSource--;
    amount *= -1;
    std::vector <Edge_ExchangePoint> exchPts(2 * m);

    std::vector <Node> nodes(n);
    for (size_t i = 0; i < n; ++i) {
        nodes[i].index = i;
    }
    for (size_t i = 0; i < 2 * m; ++i) {
        double A, B, rAB, cAB, rBA, cBA;
        std::cin >> A >> B >> rAB >> cAB >> rBA >> cBA;
        A--;
        B--;
        exchPts[i].cur1_U = A;
        exchPts[i].cur2_V = B;
        exchPts[i].exch_UV = rAB;
        exchPts[i].comm_UV = -cAB;
        ++i;
        exchPts[i].cur1_U = B;
        exchPts[i].cur2_V = A;
        exchPts[i].exch_UV = rBA;
        exchPts[i].comm_UV = -cBA;
        nodes[exchPts[i].cur1_U].vertices.emplace_back(&nodes[exchPts[i].cur2_V], 0);

    }
    std::vector<double> d = BellmanFord(n, exchPts, curSource, amount, n - 1);
    std::vector<double> d2 = BellmanFord(n, exchPts, curSource, amount, n);

    std::vector<int> cycleEdges;
    for (size_t i = 0; i < d.size(); ++i) {
        if (d[i] > d2[i] && d2[i] < 0) {
            cycleEdges.emplace_back(i);
        }
    }
    std::vector<bool> visited(n, false);
    for (auto i: cycleEdges) {
        dfs(&nodes[i], visited);
    }


    if (d[curSource] < amount || visited[curSource]) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
    return 0;
}