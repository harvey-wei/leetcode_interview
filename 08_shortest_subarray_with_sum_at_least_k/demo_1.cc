#include <vector>
#include <iostream>
#include <deque>
#include <limits>

/* https://leetcode.com/problems/minimum-size-subarray-sum/description/ */
using namespace std;

#define INT_MAX (std::numeric_limits<int>::max())

/*
    1 <= target <= 109
    1 <= nums.length <= 105
    1 <= nums[i] <= 105
*/
class Solution {
public:
    /* Key insight: all integers are positive! */
    /* Time: O(N) since both left and right are not decreased at all.
       Space: O(1)
    */
    int minSubArrayLen(int target, vector<int>& nums)
    {
        /*nums.length >= 1*/
        int l =0, r = 0;
        int min_len = INT_MAX;
        int sum = nums[0];
        while (true)
        {
            /* case 1: [5, 1, 4, 3]  7*/
            if (((sum < target) && (r == nums.size() - 1)))
            {
                break;
            }

            /* case 2: [1, 1, 1, 1, 7] 7*/
            if (l == nums.size() - 1 && r == nums.size() - 1)
            {
                if (sum >= target)
                {
                    min_len = min<int>(min_len, 1);
                }

                break;
            }

            cout << "start shifting " << endl;
            if (sum >= target)
            {
                cout << "subarrary " << l << ", " << r << ", " << sum  <<" >= target" << endl;
                min_len = min<int>(min_len, r - l + 1);
                if (l + 1 < nums.size())
                {
                    sum -= nums[l];
                    ++l;
                    r = max<int>(r, l);
                }
            }
            else
            {
                cout << "subarrary " << l << ", " << r << ", " << sum << " < target" << endl;
                if (r + 1 < nums.size())
                {
                    ++r;
                    sum += nums[r];
                }
            }
        }

        return INT_MAX == min_len ? 0 : min_len;
    }

    /*
       For double pointers, it is better to fix one and change another alternatively.
    */
    int minSubArrayLen_better(int target, vector<int>& nums)
    {
        int sum = 0;
        int l = 0;
        int min_len = INT_MAX;
        for (int r = 0; r < int(nums.size()); ++r)
        {
            sum += nums[r];

            /* We need check sum > target*/
            /* No need to consider the  0 to last l_min since it is worse/longer!*/
            while (l <= r && sum >= target)
            {
                min_len = min<int>(min_len, r - l + 1);

                sum-=nums[l];
                ++l;
            }
        }

        return min_len == INT_MAX ? 0 : min_len;
    }

    /*
       Here, the integer is allowed to be negative, leading to failure of double pointers!
       https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
    */
    int shortestSubarray(vector<int>& nums, int k)
    {
        /*p[i] = nums[0] + nums[1] + ... + nums[i-1] for i = 0, 1, 2, len(nums)
          p[i + 1] = p[i] + nums[i] for i = 1, 2, 3, ..., len(nums) recursion
          p[0] = 0, p[1] = nums[0]
          Here, we use semi-open interval nums[x, y).
          sum of nums[x, y) = p[y] - p[x] length = y - x
        */
        std::vector<long int> p(nums.size() + 1, 0);
        for (int i = 1; i <= nums.size(); ++i)
        {
            p[i] = p[i - 1] + nums[i - 1];
        }

        /* Maintain a "monoqueue" of indices of P: a deque of indices x_0, x_1, ... such that
           P[x_0], P[x_1], ... is increasing.*/
        deque<int> mono_queue;
        int min_len = INT_MAX;
        /* Fix r and check all l <= r */
        /* Now we work with p*/
        for (int r = 0; r < p.size(); ++r)
        {
            /* pop_back all elements which are >= nums[r] before push back */
            while (!mono_queue.empty() && p[r] <= p[mono_queue.back()])
            {
                mono_queue.pop_back();
            }


            /* Since we work with [l, r), we need pop_front before we insert!
               avoid [r, r) wrong!  zero length
            */
            while ((!mono_queue.empty()) && (p[r] - p[mono_queue.front()] >= k))
            {
                min_len = min<int>(min_len, r - mono_queue.front());
                mono_queue.pop_front();
            }

            mono_queue.push_back(r);

        }

        return min_len == INT_MAX ? -1 : min_len;
    }
};

/* https://leetcode.com/problems/minimum-size-subarray-sum/description/ */
class Solution_
{
public:
    int minSubArrayLen(int target, vector<int>& nums)
    {
        /*
         * subarray is defined by start and end index.
         * For each end index, we find the possible shortest array with sum >= target.
         */

        int l = 0;
        int r = 0;
        int min_len = std::numeric_limits<int>::max();
        int s = 0;

        /* Each element is visited by r once and visited by l at most once.! */
        /* Hence, the time complexity is O(N). */
        /* l r min s takes up constant space! Therefore, the space complexity is O(1). */
        while (r < nums.size())
        {
            s += nums[r]; /* Since all integers are positive, addition grows the sum. */

            /* If s >= target, we decrement l to find the shortest subarray. */
            while (l <= r && s >= target)
            {
                min_len = std::min<int>(min_len, r - l + 1);
                s -= nums[l]; /* Since all integers are positive, subtraction diminishes the sum.  */
                ++l;
            }

            /* l = r + 1 or s < target.  Hence, we need increment r */
            ++r;
        }

        return min_len == std::numeric_limits<int>::max() ? 0 : min_len;
    }

    int shortestSubarray(vector<int>& nums, int k)
    {
        /* Note that pre_sum[i] = sum of nums[0] + ... nums[i-1] with i = 1, 2, 3
           pre_sum[0] is a dummy sum. We utilize the semi-open interval (x, y] to represent the
           subarray.
           Hence, sum of subarray[x+1, y] = pre_sum[y] - pre_sum[x] and its lenth y - x

           Or you can image you prefix the nums with a zero value.

           using long int to add ints to avoid overflow!
        */
        vector<long int> pre_sum(nums.size() +  1, 0);

        for (size_t i = 0; i < nums.size(); ++i)
        {
            pre_sum[i + 1] = pre_sum[i] + nums[i];
        }

        std::deque<int> mono_queue;
        int min_len = std::numeric_limits<int>::max();

        /* For the subarray (x, y], we fix end index and check all possible start index x in the
         * monoqueue.
         * pre_sum[y] - pre_sum[x] = sum of nums[x] ... nums[y - 1] with length y - x
         */
        for (int y = 0; y < pre_sum.size(); ++y)
        {
            /* Make sure the monoqueue is sorted in strictly increasing order.
             * All previous larger prefix sum can never be optimal for end index y!
             */
            while (!mono_queue.empty() && pre_sum[y] <= pre_sum[mono_queue.back()])
            {
                /* compare with back instead of front */
                mono_queue.pop_back();
            }

            /* Check the nums[x: y -1] with all possible x's in the monoqueue! */
            while (!mono_queue.empty() && (pre_sum[y] >= pre_sum[mono_queue.front()] + k))
            {
                min_len = std::min<int>(min_len, y - mono_queue.front());
                mono_queue.pop_front();

                /* Once x is optimal for certain y, then we don't need to consider x again since
                 * since larger y yields a worse answer!
                 */
            }

            /* push back y */
            mono_queue.push_back(y);
        }

        return min_len == std::numeric_limits<int>::max() ? -1 : min_len;


        /* Since each number is pushed once and popped at most once, both time and space complexity
           is linear!
        */
    }
};

class SolutionTwo {
public:
    int minSubArrayLen(int target, vector<int>& nums)
    {
        /* Since all the integers are positve, inserting one integer increases the sum while
           deleting one from the subarray diminishes the sum.

           For a given end idx, increment start idx until sum < target or start idx > end idx
        */
        int min_len = nums.size() + 1;

        int l = 0;
        int r = 0;

        long int window_sum = 0;

        /* Don't forget to updating the running window_sum! */

        for (; r < nums.size(); ++r)
        {
            window_sum += nums[r];

            while (l <= r && window_sum >= target)
            {
                min_len = std::min<int>(min_len, r - l + 1);
                window_sum -= nums[l];
                ++l; // Diminish the sum if possible!
            }
        }


        return min_len == (nums.size() + 1) ? 0 : min_len;


    }

    int minSubArrayLen_(int target, vector<int>& nums)
    {
        /* All integers are positve. */
        int min_len = nums.size() + 1;

        int l = 0;
        int r = 0;
        long int curr_sum = 0;

        /* Derive the complexity by following key operations. */
        /* Here, the key operations are +nums[r] and -nums[l]. */

        /**
         * Given that r ranges from 0 to nums.size() - 1 and l goes from 0 to at most
         * nums.size() - 1, time complexity is O(nums.size()).
         */
        for (; r < nums.size(); ++r)
        {
            /* Check subarrays ending at r. */
            curr_sum += nums[r];

            /* Move left pointer unitl curr_sum < target or l > r*/
            while (l <= r && curr_sum >= target)
            {
                min_len = std::min<int>(min_len, r - l + 1);
                curr_sum -= nums[l];
                ++l;
            }

            /* if l == r+ 1, don't worry since r is incremented at the next iteration */
        }

        return min_len == (nums.size() + 1) ? 0 : min_len;
    }

    int shortestSubarray(vector<int>& nums, int k)
    {
        /*
         * Note that if the integer can be negative, add one number does not necessarily grow the
         * sum while deleting one number does not necessarily diminish the sum.
         * In this case, it does not work to exploit double pointers to check subarray ending at
         * some index.
         * Instead, we can switch to the prefix sum or suffix sum of array.
         */
        int min_len = std::numeric_limits<int>::max();

        /* We prefix zero to the nums such that presum[1] = 0 + nums[i - 1] */
        /* presum[i] = nums[0] + ... nums[i - 1] note that nums' index is one less than that of
           prefsum

           presum[y] - presum[x] = nums[x] + ... nums[y - 1] which is the sum of nums[x, y)
           with length y - x
           nums idx:      0 1 2 3 ...
           presum idx:  0 1 2 3 4 ...
        */
        std::vector<long int> presum(nums.size() + 1, 0);
        for (size_t i = 0; i < nums.size(); ++i)
        {
            presum[i + 1] = presum[i] + nums[i];

            std::cout << "presum " << presum[i + 1] << std::endl;
        }

        /* At this point, we are working on prefix sum array named presum. */

        /**
         * Store the indices of presum such that this deque is sorted in strictly increasing
         * order as the previous large inegers can be ruled out!
         */
        std::deque<long int> monoqueue;

        /* We still check the subarray ending at r. */
        for (int r = 0; r < presum.size(); ++r)
        {
            /* Ensure monoqueue is sorted in increasing order. */
            while (!monoqueue.empty() && presum[r] <= presum[monoqueue.back()])
            {
                monoqueue.pop_back();
            }

            /* Find the min_len for subarrays ending at r by cheking front */
            while (!monoqueue.empty() && (presum[r] - presum[monoqueue.front()] >= k))
            {
                min_len = std::min<int>(min_len, r - monoqueue.front());
                monoqueue.pop_front();
            }

            /* push back nums[r] */

            std::cout << "push back index : " << r << std::endl;
            monoqueue.push_back(r);
        }

        /* return -1 if no satisfactory subarray. */
        return min_len == std::numeric_limits<int>::max() ? -1 : min_len;
    }
};

int main()
{
    SolutionTwo sol;
    int target = 7;
    vector<int> nums = {2,3,1,2,4,3};

    /* int target = 4; */
    /* vector<int> nums = {1, 4, 4}; */

    /* int target = 11; */
    /* vector<int> nums = {1,1,1,1,1,1,1,1}; */
    /* int target = 7; */
    /* vector<int> nums = {1,1,1,1,7}; */
    /* vector<int> nums = {1}; */
    /* vector<int> nums = {2,-1,2}; */
    /* int k = 1; */
    int min_len = sol.minSubArrayLen(target, nums);
    /* int min_len = sol.shortestSubarray(nums, k); */

    cout << "min_len " << min_len << endl;

    return 0;
}
