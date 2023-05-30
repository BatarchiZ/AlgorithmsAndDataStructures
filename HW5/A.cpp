#include <iostream>
#include <vector>

std::vector <std::vector<int>> readInput() {
    std::vector <std::vector<int>> matrix;
    int n;
    std::cin >> n;
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

std::vector <std::vector<int>> floydWarshall(std::vector <std::vector<int>> &matrix) {
    for (int k = 0; k < matrix.size(); ++k) {
        for (int i = 0; i < matrix.size(); ++i) {
            if (i == k) {
                continue;
            }
            for (int j = 0; j < matrix.size(); ++j) {
                if (j == k) {
                    continue;
                }
                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }
    }
    return matrix;
}

void printMatrix(const std::vector <std::vector<int>> &matrix) {
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    std::vector <std::vector<int>> matrix = readInput();
    floydWarshall(matrix);
    printMatrix(matrix);
    return 0;
}
