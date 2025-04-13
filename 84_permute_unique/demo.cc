#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:

    void helper(vector<int>& nums, vector<bool>& is_chosen, vector<int>& permute, vector<vector<int>>& result)
    {
		if (permute.size() == nums.size())
		{
			result.push_back(permute);
		}
		else
		{
			std::unordered_set<int> explored_ints;
			for (int i = 0; i < nums.size(); ++i)
			{
				if (is_chosen[i] == false)
				{
					if (explored_ints.end() == explored_ints.find(nums[i]))
					{
						// choose
						is_chosen[i] = true;
						explored_ints.insert(nums[i]);
						permute.push_back(nums[i]);

						// explore
						helper(nums, is_chosen, permute, result);

						// unchoose
						is_chosen[i] = false;
						permute.pop_back();
					}
				}
			}

		}
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
		vector<bool> is_chosen(nums.size(), false);
		vector<int> permute;
        helper(nums, is_chosen, permute, res);

        return res;
    }
};

void print_2d_vec(const vector<vector<int>>& vec)
{
    for (int r = 0; r < vec.size(); ++r)
    {
        for (int c = 0; c < vec[r].size(); ++c)
        {
            std::cout << vec[r][c]  << " ";
        }

        std::cout << std::endl;
    }
}

int main()
{
    Solution sol;
    /* vector<int> nums = {1, 1, 2}; */
    vector<int> nums = {1, 2, 3};
    vector<vector<int>> res = sol.permuteUnique(nums);
    print_2d_vec(res);

    return 0;
}
