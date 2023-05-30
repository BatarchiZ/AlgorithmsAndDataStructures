#include <iostream>
#include <string>
#include <vector>

typedef std::vector <std::vector<int>> Matrix;

Matrix takeInput() {
    int rows, columns;
    std::cin >> rows >> columns;
    std::string bin;
    getline(std::cin, bin);
    Matrix matrix;
    for (int i = 0; i < rows; i++) {
        std::vector<int> v;
        matrix.push_back(v);
        for (int j = 0; j < columns - 1; j++) {
            std::string dummy;
            getline(std::cin, dummy, ' ');
            matrix[i].push_back(std::stoi(dummy));
        }
        std::string dummy;
        getline(std::cin, dummy);
        matrix[i].push_back(std::stoi(dummy));
    }
    return matrix;
}

void makeCostsMatrix(Matrix &costsMatrix, Matrix origMatrix) {
    for (int k = 1; k < costsMatrix.size(); k++) {
        for (int l = 0; l < costsMatrix[0].size(); l++) {
            if (l == 0) {
                costsMatrix[k][l] = origMatrix[k][l] + std::min(costsMatrix[k - 1][l], costsMatrix[k - 1][l + 1]);
            }
            else if (l == costsMatrix[0].size() - 1) {
                costsMatrix[k][l] = origMatrix[k][l] + std::min(costsMatrix[k - 1][l], costsMatrix[k - 1][l - 1]);
            }
            else {
                costsMatrix[k][l] = origMatrix[k][l] + std::min(costsMatrix[k - 1][l],
                                                                std::min(costsMatrix[k - 1][l - 1],
                                                                         costsMatrix[k - 1][l + 1]));
            }
        }
    }
}


std::vector<int> backwardsTraverse(Matrix &costsMatrix, int j) {
    std::vector<int> vAns;
    vAns.push_back(j + 1);
    vAns.push_back(costsMatrix.size());
    for (int i = costsMatrix.size() - 2; i > -1; i--) {
        if (j != 0 && j != costsMatrix[0].size() - 1) {
            if (costsMatrix[i][j] < costsMatrix[i][j + 1] && costsMatrix[i][j] < costsMatrix[i][j - 1]) {}
            else if (costsMatrix[i][j + 1] < costsMatrix[i][j - 1]) { j = j + 1; }
            else { j = j - 1; }
            vAns.push_back(j + 1);
            vAns.push_back(i + 1);
        }
        else if (j == 0) {
            if (costsMatrix[i][j] < costsMatrix[i][j + 1]) {}
            else { j = j + 1; }
            vAns.push_back(j + 1);
            vAns.push_back(i + 1);
        }
        else {
            if (costsMatrix[i][j] < costsMatrix[i][j - 1]) {}
            else { j = j - 1; }
            vAns.push_back(j + 1);
            vAns.push_back(i + 1);
        }
    }
    return vAns;
}


int main() {
    Matrix matrix = takeInput();
    std::vector <std::pair<int, int>> path;
    std::vector<int> v(matrix[0].size(), 4394500);
    Matrix costsMatrix(matrix.size(), v);
    costsMatrix[0] = matrix[0];
    makeCostsMatrix(costsMatrix, matrix);
    int minVal = 4394500;
    int minIndex = 0;
    for (int j = 0; j < costsMatrix[costsMatrix.size() - 1].size(); j++) {
        if (minVal > costsMatrix[costsMatrix.size() - 1][j]) {
            minVal = costsMatrix[costsMatrix.size() - 1][j];
            minIndex = j;
        }
    }
    int j = minIndex;
    std::vector<int> vAns = backwardsTraverse(costsMatrix, j);
    std::cout << minVal << std::endl;
    for (int i = vAns.size() - 1; i > 0; i--) {
        std::cout << '(' << vAns[i] << ',' << vAns[--i] << ')' << ' ';
    }
    return 0;
}
