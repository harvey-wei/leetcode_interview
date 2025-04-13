#include <iostream>
#include <vector>

using namespace std;


class Solution
{
public:

	void subsets_recur(const vector<int>& nums, int i, vector<int>& subset,
			vector<vector<int>>& results)
	{
		if (i < nums.size())
		{
			/* not choose nums[i] */
			subsets_recur(nums, i + 1, subset, results);

			/* choose nums[i]*/
			subset.push_back(nums[i]);

			/* explore */
			subsets_recur(nums, i + 1, subset, results);

			/*unexplore */
			subset.pop_back();
		}
		else
		{
			/* i == nums.size() reach nullptr leaf leavel*/
			results.push_back(subset);
		}

	}

    vector<vector<int>> subsets(vector<int>& nums) {
		vector<int> subset;
		std::vector<vector<int>> results;
		// acutall a DFS tree traversal
		subsets_recur(nums, 0, subset, results);

		return results;
    }
};
