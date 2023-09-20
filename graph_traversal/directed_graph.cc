#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>

class DirectedGraph
{
    private:
        std::vector<std::vector<int>>  adj;
        std::vector<std::vector<int>>  reverse_adj;


    public:
        void data_reader()
        {
            size_t n, m; // n vertices and m edges
            std::cin >> n >> m;

            adj.resize(n);
            reverse_adj.resize(n);

            // one line for onne edge in std::cin
            for (size_t i = 0; i < m; ++i)
            {
                int s, d; // 1-based vertex indexing

                std::cin >> s >> d;
                adj[s - 1].push_back(d - 1);
                reverse_adj[d - 1].push_back(s - 1);
            }
            return;
        }

        void explore(int v, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited,
                std::stack<int>& post_order)
        {
            /* Start exploring all descendants of vertex v. */
            for (const auto& neighbor : adj[v])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    explore(neighbor, adj, visited, post_order);
                }
            }

            /* Finish exploring all descendants of vertex v. */
            post_order.push(v);
        }

        void dfs_recur(const std::vector<std::vector<int>>& adj, std::stack<int>& post_order)
        {
            std::vector<bool> visited(adj.size(), false);

            for (int v = 0; v < adj.size(); ++v)
            {
                if (!visited[v])
                {
                    visited[v] = true;
                    explore(v, adj, visited, post_order);
                }
            }

            return;
        }


        void find_scc()
        {

            return;
        }
};

int
main(int argc, char** argv)
{
    return 0;
}
