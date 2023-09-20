#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <list>
#include <stack>
#include <queue>

/* class Vertex */
/* { */
/*     int id; */
/**/
/*     int key; */
/**/
    /* Parameterized constructor. */
/*     Vertex(int _id, int _key) */
/*         : id(_id), key(_key) */
/*     {} */
/**/
    /* Copy constructor */
/*     Vertex(const Vertex& rhs) */
/*     { */
/*         id = rhs.id; */
/*         key = rhs.key; */
/*     } */
/* }; */

class Graph
{
    private:
        int vertex_cnt;

        /* Pointer to the array of list of adjacent vertices. */
        std::list<int>* adj;

    public:
        Graph(int _vertex_cnt)
            : vertex_cnt(_vertex_cnt)
        {
            adj = new std::list<int>[vertex_cnt];
        }

        ~Graph()
        {
            delete [] adj;
        }

        /**
         * \brief Add a directed edge src -> dst.
         * \note Vertex index is zero-based.
         *       Graph is directed.
         */
        void add_edge(int src, int dst)
        {
            (adj + src)->push_back(dst);

            return;
        }

        /* What if the graph is empty? */
        void explore_recur_helper(const int& s);
        void explore_recur(const int& s, std::unordered_set<int>& visisted); // DFS

        void explore_dfs(const int& s);

        void explore_bfs(const int& s);

        void traverse_recur();

        void traverse_dfs();

        void traverse_bfs();

        /* ref: https://kaixih.github.io/topo-sort/ */
        void topo_sort(std::vector<int>& linear_order);
};


void
Graph::traverse_recur()
{
    return;
}

void
Graph::explore_recur_helper(const int& s)
{
    std::unordered_set<int> visisted;

    std::cout << "vertex: " << s << std::endl;

    visisted.insert(s);

    explore_recur(s, visisted);

    return;
}

void
Graph::explore_recur(const int& s, std::unordered_set<int>& visisted)
{
    /* Iterate over all the neighbors of s*/
    for (const auto& v: *(adj + s))
    {
        if (visisted.end() == visisted.find(v))
        {
            // preorder
            std::cout << "vertex: " << v << std::endl;

            visisted.insert(v);

            explore_recur(v, visisted);
        }
    }

    return;
}

/*
 * \Complexity Analysis.
 * Every vertex is pushed and poped only once! -> O(|V|)
 * Each edge is checked twice! -> O(|E|)
 * Time Complexity: O(|E| + |V|)
 *
 * stack and visisted store vertices.
 * Space Complexity: O(|V|)
 */
void
Graph::explore_dfs(const int& s)
{
    std::stack<int> stack_vertices;
    std::unordered_set<int> visisted;

    stack_vertices.push(s);

    visisted.insert(s);

    int curr_vertex;
    while (!stack_vertices.empty())
    {
        /* Pop and push all its unvisited neighbors. */
        curr_vertex = stack_vertices.top();
        stack_vertices.pop();

        std::cout << "vertex: " << curr_vertex << std::endl;

        for (const auto& neighbor: *(adj + curr_vertex))
        {
            if (visisted.end() == visisted.find(neighbor))
            {
                visisted.insert(neighbor);
                stack_vertices.push(neighbor);
            }
        }
    }
}

void
Graph::explore_bfs(const int& s)
{
    std::queue<int> queue_vertices;
    std::unordered_set<int> visisted;

    int curr_vertex;

    queue_vertices.push(s);
    visisted.insert(s);

    while (!queue_vertices.empty())
    {
        curr_vertex = queue_vertices.front();
        queue_vertices.pop();

        std::cout << "vertex: " << curr_vertex << std::endl;

        for (const auto& neighbor: *(adj + curr_vertex))
        {
            if (visisted.end() == visisted.find(neighbor))
            {
                visisted.insert(neighbor);

                queue_vertices.push(neighbor);
            }
        }
    }
}

/*
 * \ref https://www.techiedelight.com/graph-implementation-c-without-using-stl/
 */

int
main(int argc, char** argv)
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

    std::cout << "Reachable from 0" << std::endl;
    /* g.explore_recur_helper(0); */
    g.explore_dfs(0);

    std::cout << "Reachable from 0" << std::endl;
    g.explore_bfs(0);


    std::cout << "Reachable from 4" << std::endl;
    g.explore_recur_helper(4);



    return 0;
}
