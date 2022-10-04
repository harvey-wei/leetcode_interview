#include <vector>
#include <iostream>
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
    int target = 7;
    vector<int> nums = {1,1,1,1,7};
    int min_len = sol.minSubArrayLen(target, nums);

    cout << "min_len " << min_len << endl;

    return 0;
}
