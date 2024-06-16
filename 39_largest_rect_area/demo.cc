#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights)
    {
        /**
         * For each bin, we want to define the largest rect whose height == that bin.
         * Hence, we wan to locate farthest bin to both left and right of that bin >= that bin.
         * ** Next smaller bin ** -> mono-increasing stack
         * You should prove some property using proof-by-contradiction.
         * Given that we scan the heights array from left to right.
         * We could find rect of height as the most recently visited bin.
         * Once the current visited bin strictly < top, the unvisited bins are rulled out for top
         * bin as heigh.
         */
        /* int max_area = INT_MIN; */
        int max_area = -1;  // area >= 0
        std::stack<int> idx_stack;


        for (int i = 0; i < heights.size(); ++i)
        {
            while (!idx_stack.empty() && (heights[i] < heights[idx_stack.top()]))
            {
                /**
                 * The largest rect of height heights[idx_stack.top()] is
                 * [second to top + 1, i - 1] >> top bin
                 * Base on the mono-increasing.
                 * All bins > top to left of top are discared.
                 * heights[i-1] must > heights[top]. otherwise top is already discared.
                 */
                int h = heights[idx_stack.top()];
                idx_stack.pop();

                // [idx_stack.top + 1, i - 1] >= h
                // prove by contradiction based on mono-non-descending fact.
                // idx = idx_stack.top + 1 if not empty
                int idx = idx_stack.empty() ? 0 : idx_stack.top() + 1;
                max_area = max(max_area, h * (i - idx));
            }

            // idx_stack is empty or heights[i] >= heights[top]
            idx_stack.push(i);
        }

        while (!idx_stack.empty())
        {
            /* That means no bin are < them. */
            /* [idx_stack.top, heights.size()) are largest rect of height top*/
            int h = heights[idx_stack.top()];
            idx_stack.pop();
            // You have to pop out the current to know the smallest left boundary

            /* [curr_top + 1, size()) */
            // idx = curr_top + 1
            int idx = idx_stack.empty() ? 0 : idx_stack.top() + 1;

            max_area = max(max_area, h * (int(heights.size()) - idx));
        }

        return  max_area;
    }
};


int main()
{
    Solution sol;
    vector<int> heights = {2,1,5,6,2,3};
    std::cout << "Largest rectangle area: " << sol.largestRectangleArea(heights) << std::endl;

    return 0;
}
