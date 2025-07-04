#include <iostream>
#include <vector>
using namespace std;


/*
    https://leetcode.com/problems/range-sum-query-2d-immutable/
    m == matrix.length
    n == matrix[i].length
    1 <= m, n <= 200
    -104 <= matrix[i][j] <= 104
    0 <= row1 <= row2 < m
    0 <= col1 <= col2 < n
    At most 104 calls will be made to sumRegion.

    Thinking recursively.
    // How to handle the boundary problem?
    // Way 1: Introduce the dummy elements.
    // Way 2: Use if-else statement to check the boundary case.
*/
class NumMatrixOne {
private:
    /* vector<vector<int>> sums; */
    vector<vector<int>> pre_sums;
public:
    NumMatrixOne(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();
        /* sums.resize(rows, vector<int>(cols, 0)); */

        /* In pre_sums, (i, j) means ith row and jth col (1-based index)*/
        pre_sums.resize(rows + 1, vector<int>(cols + 1, 0));

        /* for (int i = 0; i < rows; ++i) */
        /* { */
        /*     int row_sum = 0; */
        /*     for (int j = 0; j < cols; ++j) */
        /*     { */
        /*         row_sum += matrix[i][j]; */
        /*         sums[i][j] = (i > 0 ? sums[i - 1][j] : 0) + row_sum; */
        /*     } */
        /* } */

        for (int i = 1; i <= rows; ++i)
        {
            int row_sum = 0;
            for (int j = 1; j <= cols; ++j)
            {
                row_sum += matrix[i - 1][j - 1];
                pre_sums[i][j] = pre_sums[i - 1][j] + row_sum;
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return pre_sums[row2 + 1][col2 + 1] - (pre_sums[row1][col2 + 1]) - (pre_sums[row2 + 1][col1]) +
                (pre_sums[row1][col1]);

        /* return sums[row2][col2] - */
        /*         (row1 > 0 ? sums[row1 - 1][col2] : 0) - */
        /*         (col1 > 0 ? sums[row2][col1 - 1] : 0) + */
        /*         (row1 > 0 && col1 > 0 ? sums[row1 - 1][col1 -1] : 0); */
    }
};


class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int rows = matrix.size();
        int cols = matrix[0].size();

        /* We append zeros the matrix to the topmost row and leftmost column, respectively. */
        /* By doing so, we handle the out of boundary problem in a unified way. */
        /* Note the off by one index between original and augmeted matricies. */
        presum.resize(rows + 1, std::vector<long int>(cols + 1, 0)); // zero!

        /**
         * presum[i][j] is the sum of the rectangle bounded by (0, 0) and (i, j) in the augmented
         * matrix
         * Inductive Reasoning: presum[i][j] = presum[i - 1][j] + sum for elements from 0 to j in
         ith row with i and j ranging from 1 to rows and cols inclusively and respectively.
         */
        long int row_sum;
        for (size_t r = 0; r < rows; ++r)
        {
            row_sum = 0;
            for (size_t c = 0; c < cols; ++c)
            {
                row_sum += matrix[r][c];
                presum[r + 1][c + 1] = presum[r][c + 1] + row_sum;
            }
        }
    }

    /**
     * Note that this range sum query will be called frequently. Hence, we are better off
     */
    int sumRegion(int row1, int col1, int row2, int col2)
    {
        /**
         * In the augmented matrix, sum = presum[row2][col2] - presum[row1 - 1][col2]
         * - presum[row2][col1 - 1] + presum[row1 - 1][col1 - 1]
         * Since the given index is in the orignal matrix, hence we need to increment by 1
         */

        return presum[row2 + 1][ col2 + 1] - presum[row1][col2 + 1] - presum[row2 + 1][col1]
                + presum[row1][col1];
    }

private:
    std::vector<std::vector<long int>> presum;
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,csumRegionol2);
 */
int main()
{
    vector<vector<int>> m = {{3, 0, 1, 4, 2}, {5, 6, 3, 2, 1}, {1, 2, 0, 1, 5}, {4, 1, 0, 1, 7}, {1, 0, 3, 0, 5}};
    NumMatrix * numMatrix = new NumMatrix(m);
    cout << numMatrix->sumRegion(2, 1, 4, 3) << endl; // return 8 (i.e sum of the red rectangle)
    cout << numMatrix->sumRegion(1, 1, 2, 2) << endl; // return 11 (i.e sum of the green rectangle)
    cout << numMatrix->sumRegion(1, 2, 2, 4) << endl; // return 12 (i.e sum of the blue rectangle)

    return 0;
}
