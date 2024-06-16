#include <iostream>
#include <vector>

using namespace std;


class Solution
{
public:
	void subset_recur(const vector<int>& nums, int curr_idx,
			vector<int>& subset, vector<vector<int>>& results)
	{
		if (curr_idx < nums.size())
		{
			/* Not choose */
			subset_recur(nums, curr_idx + 1, subset, results);


			/* Choose nums[curr_idx]*/
			subset.push_back(nums[curr_idx]);
			/* Explore */
			subset_recur(nums, curr_idx + 1, subset, results);
			/* Unchoose*/
			subset.pop_back();
		}
		else
		{
			/* base case. we need get the copy of subset*/
			results.push_back({subset});
		}
	}

    vector<vector<int>> subsets(vector<int>& nums) {
		vector<int> subset;
		std::vector<vector<int>> results;

		subset_recur(nums, 0, subset, results);

		return results;
    }
};
