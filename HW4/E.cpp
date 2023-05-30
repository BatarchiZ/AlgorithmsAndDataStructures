#include <iostream>
#include <vector>


struct Node {
    Node() : index(0) {};
    std::vector<Node *> vertices;
    size_t index;
};

std::vector <Node> readInput(int &s) {
    size_t n, e;
    std::cin >> n >> e >> s;
    s--;
    std::vector <Node> nodes(n);
    for (size_t i = 0; i < n; ++i) {
        nodes[i].index = i;
    }
    for (int i = 0; i < e; i++) {
        size_t x, y;
        std::cin >> x >> y;
        nodes[x - 1].vertices.emplace_back(&nodes[y - 1]);
        nodes[y - 1].vertices.emplace_back(&nodes[x - 1]);
    }
    return nodes;
}


#include <queue>

std::vector<int> BFS(int s, std::vector <Node> &nodes) {
    std::vector<int> ans;
    std::queue < Node * > q;
    std::vector<bool> visited(nodes.size(), false);
    q.push(&nodes[s]);
    visited[s] = true;
    while (!q.empty()) {
        for (auto i: q.front()->vertices) {
            if (!visited[i->index]) {
                visited[i->index] = true;
                q.push(i);
            }
        }
        ans.push_back(q.front()->index + 1);
        q.pop();
    }
    return ans;
}


int main() {
    int s;
    std::vector <Node> nodes = readInput(s);
    std::vector<int> ans = BFS(s, nodes);
    std::cout << ans.size() << std::endl;
    for (auto i: ans) {
        std::cout << i << ' ';
    }

    return 0;
}
