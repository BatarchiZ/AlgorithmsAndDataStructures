#include <iostream>
#include <vector>
#include <tuple>

std::vector <std::vector<int>> readInput(int n, int m) {
    std::vector<int> v(m, -1);
    std::vector <std::vector<int>> matrix(n, v);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    return matrix;
}

void printMatrix(const auto &matrix) {
    for (auto m: matrix) {
        for (auto i: m) {
            std::cout << i << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

#include <queue>
#include <string>

int rows;
int columns;
int end_row;
int end_col;

bool checkValid(const int r0, const int c0, int orientation, int &cNew, int &rNew) {
    cNew = c0;
    rNew = r0;
    if (orientation == 0) {
        rNew -= 1;
        if (rNew < 0) {
            return false;
        }
        return true;
    }
    else if (orientation == 1) {
        cNew += 1;
        if (cNew > columns) {
            return false;
        }
        return true;
    }
    else if (orientation == 2) {
        rNew += 1;
        if (rNew > rows) {
            return false;
        }
        return true;
    }
    else if (orientation == 3) {
        cNew -= 1;
        if (cNew < 0) {
            return false;
        }
        return true;
    }
}

int BFS(std::vector <std::vector<int>> &matrix, int r1, int c1, int r2, int c2) {
    std::queue <std::tuple<int, int, int>> q;
    q.push(std::make_tuple(r1, c1, 0));
    matrix[r1][c1] = 2;
    while (!q.empty()) {
        int r = std::get<0>(q.front());
        int c = std::get<1>(q.front());
        int rNew, cNew;
        if (r == r2 && c == c2) {
            return std::get<2>(q.front());
        }
        for (int i = 0; i < 4; i++) {
            if (checkValid(r, c, i, cNew, rNew)) {
                if (matrix[rNew][cNew] < 1) {
                    matrix[rNew][cNew] = 2;
                    q.push(std::make_tuple(rNew, cNew, std::get<2>(q.front()) + 1));
                }
            }
        }
        q.pop();
    }
    return -1;
}

int main() {
    int n, m;
    std::cin >> n >> m;
    rows = n - 1;
    columns = m - 1;
    std::vector <std::vector<int>> matrix = readInput(n, m);
    int c1, r1, c2, r2;
    std::cin >> c1 >> r1 >> c2 >> r2;
    c1--;
    c2--;
    r1--;
    r2--;
    end_row = r2;
    end_col = c2;
    /// Start is c1,r1
    std::cout << BFS(matrix, r1, c1, r2, c2);
    return 0;
}