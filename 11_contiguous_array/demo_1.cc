#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
using namespace std;

#define INT_MIN (std::numeric_limits<int>::min())

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

class SolutionTwo {
public:
    int findMaxLength(vector<int>& nums) {
        int max_len = std::numeric_limits<int>::min();

        /* Imagine you prefix a dummy zero prefix sum */
        std::vector<long int> presum(nums.size() + 1, 0);
        for (size_t i = 0; i < nums.size(); ++i)
        {
            /**
             * Convert 0 to -1 such that same number of 0' as that of 1's amounts to sum of 0
             */
            presum[i + 1] = presum[i] + (nums[i] == 0 ? -1 : 1);
        }

        /* CAVEAT: From this point on, we are work with prefix sum array of the augmented array. */
        /* presum[j] - presum[i] =  sum of subarray(i, j] in the augmented array. */
        /* For the subarray indexed by (i, j] or [i, j) with i <= j, its length equals j - i. */
        /* Since we seek max length, we can bookkeep the smallest index for the same presum value */
        std::unordered_map<int, int> acc_sum2idx;
        acc_sum2idx[0] = 0;

        /* Check the subarray ending at j in the virtual array */
        for (int j = 1; j < presum.size(); ++j)
        {
            /* Search for the target start index */
            /* presum[i] == presum[j] due to the sum of zero! */
            if (acc_sum2idx.end() != acc_sum2idx.find(presum[j]))
            {
                max_len = std::max<int>(max_len, j - acc_sum2idx[presum[j]]);
            }
            else
            {
                /* update acc_sum2idx. If the acc_sum already exists, DO NOT update! */
                acc_sum2idx[presum[j]] = j;
            }
        }


        /* Return 0 if no satisfactory answer. */
        return max_len == std::numeric_limits<int>::min() ? 0 : max_len;
    }
};
int main()
{
    SolutionTwo sol;
    vector<int> nums = {0,1};
    int count = sol.findMaxLength(nums);

    cout << "count: " << count << endl;

    return 0;
}
