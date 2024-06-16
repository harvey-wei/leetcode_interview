#include <iostream>
#include <vector>
using namespace std;

/* https://leetcode.com/problems/minimum-path-sum/description/ */
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid)
	{

        // write code here
		int rows = grid.size();
		int cols = grid[0].size();

		/* vector<vector<int>> dp_mat(rows, vector<int>(cols, 0)); */
		/* vector<vector<Point>> prevs(rows, vector<Point>(cols, Point(0, 0))); */

		/* dp_mat[i][j] = min_prob_path from [0][0] -> [i][j]*/
		/* dp_mat[i][j] = in[i][j] + min(dp_mat[i -1][j], dp_mat[i][j-1])) */

		/* dp_mat[0][0] = grid[0][0]; */
		for (int c = 1; c < cols; ++c)
		{
			grid[0][c] = grid[0][c - 1] + grid[0][c];
		}

		for (int r = 1; r < rows; ++r)
		{
			grid[r][0] = grid[r - 1][0] + grid[r][0];
		}

		/* Go right or down.*/
		for (int r = 1; r < rows; ++r)
		{
			for (int c = 1; c < cols; ++c)
			{
				/* int min_r = -1; */
				/* int min_c = -1; */
				/* if (dp_mat[r - 1][c ] < dp_mat[r][c - 1]) */
				/* { */
				/* 	min_r = r -1; */
				/* 	min_c = c; */
				/* } */
				/* else */
				/* { */
				/* 	min_r = r; */
				/* 	min_c = c -1; */
				/**/
				/* } */
				/* prevs[r][c] = Point(min_r, min_c); */
				/* dp_mat[r][c] = grid[r][c] + dp_mat[min_r][min_c]; */

				grid[r][c] = grid[r][c] + min(grid[r - 1][c], grid[r][c - 1]);
			}
		}

		return grid[rows - 1][cols -1];
    }
};
