#include <iostream>
#include <vector>
#include <string>
#include <stack>


using namespace std;


class Solution
{
public:
    int largest_rect(const vector<int>& heights)
    {
        int max_area = -1;
        stack<int> idx_stack;

        // -1 is to the left of 0 index and can also avoid empty check.
        idx_stack.push(-1);

        for (int i = 0; i < heights.size(); ++i)
        {
            while (-1 != idx_stack.top() && heights[i] < heights[idx_stack.top()])
            {
                /* The rectangle of height heights[idx_stack.top()] */
                /* _ - top- i, [_+1, i-1] */
                int h = heights[idx_stack.top()];
                idx_stack.pop();

                max_area = max(max_area, h * (i - idx_stack.top() - 1));
            }

            // -1 == top or > push to stack
            idx_stack.push(i);
        }

        // remnant
        while (-1 != idx_stack.top())
        {
            int h = heights[idx_stack.top()];
            idx_stack.pop();

            max_area = max(max_area, h * (int(heights.size()) - idx_stack.top() - 1));
        }

        return max_area;
    }

    int maximalRectangle(vector<vector<char>>& matrix)
    {

        /**
         * For each row, we generate a historam of size cols
         * And them, use the mono-stack to find its max area
         */
        int rows = matrix.size();
        int cols = matrix[0].size();
        int max_area = -1;

        for (int i = 0; i < rows; ++i)
        {
            vector<int> heights(cols, 0);
            for (int c = 0; c < cols; ++c)
            {
                int r = i;
                while (r >= 0 && 1 == matrix[r][c])
                {
                    ++heights[c];
                    --r;
                }
            }

            /* Get max area of historam. */
            max_area = max(max_area, largest_rect(heights));
        }

        return max_area;
    }
};
