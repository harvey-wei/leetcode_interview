#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    /*
       Time: O(N)
       Space: O(N)
    */
    int largestRectangleArea(vector<int>& heights)
    {
        /* For each bin in the histogram, we need find the ** most recent ** bins both in the past
           and in the future which are strictly less than it.
           Most recent -> stack
           Bi-directinal strictly less than -> ascending order (non-descending order stack)
           The * immediate neighor * in the stack is the most recent desirable one in the past.
           The current in the array might be the most recent desirable one in the future.

           Key: pop out the top element of the stack if the current < the top. (repeatedly)
        */
        int max_area = 0;

        // Elements in mono_stack are in ascending order and stores the index of element in the
        // original array heights.
        stack<int> mono_stack;
        mono_stack.push(-1);  // a dummy starting bin index and indicates stack is empty.

        // Each element is pushed to and popped out only once.
        for (int i = 0; i < heights.size(); ++i)
        {
            while (mono_stack.top() != -1 && heights[i] <  heights[mono_stack.top()])
            {
                int h = heights[mono_stack.top()];
                mono_stack.pop();
                max_area = max<int>(max_area, h * (i - mono_stack.top() - 1));
            }

            mono_stack.push(std::move(i));
        }

        // the mono_stack might not be empty if there are no more bins < top even all Elements
        // in the heights are visited.
        while (mono_stack.top() != -1)
        {
            int h = heights[mono_stack.top()];
            mono_stack.pop();
            max_area = max<int>(max_area, h * (heights.size() - mono_stack.top() - 1));
        }

        return max_area;
    }
};

int main()
{
    Solution sol;
    vector<int> heights = {2,1,5,6,2,3};
    std::cout << "Largest rectangle area: " << sol.largestRectangleArea(heights) << std::endl;

    return 0;
}
