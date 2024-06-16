#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    int subarraySum(vector<int>& nums, int k)
    {
        /**
         * As the integer can be negative, we should use prefix sum or suffix sum.
         * The sum calculation of sub-array reduces to the difference of two pre_sums.
         * Hashset or hashmap can be used to memorize the scanned pre_sums.
         */

        /**
         * pre_sum[0] = 0
         * pre_sum[i] = nums[0] + ... nums[i - 1] = pre_sum[i - 1] + nums[i - 1] i = 1,...
         * pre_sum[r] - pre_sum[l] = nums[l] + ... nums[r - 1], [l, r)
         */

        /* vector<int> pre_sum(nums.size() + 1, 0); */
        unordered_map<int, int> sum2cnt;
        sum2cnt.insert({0, 1});
        int count = 0;

        int pre_sum = 0;

        for (size_t i = 1; i < nums.size() + 1; ++i)
        {
            /* Late Optimization is Necessary! */
            /*  No need to use pre_sum! updating one long int variable is enough  */
            /* pre_sum[i] = pre_sum[i - 1] + nums[i - 1]; */
            pre_sum += nums[i - 1];
            /* long int left_sum = pre_sum[i] - k; */
            int left_sum = pre_sum - k;

            if (sum2cnt.end() != sum2cnt.find(left_sum))
            {
                count += sum2cnt[left_sum];
            }


            // insert pre_sum[i]
            if (sum2cnt.end() == sum2cnt.find(pre_sum))
            {
                sum2cnt.insert({pre_sum, 1});
            }
            else
            {
                sum2cnt[pre_sum] += 1;
            }

        }

        return  count;
    }
};

int
main(int argc, char** argv)
{
    return 0;
}
