#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    void swap_nums(vector<int>& nums, int i, int j)
    {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    void helper(vector<int>& nums, int curr_idx, vector<vector<int>>& result)
    {
        if (curr_idx == nums.size())
        {
            /* Might need to fix! */
            result.push_back(nums);
        }
        else
        {
            /* The numbers at position 0 - (curr_idx - 1) have been selected. */
            unordered_set<int> choosed_ints;
            for (int i = curr_idx; i < nums.size(); ++i)
            {
                if (choosed_ints.end() == choosed_ints.find(nums[i]))
                {
                    choosed_ints.insert(nums[i]);
                    swap_nums(nums, curr_idx, i); // choose
                    helper(nums, curr_idx + 1, result);  // explore
                    swap_nums(nums, curr_idx, i); // unchoose
                }
            }
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        helper(nums, 0, res);

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
