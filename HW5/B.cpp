#include <iostream>
#include <vector>
#include <algorithm>

std::vector <std::vector<int>> readInput() {
    std::vector <std::vector<int>> matrix;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::vector<int> v;
        for (int j = 0; j < n; j++) {
            int a;
            std::cin >> a;
            if (a == -1) {
                a = INT16_MAX;
            }
            v.push_back(a);
        }
        matrix.push_back(v);
    }
    return matrix;
}

std::vector <std::vector<int>> floydWarshall(std::vector <std::vector<int>> &matrix) {
//    std::vector<std::vector<int>> matrixCopy = matrix;
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
    int max = -1;
    int rowMin = INT16_MAX;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            max = std::max(max, matrix[i][j]);
        }
        std::vector<int>::iterator result = std::max_element(matrix[i].begin(), matrix[i].end());
        rowMin = std::min(rowMin, *result);
    }
    std::cout << max << std::endl << rowMin << std::endl;
    return 0;
}
