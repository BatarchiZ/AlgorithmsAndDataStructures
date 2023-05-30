#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <unordered_set>

struct Node
{
    std::unordered_map<size_t, std::set<Node *>> map;
    size_t index;
};

std::vector<std::pair<int,std::pair<int,int>>> readInput()
{
    size_t n, e, k;
    std::cin >> n >> e >> k;
    std::vector<std::pair<int,std::pair<int,int>>> corridors;
    for (int i = 0; i < e; i++)
    {
        size_t x, y, z;
        std::cin >> x >> y >> z;
        corridors.emplace_back(x, std::make_pair(y,z));
    }
    return corridors;
}

std::unordered_set<int> search(const std::vector<std::pair<int,std::pair<int,int>>>& corridors,
                               const std::vector<int>& instructionV, int source)
{
        std::unordered_set<int> positions;
        positions.insert(source);
        for(int i = 0; i < instructionV.size(); ++i)
        {
            int curColour = instructionV[i];
            std::unordered_set<int> positionsCurStep;
            for(int j = 0; j < corridors.size(); ++j)
            {
                if(positions.find(corridors[j].first)!= positions.end() && curColour == corridors[j].second.second)
                positionsCurStep.insert(corridors[j].second.first);
            }
            positions = positionsCurStep;
        }
    return positions;
}

int main()
{
    std::vector<std::pair<int,std::pair<int,int>>> corridors = readInput();
    int instructions, inst;
    std::cin >> instructions;
    std::vector<int> instructionV;
    for (int i = 0; i < instructions; i++)
    {
        std::cin >> inst;
        instructionV.push_back(inst);
    }

    int source;
    std::cin >> source;
    std::unordered_set<int> finalRooms = search(corridors, instructionV, source);
    if (finalRooms.empty())
    {
        std::cout << "Hangs";
        return 0;
    }
    std::cout << "OK" << std::endl;
    std::cout << finalRooms.size() << std::endl;
    std::vector<int> finRooms;
    for (auto s: finalRooms)
    {
        finRooms.push_back(s);
    }
    std::sort(finRooms.begin(), finRooms.end());
    for(auto i : finRooms)
        std::cout << i << ' ';
    return 0;
}