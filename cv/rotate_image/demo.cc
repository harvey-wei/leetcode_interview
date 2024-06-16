#include <iostream>
#include <vector>


using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix)
	{
		/**
		 * Clockwise rotation of 90: [[0, 1], [-1, 0]]
		 * Column index shift:  +(n-1)
		 * r_new = c
		 * c_new = -r + n - 1
		 */
		int n = matrix.size(); // matrix is n by n.
		int temp;

		for (int r = 0; r < (n / 2 + n % 2); ++r)
		{
			for (int c = 0; c < n / 2; ++c)
			{
				/* (r, c) -> (c, n - 1 - r) -> (n - 1 - r, n - 1 - c) -> (n -1 - c, r)*/
				temp = matrix[r][c];
				matrix[r][c] = matrix[n - 1 - c][r];
				matrix[n - 1 - c][r] = matrix[n - 1 - r][n - 1 - c];
				matrix[n - 1 - r][n - 1 - c] = matrix[c][n - 1 -r];
				matrix[c][n - 1 -r] = temp;

				/* int r_new = c; */
				/* int c_new = -r + n - 1; */
				/* int temp_1 = matrix[r_new][c_new]; */
				/* matrix[r_new][c_new] = matrix[r][c]; */
				/**/
				/**/
				/* int r_new_1 = c_new; */
				/* int c_new_1 = -r_new + n - 1; */
				/* int temp_2 = matrix[r_new_1][c_new_1]; */
				/* matrix[r_new_1][c_new_1] = temp_1; */
				/**/
				/* int r_new_2 = c_new_1; */
				/* int c_new_2 = -r_new_1 + n - 1; */
				/* int temp_3 = matrix[r_new_2][c_new_2]; */
				/* matrix[r_new_2][c_new_2] = temp_2; */
				/**/
				/* matrix[r][c] = temp_3; */

			}
		}

    }
};

void print_mat(const std::vector<std::vector<int>>& mat)
{
	for (int r = 0; r < mat.size(); ++r)
	{
		for (int c = 0; c < mat[0].size(); ++c)
		{
			std::cout << mat[r][c] << ", ";
		}

		std::cout << std::endl;
	}

}

int
main()
{
	std::vector<std::vector<int>> mat{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

	Solution sol;
	sol.rotate(mat);

	print_mat(mat);

	return 0;
}
