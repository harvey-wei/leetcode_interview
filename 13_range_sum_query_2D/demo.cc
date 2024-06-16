#include <iostream>
#include <vector>

using namespace std;


class NumMatrix
{
public:
    NumMatrix(vector<vector<int>>& matrix)
    {
        const int rows = matrix.size();
        const int cols = matrix[0].size();

        /* Append zero to top and left */
        pre_sums.resize(rows + 1, vector<int>(cols + 1, 0));

        /**
         * pre_sums[0, :] = 0, pre_sums[:, 0] = 0
         * pre_sums[i, j] = sum of (matrix[0][0]) - (matrix[i-1][j-1])
         */

        /* Precompute the presum in a raster fashion.
         * pre_sum[i, j] = presum[i - 1, j] + acc_sum of row i to current element.
         */
        for (int row = 1; row < pre_sums.size(); ++row)
        {
            int acc_row_sum = 0;
            for (int col = 1; col < pre_sums[0].size(); ++col)
            {
                /* Note the off-by-one diff of index between matrix and presums. */
                acc_row_sum += matrix[row - 1][col - 1];
                pre_sums[row][col] = pre_sums[row - 1][col] + acc_row_sum;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return pre_sums[row2 + 1][col2 + 1] - pre_sums[row1][col2 + 1]
                - pre_sums[row2 + 1][col1] + pre_sums[row1][col1];
    }

private:
    vector<vector<int>> pre_sums;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */
