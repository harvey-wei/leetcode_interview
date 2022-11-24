#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    void subsets_helper(const vector<int>& nums, int curr_idx, vector<int>& curr_subset,
            vector<vector<int>>& results)
    {
        if (curr_idx < nums.size())
        {
            /* choose the currend index -> explore (insert or not insert) -> unchoose */
            /* Not include nums[curr_idx] */
            subsets_helper(nums, curr_idx + 1, curr_subset, results);

            /* include nums[curr_idx] */
            curr_subset.push_back(std::move(nums[curr_idx]));
            subsets_helper(nums, curr_idx + 1, curr_subset, results);

            /* unchoose */
            curr_subset.pop_back();
        }
        else
        {
            /* The resuslt should get the copy of curr_subset. */
            vector<int> temp(curr_subset);
            results.push_back(temp);
        }

        return;

    }

    vector<vector<int>> subsets(vector<int>& nums) {
        int curr_idx = 0;
        vector<int> curr_subset= {};

        vector<vector<int>> results;
        subsets_helper(nums, curr_idx, curr_subset, results);

        return results;
    }
};

void print_mat(const vector<vector<int>>& mat)
{
    for (size_t r = 0; r < mat.size(); ++r)
    {
        for (size_t c = 0; c < mat[0].size(); ++c)
        {
            std::cout << mat[r][c] << " ";
        }

        std::cout << std::endl;
    }
    return;
}
int main()
{
    std::vector<int> nums = {0, 1, 2, 3};
    Solution sol;
    vector<vector<int>> res = sol.subsets(nums);

    std::cout << res[1][1] << std::endl;

    return 0;
}
