#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<long int, int> sum2cnt; sum2cnt.insert({0, 1});
        int count = 0;

        /* acc_sum[i] = nums[0] + nums[1] ... nums[i], for i = 0, 1, 2, len(nums) - 1
           acc_sum[i] = acc_sum[i - 1] + nums[i], for i = 1, 2, 3...len(nums) - 1
           nums[i..j] = acc_sum[j] - acc_sum[i - 1] for i <= j, i = 1, 2, ... N-1, j = 0, 1, ..., N-1
           nums[0..j] = acc_sum[j]

           If we define acc_sum[i] = 0 + nums[0] + ... + nums[i - 1], for i = 1, 2, 3,..., N
           acc_sum[0] = 0, for i =0, i.e. the sum of previous i numbers!
           nums[i..j] = acc_sum[j+1] - acc_sum[i]
        */
        /* Here, we adopt the first definition. */
        vector<long int> acc_sum(nums.size(), 0);

        acc_sum[0] = nums[0];
        count += (k == acc_sum[0]);
        if (sum2cnt.end() == sum2cnt.find(acc_sum[0]))
        {
            /*Not found!*/
            sum2cnt.insert({nums[0], 1});
        }
        else
        {
            sum2cnt[nums[0]] += 1;
        }

        /* Loop invariant: the count of subarray ending at i whose sum = k. */
        for (int i = 1; i < nums.size(); ++i)
        {
            acc_sum[i] = acc_sum[i - 1] + nums[i];
            long int addend = acc_sum[i] - k;
            if (sum2cnt.end() != sum2cnt.find(addend))
            {
                count += sum2cnt[addend];
            }

            if (sum2cnt.end() == sum2cnt.find(acc_sum[i]))
            {
                sum2cnt.insert({acc_sum[i], 1});
            }
            else
            {
                sum2cnt[acc_sum[i]] += 1;
            }
        }

        return count;
    }

    /* One more thing after you get the right implementation!
       Can we optimize or do you ascertain something redundant?
       Yes. acc_sum vector is not needed at all since we only use it from left to right only once!
       For sum[i] = sum[i -1] + nums[i] you only need one sum variable. reuse by updating

    */
    int subarraySum_better(vector<int>& nums, int k)
    {
        int count = 0;
        unordered_map<long int, int> sum2cnt;
        long int acc_sum = 0;
        sum2cnt[0] = 1;

        /* Loop variant: the count of non-empty subarray ending at i whose sum equals k. */
        for (int i = 0; i < nums.size(); ++i)
        {
            /* update the acc_sum to nums[0] +.. nums[i]*/
            acc_sum += nums[i];
            /* cout << "acc_sum: " << acc_sum << endl; */

            /*check whether the addend is in the previous sum. */
            long int addend = acc_sum - k;
            if (sum2cnt.end() != sum2cnt.find(addend))
            {
                count += sum2cnt[addend];
            }

            /* insert current acc_sum into map*/
            if (sum2cnt.end() == sum2cnt.find(acc_sum))
            {
                sum2cnt[acc_sum] = 1;
            }
            else
            {
                sum2cnt[acc_sum] += 1;
            }
        }

        return count;
    }
};


int main()
{
    Solution sol;
    vector<int> nums = {1,1,1};
    int k = 2;
    /* vector<int> nums = {1,2,3}; */
    /* int k = 3; */
    /* int count = sol.subarraySum(nums, k); */
    int count = sol.subarraySum_better(nums, k);

    cout << "count: " << count << endl;

    return 0;
}
