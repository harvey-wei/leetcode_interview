#include <queue> // front is oldest.

using namespace std;
class MovingAverage {
    public:
        MovingAverage(int size)
        {
            this->size = size;
            acc_sum = 0;
        }

        double next(int val)
        {
            if (size == q.size())
            {
                // remove th oldest
                acc_sum -= q.front();
                q.pop();
            }

            // push val
            acc_sum += val;
            q.push(val);

            return static_cast<double>(acc_sum) / static_cast<double>(q.size());

        }
    private:
        int size;
        queue<int> q;
        int acc_sum;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */
