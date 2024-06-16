#include <queue> // front is the oldest one

using namespace std;

class RecentCounter
{
public:
    RecentCounter()
    {
    }

    int ping(int t)
    {
        /* It is guaranteed that every call to pint use a strictly larger value of ti than
         * the previous call.
         * That is, front is always smaller than back in the queue.
         */
        int l = t - 3000;

        while (!t_q.empty() && t_q.front() < l)
        {
            t_q.pop();
        }

        t_q.push(t);

        return t_q.size();
    }

private:
    queue<int> t_q;

};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */
