#include <iostream>
#include <vector>

typedef std::vector <std::vector<int>> Matrix;

void takeInput(std::vector <std::vector<int>> &matrix) {
    int rows, columns;
    std::cin >> rows >> columns;
    std::string dummy;
    getline(std::cin, dummy);
    for (int i = 0; i < rows; i++) {
        std::vector<int> v;
        matrix.push_back(v);
        std::string str;
        getline(std::cin, str);
        for (int j = 0; j < columns; j++) {
            int k = str[j] - '0';
            matrix[i].push_back(k);
        }
    }
}

void foundZero(Matrix &matrix, int &maxN, int i, int j) {
    int upperBoundColumns = matrix[0].size();
    for (int c1 = 0; i + c1 < matrix.size(); c1++) {
        if (matrix[i + c1][j]) {
            break;
        }
        for (int c2 = 0; j + c2 < upperBoundColumns; c2++) {
            if (matrix[i + c1][j + c2] == 0) {
                maxN = std::max(maxN, (c1 + 1) * (c2 + 1));
            }
            else {
                upperBoundColumns = j + c2;
                break;
            }
        }
    }
}

int main() {
    std::vector <std::vector<int>> matrix;
    takeInput(matrix);
    int maxN = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (!matrix[i][j]) {
                foundZero(matrix, maxN, i, j);
            }
        }
    }
    std::cout << maxN;
    return 0;
}
