#include <vector>
#include <queue>
#include <stack>
using namespace std;

/* ref : https://leetcode.com/problems/course-schedule/editorial/ */
class Solution {
public:
    /**
     * Kahn's Algorithm. Start with the zero-in_degree vertex and decrement the in-degree of its
     * neighbor recursively.
     * enqueue the zero-indegree of vertex and  do BFS
     * Time Complexity: O(|E| + |V|)
     * Space Complexity: O(|E| + |V|)
     */
    bool canFinish_kahn(int numCourses, vector<vector<int>>& prerequisites)
    {
        /**
         * Index acts as the vertex ID. Courseras are labeled from 0 to numCourses - 1.
         */
        vector<int> in_degrees(numCourses, 0);   // O(|V|)
        vector<vector<int>> adj(numCourses); // O(|V| + |E|)

        // O(|V|) for time
        for (const auto& prerequisite : prerequisites)
        {
            /* prerequisite[0] depends on prerequisite[1] */
            adj[prerequisite[1]].push_back(prerequisite[0]);
            ++in_degrees[prerequisite[0]];
        }

        queue<int> zero_in_vertex;

        for (int i = 0; i < numCourses; ++i)
        {
            if (0 == in_degrees[i])
            {
                zero_in_vertex.push(i);
            }
        }

        int zero_in_cnt =  zero_in_vertex.size();

        /*
         * Each vertex is pushed and popped at most once. O(|V|)
         */
        int curr_vertex;
        while (!zero_in_vertex.empty())
        {
            curr_vertex = zero_in_vertex.front();
            zero_in_vertex.pop();

            /* Each edge is checked once. O(|E|)*/
            for (const auto& neighbor : adj[curr_vertex])
            {
                /* Delete the current vertex and decrement the in_degrees of its neighbors. */
                --in_degrees[neighbor];
                if (0 == in_degrees[neighbor])
                {
                    ++zero_in_cnt;
                    zero_in_vertex.push(neighbor);
                }
            }
        }

        /* Is a topological sort exists for the current directed graph. */
        return zero_in_cnt == numCourses;
    }


    bool explore_recur(int curr_vertex, const vector<vector<int>>& adj, vector<bool>& in_recur,
            vector<bool>& visited)
    {
        /* check status */
        if (in_recur[curr_vertex]) return true;  // in recursion stack we have a cycle

        if (visited[curr_vertex]) return false; // finish traversing all its reachable descendants.

        /* update status and perform recursion. */
        in_recur[curr_vertex] = true;

        for (const auto& neighbor : adj[curr_vertex])
        {
            if (explore_recur(neighbor, adj, in_recur, visited)) return true;
        }

        in_recur[curr_vertex] = false; visited[curr_vertex] = true;

        return false;
    }
    /**
     * We differentiate the vertex in the recursion stack, unvisited vertex, visited vertex popped
     * out of the recursion stack.
     * Each vertex can only have one of the following status:
     * 1. In recursion stack.
     * 2. Visited but not in the recursion stack.
     * A node remains in the DFS recursion stack until all of its branches
     * (all nodes in its subtree) have been explored.
     */
    bool canFinish_dfs_recur(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<vector<int>> adj(numCourses); // O(|V| + |E|)

        // O(|V|) for time
        for (const auto& prerequisite : prerequisites)
        {
            /* prerequisite[0] depends on prerequisite[1] */
            adj[prerequisite[1]].push_back(prerequisite[0]);
        }

        std::vector<bool> in_recur(numCourses, false);
        std::vector<bool> visited(numCourses, false);

        for (int curr_vertex = 0; curr_vertex < numCourses; ++curr_vertex)
        {
            /* explore from curr_vertex and check status of vertex at the start of the explore_recur */
            if (explore_recur(curr_vertex, adj, in_recur, visited)) return false;
        }

        /* No cycle */
        return true;
    }

    enum VertexState {UNVISITED, VISITING, VISITED};
    enum StackSate {ENTER, EXIT, NONE};

    bool explore_iter_(const int& curr_vertex, std::vector<VertexState>& vertex_states,
            std::vector<StackSate>& stack_states, std::vector<vector<int>>& adj)
    {
        std::stack<int> v_stack;

        /* All vertices start UNVISITED and NONE. */
        if (UNVISITED == vertex_states[curr_vertex])
        {
            v_stack.push(curr_vertex);
            stack_states[curr_vertex] = ENTER;
        }

        while (!v_stack.empty())
        {
            auto top_v = v_stack.top();
            v_stack.pop();

            /* update vertex status when popped out. */

            /* Check and update the status of the top vertex. */
            if (EXIT == stack_states[top_v])
            {
                vertex_states[top_v] = VISITED;
            }
            else
            {
                v_stack.push(top_v);
                stack_states[top_v] = EXIT;
                vertex_states[top_v] = VISITING;

                for (const auto& neighbor : adj[top_v])
                {
                    if (NONE == stack_states[neighbor])
                    {
                        v_stack.push(neighbor);
                        stack_states[neighbor] = ENTER;
                    }
                    else if (VISITING == vertex_states[neighbor])
                    {
                        /* A back edge is found which means a cycle exists. */
                        return true;
                    }
                    else
                    {
                        /* DO NOTHING if VISITED. */
                    }
                }
            }

        }

        return false;
    }

    bool canFinish_(int numCourses, vector<vector<int>>& prerequisites)
    {
        vector<vector<int>> adj(numCourses); // O(|V| + |E|)

        // O(|V|) for time
        for (const auto& prerequisite : prerequisites)
        {
            /* prerequisite[0] depends on prerequisite[1] */
            adj[prerequisite[1]].push_back(prerequisite[0]);
        }

        std::vector<VertexState> vertex_states(numCourses, UNVISITED);
        std::vector<StackSate> stack_states(numCourses, NONE);

        for (int curr_vertex = 0; curr_vertex < numCourses; ++curr_vertex)
        {
            /* explore from curr_vertex and check status of vertex at the start of the explore_recur */
            /* if (explore_recur(curr_vertex, adj, in_recur, visited)) return false; */
            if (explore_iter_(curr_vertex, vertex_states, stack_states ,adj)) return false;
        }

        /* No cycle */
        return true;
    }

};

int
main(int argc, char** argv)
{
    return 0;
}
