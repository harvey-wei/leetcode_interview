#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/* https://leetcode.com/problems/contiguous-array/ */
class Solution {
public:
    int findMaxLength(vector<int>& nums)
    {
        unordered_map<int, int> sum2min_idx;
        /* Don't forget to insert the dummy acc_sum 0 at index -1*/
        sum2min_idx.insert({0, -1});
        int acc_sum = 0;
        int max_len = INT_MIN;

        for (int i = 0; i < int(nums.size()); ++i)
        {
            /* update the acc_sum to be nums[0] + ... +nums[i] */
            /* we treat 0 as -1 */
            acc_sum += nums[i] == 0 ? -1 : 1;

            /* check the count of sub-arrays with an equal number of 1 and 0 in nums[0:i]*/
            /* And then insert the current acc_sum and its count of occurrences. */
            if (sum2min_idx.end() != sum2min_idx.find(acc_sum))
            {
                max_len = max<int>(max_len, i - sum2min_idx[acc_sum]);
                /* No need to insert the current index since we want smallest index for longest
                   sub-array with an equal number of 0 and 1.
                */
            }
            else
            {
                sum2min_idx[acc_sum] = i;
            }
        }

        return max_len == INT_MIN ? 0 : max_len;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {0,1};
    int count = sol.findMaxLength(nums);

    cout << "count: " << count << endl;

    return 0;
}
