
#include <iostream>
#include <vector>
#include <algorithm>

int R;
int C;

std::vector <std::vector<int>> readInput() {
    std::vector <std::vector<int>> matrix;
    int r, c;
    std::cin >> r >> c;
    R = r;
    C = c;
    int num;
    for (int i = 0; i < r; ++i) {
        std::vector<int> temp;
        for (int j = 0; j < c; ++j) {
            std::cin >> num;
            temp.push_back(num);
        }
        matrix.push_back(temp);
    }
    return matrix;
}

void printMatrix(std::vector <std::vector<int>> &matrix) {
    for (auto i: matrix) {
        for (auto j: i) {
            std::cout << j << ' ';
        }
        std::cout << std::endl;
    }

}

#include <queue>


void
addToQueue(std::queue <std::pair<int, int>> &q, const int i, const int j,
           const std::vector <std::vector<int>> &matrix) {
    if (i - 1 > -1 && matrix[i - 1][j] == 0) {
        q.push(std::make_pair(i - 1, j));
    }
    if (i + 1 < matrix.size() && matrix[i + 1][j] == 0) {
        q.push(std::make_pair(i + 1, j));
    }
    if (j + 1 < matrix[i].size() && matrix[i][j + 1] == 0) {
        q.push(std::make_pair(i, j + 1));
    }
    if (j - 1 > -1 && matrix[i][j - 1] == 0) {
        q.push(std::make_pair(i, j - 1));
    }
}

int main() {
    std::vector <std::vector<int>> matrix = readInput();
    std::queue <std::pair<int, int>> q;
    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == 1) {
                addToQueue(q, i, j, matrix);
            }
        }
    }
    int d = 2;
    std::queue <std::pair<int, int>> q2;
    while (!q.empty()) {
//        if(q.empty())
//        {
//            break;
//        }
        std::pair<int, int> element = q.front();
        if (matrix[element.first][element.second] == 0) {
            addToQueue(q2, element.first, element.second, matrix);
            matrix[element.first][element.second] = d;
        }

        q.pop();
        if (q.empty()) {
            d++;
            std::swap(q, q2);
        }
    }
    for (auto &r: matrix) {
        for (auto &i: r) {
            i -= 1;
        }
    }
    printMatrix(matrix);
    return 0;
}