#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k)
    {
        /**
         * double pointer (aka slidding window) or pre_prod?
         * As all numbers are positive, we can use  double pointers.
         */

        long int prod = 1;
        int l = 0, r = 0;
        int count = 0;

        while (r < nums.size())
        {
            // Update window state
            prod *= nums[r];

            /* Advance l until prod < k */
            while (l <= r && prod >= k)
            {
                // update window state
                prod /= nums[l];
                ++l;
            }

            if (l <= r && prod < k)
            {
                /* Since all ints are > 0, all subarray ending at r have prod < k */
                count += r - l + 1;

            }

            /* Increment r to check subarrays ending at r */
            ++r;
        }

        return count;
    }
};

int
main(int argc, char** argv)
{
    return 0;
}
