#include <iostream>
#include <vector>
#include <unordered_map>


int takeInput(int n, std::unordered_map<int, int> &scoreIndexMap) {
    std::vector<int> inputV;
    int number;
    for (int i = 0; i < n; i++) //O(n)
    {
        std::cin >> number;
        inputV.push_back(number);
    }
    int index1;
    int index2;
    std::cin >> index1 >> index2;
    for (int i = 0; i < n; i++) //O(n)
    {
        if (i != index1 && i != index2) {
            scoreIndexMap[inputV[i]] = i;
        }
    }
    return (inputV[index1] + inputV[index2]);
}


int main() {
    int cycles;
    std::cin >> cycles;
    std::vector<int> inputV;

    std::unordered_map<int, int> scoreIndexMap;
    int desN = takeInput(cycles, scoreIndexMap);
    for (std::pair<int, int> p: scoreIndexMap) //O(n)
    {
        auto it = scoreIndexMap.find(desN - p.first); //Constant complexity in unordered_map;
        if (it != scoreIndexMap.end()) {
            std::cout << std::min(scoreIndexMap[it->first], scoreIndexMap[p.first]) << ' '
                      << std::max(scoreIndexMap[it->first], scoreIndexMap[p.first]);
            return 0;
        }
    }
    return 0;
}
//Complexity is O(3n) I think adfasdsdas