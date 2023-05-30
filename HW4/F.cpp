#include <iostream>
#include <vector>
#include <string>

void printMatrix(std::vector <std::vector<int>> &matrix) {
    for (auto i: matrix) {
        for (auto j: i) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}

void helpFunc(int &i1, int &j1, std::string str) {
    if (str[0] == 'a') {
        j1 = 0;
    }
    else if (str[0] == 'b') {
        j1 = 1;
    }
    else if (str[0] == 'c') {
        j1 = 2;
    }
    else if (str[0] == 'd') {
        j1 = 3;
    }
    else if (str[0] == 'e') {
        j1 = 4;
    }
    else if (str[0] == 'f') {
        j1 = 5;
    }
    else if (str[0] == 'g') {
        j1 = 6;
    }
    else if (str[0] == 'h') {
        j1 = 7;
    }
    i1 = (str[1] - '0') - 1;
}


#include <queue>

void processFront(std::queue <std::pair<int, int>> &q, const std::vector <std::vector<int>> &matrix,
                  const std::pair<int, int> &front) {
    int i = front.first;
    int j = front.second;
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

bool dfs(std::vector <std::vector<int>> &matrix, int R1, int C1) {
    std::queue <std::pair<int, int>> q;
    std::queue <std::pair<int, int>> q2;
    q.push(std::make_pair(R1, C1));
    int d = 1;
    while (!q.empty()) {
        if (matrix[q.front().first][q.front().second] == 0) {
            processFront(q2, matrix, q.front());
        }
        matrix[q.front().first][q.front().second] = d;
        q.pop();
        if (q.empty()) {
            d++;
            std::swap(q, q2);
        }
    }
    return false;
}


void readInput(int &i1, int &j1, int &i2, int &j2) {
    std::string str;
    getline(std::cin, str, ' ');
    helpFunc(i1, j1, str);
    getline(std::cin, str);
    helpFunc(i2, j2, str);
}

int main() {
    int i1, i2, j1, j2;
    readInput(i1, j1, i2, j2);
    std::vector<int> v(8, 0);
    std::vector <std::vector<int>> matrix(8, v);
    dfs(matrix, i1, j1);
    std::vector <std::vector<int>> matrix2(8, v);
    dfs(matrix2, i2, j2);

    int minN = INT16_MAX;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == matrix2[i][j]) {
                if (matrix[i][j] - 1 < minN) {
                    minN = matrix[i][j] - 1;
                }
            }

        }
    }
    if (minN == INT16_MAX) {
        std::cout << -1;
    }
    else {
        std::cout << minN;
    }
    return 0;
}