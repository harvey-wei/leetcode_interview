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
*/
class NumMatrix {
private:
    /* vector<vector<int>> sums; */
    vector<vector<int>> pre_sums;
public:
    NumMatrix(vector<vector<int>>& matrix) {
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

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
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
