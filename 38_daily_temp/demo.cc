#include <vector>
#include <stack>


using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures)
    {
        stack<int> stack_idx;
        vector<int> result(temperatures.size(), 0);

        for (int i = 0; i < temperatures.size(); ++i)
        {
            while (!stack_idx.empty() && temperatures[i] > temperatures[stack_idx.top()])
            {
                result[stack_idx.top()] = i - stack_idx.top();
                stack_idx.pop();
            }

            // Note to push i
            stack_idx.push(i);
        }

        return result;
    }
};
