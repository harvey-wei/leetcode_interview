#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k)
    {
        int count = 0;
        int l = 0;
        int prod = 1;


        /* Loop variant: [l, r] is the longest subarray for which prod < k for the given k. */
        for (int r = 0; r < nums.size(); ++r)
        {
            prod *= nums[r];

            /* Loop invariant: the l after this while is the smallest for which prod < k.
            */
            while (l <= r && prod >= k)
            {
                prod /= nums[l];
                ++l;
            }

            if (l <= r && prod < k)
            {
                count += r - l + 1;
            }
        }

        return count;
    }
};

int main()
{
    Solution sol;
    /* vector<int> nums = {10,5,2,6}; */
    /* int k = 100; */
    vector<int> nums = {1, 2, 3};
    int k = 100;
    int count = sol.numSubarrayProductLessThanK(nums, k);
    cout << "count " << count <<  endl;

    return 0;
}
