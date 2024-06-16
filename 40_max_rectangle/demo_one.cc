#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largest_rect(const vector<int>& heights)
    {
        int max_area = 0;
        stack<int> mono_stack; // store index and in ascending order
        mono_stack.push(-1);

        for (uint i = 0; i < heights.size(); ++i)
        {
            while (mono_stack.top() != -1 && heights[mono_stack.top()] > heights[i])
            {
                int h = heights[mono_stack.top()];
                mono_stack.pop();
                max_area = max<int>(max_area, h * (i - mono_stack.top() - 1));
            }

            // don't forget to push
            mono_stack.push(std::move(i));
        }

        // the remaining bins.
        while (mono_stack.top() != -1)
        {
            int h = heights[mono_stack.top()];
            mono_stack.pop();
            max_area = max<int>(max_area, h * (heights.size() - mono_stack.top() - 1));
        }

        return max_area;
    }

    int maximalRectangle(vector<vector<char>>& matrix)
    {
        int max_area = 0;
        int rows = matrix.size();
        int cols = matrix[0].size();

        for (int i = 0; i < rows; ++i)
        {
            vector<int> heights(cols, 0);
            for (int j = 0; j < cols; ++j)
            {
                int r = i;
                while (r >= 0 && '1' == matrix[r][j])
                {
                    heights[j] += 1;

                    // decrement r
                    --r;
                }
            }

            /* call largest rectangle function */
            max_area = max<int>(largest_rect(heights), max_area);
        }

        return max_area;
    }
};

int main()
{
    /* vector<vector<char>> matrix = {{'1', '0', '1', '0', '0'}, */
    /*     {'1','0','1','1','1'}, */
    /*     {'1','1','1','1','1'}, */
    /*     {'1','0','0','1','0'}}; */

    vector<vector<char>> matrix= {{'1'}};

    Solution sol;
    std::cout << sol.maximalRectangle(matrix) << std::endl;

    return 0;
}

