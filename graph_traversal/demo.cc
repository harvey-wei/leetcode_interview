#include <iostream>
#include <list>
#include <vector>
#include <cassert>

class Graph
{
    private:
        int num_of_verticies;

        /* Adjacency list is defined as array of list of vertex index. */
        /* Or use hash_map to map vertext to the vector of its neighbors. */
        /* Actually directed graph. */
        std::list<int>* adj_list;

    public:
        Graph(int _num_of_verticies)
            :num_of_verticies(_num_of_verticies)
        {
            adj_list = new std::list<int>[_num_of_verticies];
        }

        void add_edge(int v, int w)
        {
            assert(v < num_of_verticies);
            assert(w < num_of_verticies);

            (adj_list + v)->push_back(w);
        }

        ~Graph()
        {
            delete [] adj_list;
        }

        void explore(int v, std::vector<int>& path);
        void explore_helper(int v, std::vector<bool>& is_visited, std::vector<int>& path);

        void dfs_recur();

        void dfs_iter();
};

void Graph::explore_helper(int v, std::vector<bool>& is_visited, std::vector<int>& path)
{
    if (!is_visited[v])
    {
        is_visited[v] = true;
        path.push_back(std::move(v));

        for (const auto& neighbor: *(adj_list + v))
        {
            if (!is_visited[neighbor])
            {
                explore_helper(neighbor, is_visited, path);
            }
        }

    }
    else
    {
        return;
    }
}

void Graph::explore(int v, std::vector<int>& path)
{
    assert(v < num_of_verticies);
    std::vector<bool> is_visited(num_of_verticies, false);
    explore_helper(v, is_visited, path);
}

void print_vec(std::vector<int>& vec)
{
    for (const auto& ele: vec)
    {
        std::cout << " " << ele;
    }

    std::cout << std::endl;
}

int main()
{
    Graph g(6);
    g.add_edge(0, 1);
    g.add_edge(1, 0);
    g.add_edge(0, 2);
    g.add_edge(2, 0);
    g.add_edge(1, 2);
    g.add_edge(2, 1);
    g.add_edge(2, 3);
    g.add_edge(3, 2);
    g.add_edge(4, 5);
    g.add_edge(5, 4);

    std::vector<int> path;
    g.explore(0, path);
    print_vec(path);

    return 0;
}
