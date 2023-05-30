#include <iostream>
#include <vector>

typedef std::vector <std::vector<int>> Matrix;

std::vector <std::vector<int>> readInput(int n) {
    std::vector <std::vector<int>> matrix;
    for (int i = 0; i < n; i++) {
        std::vector<int> v;
        for (int j = 0; j < n; j++) {
            int a;
            std::cin >> a;
            v.push_back(a);
        }
        matrix.push_back(v);
    }
    return matrix;
}

void printMatrix(auto matrix) {
    for (auto m: matrix) {
        for (auto i: m) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

#include <set>

int nextVertex(const std::set<int> &visited, const std::vector<int> &spV) {
    int min = INT16_MAX + 1;
    int minElement = -1;
    for (int i = 0; i < spV.size(); ++i) {
        auto it = visited.find(i);
        if (spV[i] < min && it == visited.end()) {
            min = spV[i];
            minElement = i;
        }
    }
    return minElement;
}

int djikstras(const Matrix &matrix, int source, int final) {
    std::set<int> visited;
    std::vector<int> shortestPath(matrix.size(), INT16_MAX);
    shortestPath[source] = 0;

    for (int j = 0; j < matrix.size(); ++j) {
        int nextV = nextVertex(visited, shortestPath);
        visited.insert(nextV);
        for (int i = 0; i < matrix.size(); ++i) {
            if (matrix[nextV][i] == -1) {
                continue;
            }
            if (matrix[nextV][i] + shortestPath[nextV] < shortestPath[i]) {
                shortestPath[i] = matrix[nextV][i] + shortestPath[nextV];
            }
        }
    }
    return shortestPath[final];
}

int main() {
    int n, s, f;
    std::cin >> n >> s >> f;
    s -= 1;
    f -= 1;
    Matrix matrix = readInput(n);
    int answer = djikstras(matrix, s, f);
    if (answer == INT16_MAX) {
        std::cout << -1;
        return 0;
    }

    std::cout << answer << std::endl;
    return 0;
}
