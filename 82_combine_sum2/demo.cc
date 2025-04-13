#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
	int get_next(vector<int>& candidates, int idx)
	{
		int next = idx;

		// Do not forget to check the bound
		while (next < candidates.size() && candidates[idx] == candidates[next])
		{
			++next;
		}

		return next;
	}

	void helper(vector<int>& candidates, int target, int idx, vector<int>& com, vector<vector<int>>& res)
	{
		if (0 == target)
		{
			res.push_back(com);
		}
		else if (idx < candidates.size() && target > 0)
		{
			/* Note that each number can only be used once*/
			/* To avoid duplicate tuple due to repteated numbers*/
			helper(candidates, target, get_next(candidates, idx), com, res);

			// choose
			com.push_back(candidates[idx]);
			target -= candidates[idx];

			// explore note target is possed by value, no need to unchoose
			helper(candidates, target, idx + 1, com, res);

			// unchoose
			com.pop_back();
		}

	}
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        std::sort(candidates.begin(), candidates.end());

        vector<int> pre_com;
        helper(candidates, target, 0, pre_com, res);

        return res;
    }
};

void print_2d_vec(const vector<vector<int>>& vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        for (size_t j = 0; j < vec[i].size(); ++j)
        {
            std::cout << vec[i][j] << ", ";
        }

        std::cout << std::endl;
    }

    return;
}

int main()
{
    vector<int> cands = {10,1,2,7,6,1,5};
    int target = 8;
    Solution sol;
    vector<vector<int>> res = sol.combinationSum2(cands, target);
    print_2d_vec(res);

    return 0;
}
