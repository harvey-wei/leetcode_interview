#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>


int SumDist(const std::vector<std::vector<int>>& edges, const int& target)
{
    if (edges.size() == 0) return 0;

    int sum = 0;

    std::unordered_map<int, std::vector<int>> adj_list;

    // Convert Edge List to Adjacency List fo quick neighbor query
    for (const auto& e : edges)
    {
        adj_list[e[0]].push_back(e[1]);
        adj_list[e[1]].push_back(e[0]);
    }

    std::unordered_set<int> visited;

    int curr_level = 0;
    int curr_node;

    int curr_node_cnt = 0;
    int next_node_cnt = 0;

    std::queue<int> node_q;
    node_q.push(target);
    visited.insert(target);
    ++curr_node_cnt;

    while (!node_q.empty())
    {
        curr_node = node_q.front();
        node_q.pop();
        --curr_node_cnt;



        for (const auto& neighbor : adj_list[curr_node])
        {
            if (visited.end() != visited.find(neighbor)) continue;

            node_q.push(neighbor);
            sum += curr_level;
            visited.insert(neighbor);
            ++next_node_cnt;
        }

        if (0 == curr_node_cnt)
        {
            curr_node_cnt = next_node_cnt;
            next_node_cnt = 0;
            ++curr_level;
        }
    }

    return sum;
}

int
main(int argc, char** argv)
{
    std::vector<std::vector<int>> edges = {{0, 1}, {2, 1}, {2, 3}, {2, 4}};
    int target = 2;

    std::cout << "SumDist: " << SumDist(edges, target);

    return 0;
}
