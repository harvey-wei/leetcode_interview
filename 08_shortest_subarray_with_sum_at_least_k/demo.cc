#include <vector>
#include <iostream>
#include <deque>

using namespace std;

/*
    1 <= target <= 109
    1 <= nums.length <= 105
    1 <= nums[i] <= 105
    https://leetcode.cn/problems/2VG8Kg/?favorite=e8X3pBZi
*/
class Solution {
public:
    /* Key insight: all integers are positive! */
    /* Time: O(N) since both both left and right are not decreased at all.
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
          p[i + 1] = p[i] + nums[i] for i = 1, 2, 3, ..., len(nums)
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

int main()
{
    Solution sol;
    /* int target = 7; */
    /* vector<int> nums = {2,3,1,2,4,3}; */

    /* int target = 4; */
    /* vector<int> nums = {1, 4, 4}; */

    /* int target = 11; */
    /* vector<int> nums = {1,1,1,1,1,1,1,1}; */
    /* int target = 7; */
    /* vector<int> nums = {1,1,1,1,7}; */
    vector<int> nums = {2,-1,2};
    int k = 3;
    int min_len = sol.shortestSubarray(nums, k);

    cout << "min_len " << min_len << endl;

    return 0;
}
