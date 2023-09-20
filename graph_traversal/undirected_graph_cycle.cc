#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

class Graph
{
    private:
        /* std::vector<std::list<int>> adj; */
        std::unordered_map<int, std::unordered_set<int>> adj;


    public:
        void add_edge(int u, int v)
        {
            assert(u >=0 && v >= 0);

            /* Multi-edge is disallowed! */
            if (u == v) return;
            adj[u].insert(v);
            adj[v].insert(u);

            return;
        }

        bool has_cycle()
        {
            std::unordered_set<int> visited;
            std::stack<int> vertex_stack;
            std::stack<int> parent_stack;

            int top_vertex;
            int parent_vertex;

            for (const auto& it: adj)
            {
                const int& v = it.first;

                /* Skip if the vertex v is already visited. */
                if (visited.end() != visited.find(v)) continue;

                vertex_stack.push(v);
                parent_stack.push(-1);

                visited.insert(v);

                while (!vertex_stack.empty())
                {
                    top_vertex = vertex_stack.top();
                    vertex_stack.pop();

                    parent_vertex = parent_stack.top();
                    parent_stack.pop();

                    for (const auto& neighbor: adj[top_vertex])
                    {
                        if (visited.end() != visited.find(neighbor) && parent_vertex != neighbor)
                        {
                            return true;
                        }

                        if (visited.end() != visited.find(neighbor)) continue;

                        visited.insert(neighbor);

                        vertex_stack.push(neighbor);
                        parent_stack.push(top_vertex);
                    }
                }
            }

            return false;
        }

        bool dfs_recur(int curr_vertex, std::unordered_map<int, std::unordered_set<int>>& adj,
                std::unordered_set<int>& visited, int parent_vertex)
        {
            for (const auto& neighbor : adj[curr_vertex])
            {
                if (visited.end() != visited.find(neighbor) && parent_vertex != curr_vertex)
                {
                    /* Find a back edge and it implies that cycle exists. */
                    return true;
                }

                if (visited.end() != visited.find(neighbor)) continue;

                visited.insert(neighbor);
                dfs_recur(neighbor, adj, visited, curr_vertex);
            }

            return false;
        }

        bool has_cycle_dfs()
        {
            std::unordered_set<int> visited;

            for (const auto& it: adj)
            {
                const auto curr_vertex = it.first;

                if (visited.end() != visited.find(curr_vertex)) continue;

                visited.insert(curr_vertex);
                if (dfs_recur(curr_vertex, adj, visited, -1)) return true;
            }

            return false;
        }
};


int
main(int argc, char** argv)
{
    Graph g;
    g.add_edge(0, 1);
    g.add_edge(0, 3);
    g.add_edge(0, 5);
    g.add_edge(1, 2);
    g.add_edge(3, 4);
    g.add_edge(1, 3);

    bool has_cycle_iter = g.has_cycle_dfs();
    bool has_cycle_recur = g.has_cycle();

    std::cout << "The graph has cycle? " << has_cycle_iter << std::endl;
    std::cout << "The graph has cycle? " << has_cycle_recur << std::endl;

    return 0;
}
