#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
	void combinationSumHelper(const vector<int>& candidates, int curr, vector<int>& com,
			int& remain_sum, vector<vector<int>>& res)
	{
		if (0 == remain_sum)
		{
			res.push_back(com);
		}
		else if (curr < candidates.size() && remain_sum > 0)
		{
			/* Skip candidates[curr] */
			combinationSumHelper(candidates, curr + 1, com, remain_sum, res);

			// choose candidates[curr]
			com.push_back(candidates[curr]);
			remain_sum -= candidates[curr];

			// explore but candidates[curr] can be reused it can may be skpped in next recursion
			// remain_sum can be passed by value -> avoid unexplore
			combinationSumHelper(candidates, curr, com, remain_sum, res);

			// unexplore
			com.pop_back();
			remain_sum += candidates[curr];
		}
	}

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> curr_subset;

		int remain_sum = target;
		combinationSumHelper(candidates, 0, curr_subset, remain_sum, res);

        return res;
    }
};

int main()
{
    return 0;
}
