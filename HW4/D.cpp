#include <iostream>
#include <vector>

void printMatrix(std::vector <std::vector<int>> &matrix) {
    for (auto i: matrix) {
        for (auto j: i) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

int R1, C1, R2, C2;

std::vector <std::vector<int>> readInput() {
    int r, c, j, i, m, s;
    std::cin >> r >> c >> j >> i >> m >> s;
    j -= 1;
    i -= 1;
    m -= 1;
    s -= 1;

    R1 = j;
    C1 = i;
    R2 = m;
    C2 = s;
    std::vector <std::vector<int>> matrix;
    for (int rows = 0; rows < r; ++rows) {
        std::vector<int> temp;
        for (int columns = 0; columns < c; ++columns) {
            temp.push_back(0);
        }
        matrix.push_back(temp);
    }
    matrix[j][i] = 1;
    matrix[m][s] = -1;
    return matrix;
}

#include <queue>

bool checker = false;

void processFront(std::queue <std::pair<int, int>> &q, const std::vector <std::vector<int>> &matrix) {
    std::pair<int, int> front = q.front();
    int i = front.first;
    int j = front.second;
    if ((i - 2 > -1 && j - 1 > -1 && matrix[i - 2][j - 1] == -1) ||
        (i - 2 > -1 && j + 1 < matrix[i].size() && matrix[i - 2][j + 1] == -1) ||
        (i + 2 < matrix.size() && j - 1 > -1 && matrix[i + 2][j - 1] == -1) ||
        (i + 2 < matrix.size() && j + 1 < matrix[i].size() && matrix[i + 2][j + 1] == -1) ||
        (i + 1 < matrix.size() && j - 2 > -1 && matrix[i + 1][j - 2] == -1) ||
        (i - 1 > -1 && j - 2 > -1 && matrix[i - 1][j - 2] == -1) ||
        (i + 1 < matrix.size() && j + 2 < matrix[i].size() && matrix[i + 1][j + 2] == -1) ||
        (i - 1 > -1 && j + 2 < matrix[i].size() && matrix[i - 1][j + 2] == -1)) {
        checker = true;
        return;
    }

    if (i - 2 > -1 && j - 1 > -1 && matrix[i - 2][j - 1] == 0) { q.push(std::make_pair(i - 2, j - 1)); }
    if (i - 2 > -1 && j + 1 < matrix[i].size() && matrix[i - 2][j + 1] == 0) { q.push(std::make_pair(i - 2, j + 1)); }
    if (i + 2 < matrix.size() && j - 1 > -1 && matrix[i + 2][j - 1] == 0) { q.push(std::make_pair(i + 2, j - 1)); }
    if (i + 2 < matrix.size() && j + 1 < matrix[i].size() && matrix[i + 2][j + 1] == 0) {
        q.push(std::make_pair(i + 2, j + 1));
    }
    if (i + 1 < matrix.size() && j - 2 > -1 && matrix[i + 1][j - 2] == 0) { q.push(std::make_pair(i + 1, j - 2)); }
    if (i - 1 > -1 && j - 2 > -1 && matrix[i - 1][j - 2] == 0) { q.push(std::make_pair(i - 1, j - 2)); }
    if (i + 1 < matrix.size() && j + 2 < matrix[i].size() && matrix[i + 1][j + 2] == 0) {
        q.push(std::make_pair(i + 1, j + 2));
    }
    if (i - 1 > -1 && j + 2 < matrix[i].size() && matrix[i - 1][j + 2] == 0) { q.push(std::make_pair(i - 1, j + 2)); }
}

bool dfs(std::vector <std::vector<int>> &matrix) {
    std::queue <std::pair<int, int>> q;
    q.push(std::make_pair(R1, C1));
    matrix[q.front().first][q.front().second] = 0;
    while (!q.empty()) {
        if (matrix[q.front().first][q.front().second] == 0) {
            processFront(q, matrix);
        }
        if (checker) {
            return true;
        }
        matrix[q.front().first][q.front().second] = 1;
        q.pop();
    }
    return false;
}

int main() {
    std::vector <std::vector<int>> matrix = readInput();
    if (dfs(matrix)) {
        std::cout << "YES";
        return 0;
    }
    std::cout << "NO";
    return 0;
}
// 8 8 1 1 7 8