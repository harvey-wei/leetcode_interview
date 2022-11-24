#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    void helper(const vector<int>& candidates, int curr_target, int curr_idx,
            vector<int>& curr_subset, vector<vector<int>>& res)
    {
        if (0 == curr_target)
        {
            /* Be sure to copy! */
            vector<int> temp(curr_subset);
            res.push_back(std::move(temp));
        }
        else if (curr_idx < candidates.size() && curr_target > 0)
        {
            /* skip the current candidate. */
            helper(candidates, curr_target, curr_idx + 1, curr_subset, res);

            /* choose the current candidate again */
            curr_subset.push_back(std::move(candidates[curr_idx]));
            helper(candidates, curr_target - candidates[curr_idx], curr_idx, curr_subset, res);
            curr_subset.pop_back();
        }

        return;
    }
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> curr_subset;

        helper(candidates, target, 0, curr_subset, res);

        return res;
    }
};

int main()
{
    return 0;
}
