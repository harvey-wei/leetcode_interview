#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findMaxLength_init(vector<int>& nums)
    {
        /**
         * 1. nums is binary array, i.e. comprised of 0 and 1.
         * 2. Convert 0 to -1. The target subarray should have sum of zero.
         * 3. -1 is negative. We need prefix_sum or suffix_sum followed by double pointers.
         */

        /**
         * pre_sum[0] = 0
         * pre_sum[i] = nums[0] ... nums[i-1] = pre_sum[i-1] + nums[i-1] [0, i)
         * for i = 1, 2, 3...
         */
        vector<int> pre_sum(nums.size() + 1, 0);
        /* For the same sum, we only need bookkeep the smallest idx. */
        unordered_map<int, int> sum2idx;
        sum2idx.insert({0, 0});

        int max_len = 0;
        for (size_t i = 1; i < pre_sum.size(); ++i)
        {
            pre_sum[i] = pre_sum[i - 1] + (nums[i - 1] == 0 ? -1 : 1);

            if (sum2idx.end() == sum2idx.find(pre_sum[i]))
            {
                sum2idx.insert({pre_sum[i], i});
            }
        }


        for (size_t r = 1; r < pre_sum.size(); ++r)
        {
            // pre_sum[r] - pre_sum[l] = 0 -> pre_sum[l] == pre_sum[r]
            // [l, r)
            if (sum2idx.end() != sum2idx.find(pre_sum[r]))
            {
                max_len = std::max<int>(max_len, r - sum2idx[pre_sum[r]]);
            }
        }

        return max_len;
    }

    /* Late Optimization. */
    int findMaxLength(vector<int>& nums)
    {
        const int pre_sum_size = nums.size() + 1;
        unordered_map<int, int> pre_sum2idx;

        /**
         * pre_sum[0] = 0
         * pre_sum[i] = nums[0] + ... nums[i - 1] = pre_sum[i-1] + nums[i-1], i = 1, ..
         * Note to convert 0 to -1
         * prem[r] - prem[l] = sum of subarray[l, r) with length of r - l.
         */

        int pre_sum = 0;
        pre_sum2idx.insert({0, 0});
        int max_len = 0;

        for (size_t r = 1; r < pre_sum_size; ++r)
        {
            pre_sum += nums[r - 1] == 0 ? -1 : 1;

            if (pre_sum2idx.end() != pre_sum2idx.find(pre_sum))
            {
                max_len = std::max<int>(max_len, r - pre_sum2idx[pre_sum]);
            }
            else
            {
                /**
                 * For the same pre_sum, we only need the smallest one since we
                 * only need the max_len.
                 */
                pre_sum2idx.insert({pre_sum, r});
            }
        }

        return max_len;
    }
};


int
main()
{
    return 0;
}
