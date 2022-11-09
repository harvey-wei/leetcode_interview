#include <iostream>
#include <queue>  // front means oldest while back means newest
#include <vector>
using namespace std;

class MovingAverage {
private:
    queue<int> q;
    long int s;
    int win_size;
public:
    MovingAverage(int size) {
        win_size = size;
        s = 0;
    }

    double next(int val)
    {
        /* double avg = 0.0; */
        /* if (win_size == q.size()) */
        /* { */
        /*     int front = q.front(); */
        /*     q.pop(); */
        /*     q.push(val); */
        /*     s = s - front + val; */
        /**/
        /*     avg = (double) (s) / (double) (q.size()); */
        /* } */
        /* else */
        /* { */
        /*     s += val; */
        /*     q.push(val); */
        /*     avg = (double) (s) / (double) (q.size()); */
        /* } */

        /* optimze after passing all test cases.
           Don't do early non-asymptotic optimization!
        */

        double avg = 0.0;
        s += val;

        if (win_size == q.size())
        {
            int front = q.front();
            s -= front;
            q.pop();
        }

        q.push(val);

        avg = (double) (s) / (double) (q.size());

        return avg;
    }
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */

int main()
{
    return 0;
}
