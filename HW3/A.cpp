#include <iostream>
#include <vector>

int indexGlob = 0;

std::vector <std::vector<int>> readInput() {
    std::vector <std::vector<int>> matrix;
    int n, s;
    std::cin >> n >> s;
    indexGlob = s - 1;
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

void dfs(std::vector<bool> &visited, const std::vector <std::vector<int>> &matrix, int index) {
    for (int i = 0; i < visited.size(); i++) {
        if (matrix[index][i] == 1 && !visited[i]) {
            visited[i] = true;
            dfs(visited, matrix, i);
        }
    }
}

int main() {
    std::vector <std::vector<int>> inpMatrix = readInput();
    std::vector<bool> visited(inpMatrix.size(), false);
    visited[indexGlob] = true;
    dfs(visited, inpMatrix, indexGlob);
    int counter = 0;
    for (auto v: visited) {
        if (v == 1) {
            counter++;
        }
    }
    std::cout << counter << std::endl;
    return 0;
}
//8 3
//0 1 0 0 0 0 0 0
//1 0 1 0 0 0 0 0
//0 1 0 1 0 0 0 0
//0 0 1 0 0 0 0 0
//0 0 0 0 0 1 1 0
//0 0 0 0 1 0 1 0
//0 0 0 0 1 1 0 1
//0 0 0 0 0 0 1 0
