#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    void combine_helper(const int& n, const int& k, int curr, vector<int>& curr_com,
            vector<vector<int>>& res)
    {
        if (curr_com.size() == k)
        {
            /* Make a copy before push to res. */
            vector<int> temp(curr_com);
            res.push_back(std::move(temp));
        }
        else if (curr <= n)
        {
            combine_helper(n, k, curr + 1, curr_com, res);
            curr_com.push_back(curr);
            combine_helper(n, k, curr + 1, curr_com, res);
            curr_com.pop_back(); // back the state of calling function.
        }

        return;

    }
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> curr_com;

        combine_helper(n, k, 1, curr_com, res);
        return res;
    }
};
