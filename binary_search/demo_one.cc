#include <vector>
#include <iostream>

using namespace std;

/* https://leetcode.com/problems/binary-search/ */

class Solution {
public:
    int search(vector<int>& nums, int target)
    {
        /* nums is sorted in ascending order. */
        int l = 0;
        int r = nums.size();
        int m = 0;

        /* we use semi-open interval [l, r) to simplify the termination condition */
        while (r > l)
        {
			/* continue if */
            m = l + (r - l) / 2;

            if (target == nums[m])
            {
                return m;
            }
            else if (target < nums[m])
            {
                r = m; // exclusive right boundary
            }
            else
            {
                /* target > nums[m] */
                l = m + 1; // inclusive left boundary
            }
        }

        return -1;
    }
};

int
main(int argc, char** argv)
{
    return 0;
}
