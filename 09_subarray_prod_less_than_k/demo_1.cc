#include <iostream>
#include <vector>
using namespace std;

/* https://leetcode.com/problems/subarray-product-less-than-k/ */
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


class SolutionTwo
{
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k)
    {
        /* Since all input integers are positve, we could use double pointers. */
        /**
         * Increment of end index subsumes new numbers while increment of start index
         * drop left most number in the subarray.
         */
        int res = 0;
        int l = 0;
        long int window_prod = 1;


        for (int r = 0; r < nums.size(); ++r)
        {
            window_prod *= nums[r];

            /* Increment left pointers until window_prod is < k or l > r */
            while (l <= r && window_prod >= k)
            {
                window_prod /= nums[l];
                ++l;
            }

            if (l <= r && window_prod <k)
            {
                /* All subarrays of [l, r] ending at r have a product < k since all integers > 0 */
                res  += (r - l + 1);
            }
        }

        return res;
    }

    int numSubarrayProductLessThanK_(vector<int>& nums, int k)
    {
        int count = 0;
        long int curr_prod = 1;

        int l = 0;
        for (int r = 0; r < nums.size(); ++r)
        {
            /* Check the subarrays ending at r */
            curr_prod *= nums[r];

            /* Advance the start index l until curr_prod < k or l > r */
            while (l <= r && curr_prod >= k)
            {
                curr_prod /= nums[l];
                ++l;
            }

            /* curr_prod < k and l > r can hold at the same time. */
            if (l <= r && curr_prod < k)
            {
                count += r - l + 1;
            }
        }

        return count;
    }
};

int main()
{
    SolutionTwo sol;
    vector<int> nums = {10,5,2,6};
    int k = 100;
    /* vector<int> nums = {1, 2, 3}; */
    /* int k = 100; */
    int count = sol.numSubarrayProductLessThanK(nums, k);
    cout << "count " << count <<  endl;

    return 0;
}



/**
 * Why we could use double pointers to handle problems pertaining to subarray of positves
 * Because sliding windows implies the a cetrain way of *monotonic* state change of
 * the window!
 */
