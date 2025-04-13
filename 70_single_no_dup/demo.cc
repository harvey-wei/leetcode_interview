#include <vector>
#include <iostream>

using namespace std;

// https://leetcode.com/problems/single-element-in-a-sorted-array/
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums)
    {
        /* The number of numbers must be odd. */
        int group = (nums.size() + 1) / 2;

        /* if (group == 1) return nums[0]; */

        int l = 0;
        int r = group;
        int m;
        int single;

        /* [l, r) and solution must exists. Hence, when r -l == 1, we reach the solution. */
        while (r - l >= 1)
        {
            /* r - l >= 2, m  >= l + 1 < r*/
            m = l + (r - l) / 2;

            int start = 2 * m;
            int end = start + 1;

            if (end == nums.size() || nums[start] != nums[end])
            {
                // check if m is the first group where two elements are diff or only one element
                // At least 2 groups
                if ((m - 1 >= 0 && (nums[2 * (m - 1)] == nums[2 * (m - 1) + 1])) || m - 1 < 0)
                {

                    single = nums[start];
                    break;
                }
                else
                {
                    // m is exclusive
                    r = m;
                }
            }
            else
            {
                // m is exclusive
                l = m + 1;
            }
        }


        return single;
    }
};


int
main()
{
    std::vector<int> arr = {1, 1, 2, 2, 3};
    Solution sol;

    std::cout << "single: " << sol.singleNonDuplicate(arr) << std::endl;

    arr = {3,3,7,7,10,11,11};
    std::cout << "single: " << sol.singleNonDuplicate(arr) << std::endl;
    arr = {9, 1, 1, 2, 2};
    std::cout << "single: " << sol.singleNonDuplicate(arr) << std::endl;

    arr = {1};
    std::cout << "single: " << sol.singleNonDuplicate(arr) << std::endl;

}
