#include <iostream>
#include <vector>
#include <stack>
using namespace std;


class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures)
    {
        /*
           Monotonic stacks are a good option when a problem involves comparing the size of
           numeric elements, with their order being relevant.

           Since we need find the most recent day when the temperature is higher than the current.
           And need to main the descending order.
        */
        vector<int> result(temperatures.size(), 0);
        stack<int> stack_idx;

        for (int i = 0; i < temperatures.size(); ++i)
        {
            /* pop until current is smaller than the top. */
            while (!stack_idx.empty() && temperatures[stack_idx.top()] < temperatures[i])
            {
                /* Pop out the idx for which the number of waiting days is found. */
                result[stack_idx.top()] = i - stack_idx.top();
                stack_idx.pop();
            }

            /* then push */
            stack_idx.push(std::move(i));
        }

        return result;
    }
};

int main()
{
    return 0;
}
