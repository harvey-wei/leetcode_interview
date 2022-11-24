#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int get_next(const vector<int>& candidates, const int& curr_idx)
    {
        int next_idx = curr_idx;

        while (next_idx < candidates.size() && candidates[next_idx] == candidates[curr_idx])
        {
            ++next_idx;
        }

        /*
           case 1: next_idx == candidates.size();
           case 2: next_idx < candidates.size() but candidates[next_idx] != candidates[curr_idx]
        */
        return next_idx;
    }

    void helper(const vector<int>& candidates, int curr_target,int curr_idx, vector<int>& pre_com,
            vector<vector<int>>& results)
    {
        /* if (candidates.size() == curr_idx) */
        if (0 == curr_target)
        {
            /* base case */
            results.push_back(pre_com); // Invoke copy constructor
        }
        else if (curr_target > 0 && curr_idx < candidates.size())
        {
            /* choice 1: skip the current number and all the subsequent number of the same values.*/
            int next_idx = get_next(candidates, curr_idx);
            helper(candidates, curr_target, next_idx, pre_com, results);

            /* choice 2: Select the current number. */
            pre_com.push_back(std::move(candidates[curr_idx]));
            helper(candidates, curr_target - candidates[curr_idx] , curr_idx + 1, pre_com, results);
            pre_com.pop_back();
        }

        return;
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
