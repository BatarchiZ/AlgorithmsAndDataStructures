#include <iostream>
#include <vector>

int rows, columns;

typedef std::vector <std::vector<double>> Matrix;

void printMatrix(Matrix matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (const auto &column: matrix[i]) {
            std::cout << column << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void takeInput(Matrix &matrix, std::vector<int> &costs) {
    std::string dummy;
    getline(std::cin, dummy, ' ');
    rows = stoi(dummy);
    getline(std::cin, dummy);
    columns = stoi(dummy);
    for (int i = 0; i < rows; i++) {
        std::vector<double> vtemp;
        matrix.push_back(vtemp);
        for (int j = 0; j < columns; j++) {
            getline(std::cin, dummy, ' ');
            matrix[i].push_back(stoi(dummy));
        }
        getline(std::cin, dummy);
        costs.push_back(stoi(dummy));
    }
}


void reduceRow(Matrix &matrix, int column, int row, double coeffNumber, int pivotRow) {

    for (int j = 0; j < matrix[row].size(); j++) {
        matrix[row][j] -= matrix[pivotRow][j] * coeffNumber;
    }
}

#include <set>

int main() {
    std::vector <std::vector<double>> matrix;
    std::vector<int> costs;
    takeInput(matrix, costs);
    std::set<int> minRows;
    for (int j = 0; j < columns; j++) {
        int minCost = 100000000;
        int minRow = -1;
        double initcoeffNumber = 0.0;
        for (int i = 0; i < matrix.size(); i++) {
            auto it = minRows.find(i);
            if (matrix[i][j] != 0 && costs[i] < minCost && it == minRows.end()) {
                initcoeffNumber = matrix[i][j];
                minCost = costs[i];
                minRow = i;
            }
        }
        if (minRow == -1) {
            continue;
        }
        minRows.insert(minRow);
        for (int i = 0; i < matrix.size(); i++) {
            if (i == minRow) {
                continue;
            }
            else {
                double coeffNumber = matrix[i][j] / initcoeffNumber;
                reduceRow(matrix, j, i, coeffNumber, minRow);
            }
        }
    }
    if (minRows.size() < columns) {
        std::cout << -1;
        return 0;
    }
    for (auto el: minRows) {
        std::cout << el + 1 << ' ';
    }
    return 0;
}