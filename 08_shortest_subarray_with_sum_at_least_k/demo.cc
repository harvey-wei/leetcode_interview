#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Solution
{
public:
    int minSubArrayLen(int target, vector<int>& nums)
    {
        /**
         * All numbers are positive.
         * Move the length-variable window. Insert positive -> sum gets larger.
         * Remove positive -> sum gets smaller.
         * Goal is to get a sum >= target.
         * ++r -> increase sum.
         * ++l -> decrease sum.
         */
        int sum = 0;
        int l = 0, r = 0;
        int min_len = nums.size() + 1;
        for (; r < nums.size(); ++r)
        {
            sum += nums[r];

            /* It matters to limit l <= r! */
            /* ++l only if sum >= target since ++l decrease sum*/
            while (l <= r && sum >= target)
            {
                min_len = std::min(min_len, r - l + 1);

                // update sum and l
                sum -= nums[l];
                ++l;
            }
        }

        return min_len == nums.size() + 1 ? 0 : min_len;
    }

    int shortestSubarray(vector<int>& nums, int k)
    {
        int min_len = nums.size() + 1;

        /**
         * pre_sum[0] = 0
         * pre_sum[i] = nums[0] + ... nums[i-1] for i = 1, 2, ...
         * recursion: pre_sum[i] = nums[i-1] + pre_sum[i-1]
         * pre_sum[y] - pre_sum[x] = nums[x] +... nums[y-1], [x, y) x, y>=0
         */
        std::vector<long int> pre_sum(nums.size() + 1, 0);
        for (size_t i = 1; i < pre_sum.size(); ++i)
        {
            pre_sum[i] = pre_sum[i - 1] + nums[i -1];
        }

        /**
         * We check subarray [x, y).
         * sum of sub[x, y) = pre_sum[y] - pre_sum[x]
         * For a subarray ending at y, candidate x is the one for which
         * pre_sum[x] <= pre_sum[y] - k
         *
         * Two key observations:
         * If x1 < x2, but pre_sum[x1] >= pre_sum[x2], then x1 can not be the optimal.
         * => we need to maintain a queue of increasing pre_sum[x] even for the 1st
         * candidate x
         * If x is optimal for y1, then x can be ignored for any y > y since we find
         * the shortestSubarray.
         */

        std::deque<long int> mono_queue; // store the index instead of presum

        for (int r = 0; r < pre_sum.size(); ++r)
        {
            /* Check all possible sub-arraies [?, r)*/

            // Ensure increasing property.
            while (!mono_queue.empty() && pre_sum[mono_queue.back()] >= pre_sum[r])
            {
                mono_queue.pop_back();
            }

            // Check sub-array [front, r)
            while (!mono_queue.empty() &&
                    (pre_sum[r] - pre_sum[mono_queue.front() >= k]))
            {
                min_len = std::min<int>(min_len, r - mono_queue.front());

                // pop front
                mono_queue.pop_front();
            }


            // push r to mono_queue
            mono_queue.push_back(r);

        }

        return min_len == nums.size() + 1 ? -1 : min_len;
    }
};

int
main(int argc, char** argv)
{
    return 0;
}
