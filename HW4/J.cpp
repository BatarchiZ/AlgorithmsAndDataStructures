#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

std::vector<std::vector<std::pair<size_t, bool>>>readInput()
{
    size_t cities, roads;
    std::cin >> cities >> roads;
    std::vector<int> barons(cities);
    for (size_t i = 0; i < cities; ++i)
    {
        std::cin >> barons[i];
    }
    std::vector<std::vector<std::pair<size_t, bool>>> adjList(cities);
    for (size_t i = 0; i < roads; ++i)
    {
        size_t a, b;
        std::cin >> a >> b;
        adjList[a - 1].emplace_back(std::make_pair(b - 1, barons[a - 1] != barons[b - 1]));
        adjList[b - 1].emplace_back(std::make_pair(a - 1, barons[a - 1] != barons[b - 1]));
    }
    return adjList;
}

#include <queue>

int djikstras(const std::vector<std::vector<std::pair<size_t, bool>>> &adjList, int source, int final,
              std::vector<int> &prev)
{
//    std::vector<bool> visited(adjList.size(), false);
    std::vector<int> shortestPath(adjList.size(), INT16_MAX);
    shortestPath[source] = 0;
    prev[source] = source;

    std::queue<std::pair<size_t, std::vector<std::pair<size_t, bool>>>> q;
    q.push(std::make_pair(0, adjList[source]));

    while (!q.empty())
    {
        std::pair<size_t, std::vector<std::pair<size_t, bool>>> curIsland = q.front();
        q.pop();
        int curIndex = curIsland.first;
        for (const std::pair<size_t, bool>& road: curIsland.second)
        {
            size_t dest = road.first;
            bool price = road.second;
            if (shortestPath[dest] > shortestPath[curIndex] + price)
            {
                shortestPath[dest] = shortestPath[curIndex] + price;
                q.push(std::make_pair(dest, adjList[dest]));
                prev[dest] = curIndex;
            }
        }
    }
    return shortestPath[final];
}


int main()
{
    std::vector<std::vector<std::pair<size_t, bool>>> adjList = readInput();
    std::vector<int> prev(adjList.size(), -1);
    int answer = djikstras(adjList, 0, adjList.size() - 1, prev);

    if (answer == INT16_MAX)
    {
        std::cout << "impossible";
        return 0;
    }
    int j = adjList.size() - 1;
    std::vector<int> answerV;
    while (j != 0)
    {
        answerV.push_back(j + 1);
        j = prev[j];
    }
    answerV.push_back(j + 1);
    std::cout << answer << ' ' << answerV.size() << std::endl;
    for (int & i : std::ranges::reverse_view(answerV))
    {
        std::cout << i << ' ';
    }
    return 0;
}