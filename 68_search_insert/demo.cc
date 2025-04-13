#include <vector>

using namespace std;


class Solution_ {
public:
    int searchInsert(vector<int>& nums, int target) {
        /**
         * [l, r)
         * m = l + (r - l) / 2; (floor)
         */
        int l = 0;
        int r = nums.size();
        int m;

        while (r - l > 0)
        {
            m = l + (r - l) / 2; // m >= l

            if (target == nums[m])
            {
                return m;
            }
            else if (target < nums[m])
            {
                // [l, m)
                r = m;
            }
            else
            {
                // target > nums[m], [m + 1, r)
                l = m + 1;  // if l = m, infinite loop
            }
        }

        /* the edge case: [l, l + 1)*/
        /* m = l + 1/ 2 = l */
        /* l == r [l, l) */

        /**
         * Target is not found.
         * For example, 1 3 5 6, target = 4
         * l = 1, r = 3, -> m = 1 + 1 = 2, 4 < nums[2]
         * r = m = 2, [1, 2), m = 1 + 1 / 2 = 1, 4 > nums[1]
         * l = m + 1 = 2, [2, 2) return 2
         *
         * target = -1 target < nums[m], r == m
         * l = 0, r = 4, m = 0 + 2 = 2, -1 < nums[2]
         * l = 0, r = 2, m = 0 + 2 / 2 = 1, -1 < nums[1]
         * l = 0, r = 1, m = 0 + 1 / 2= 0, -1 < nums[1]
         * l = 0, r = 0, [0, 0) return 0
         *
         * target = 7 > nums[m], target > nums[m], l = m + 1
         * l = 0, r = 4, m = 0 + 2 = 2, l = 2 + 1 =3
         * l = 3, r = 4, m = 3 + 0 = 3, l = 3 + 1 = 4
         * l = 4, r = 4 return 4
         *
         */

        return l;

    }
};


class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        /**
         * [l, r)
         * m = l + (r - l) / 2; (floor)
         */
        int l = 0;
        int r = nums.size() - 1;
        int m;

        while (r - l + 1 > 0) // (length of interval > 0)
        {
            m = l + (r - l + 1) / 2; // (r - l + 1) / 2 is floor(half of the interval length)

            if (target == nums[m])
            {
                return m;
            }
            else if (target < nums[m])
            {
                // [l, m]
                r = m - 1;
            }
            else
            {
                // target > nums[m], [m + 1, r)
                l = m + 1;
            }
        }

        /* the edge case: [l, l + 1)*/
        /* m = l + 1/ 2 = l */
        /* l == r [l, l) */

        /**
         * Target is not found.
         * For example, 1 3 5 6, target = 4
         * l = 1, r = 3, -> m = 1 + 1 = 2, 4 < nums[2]
         * r = m = 2, [1, 2), m = 1 + 1 / 2 = 1, 4 > nums[1]
         * l = m + 1 = 2, [2, 2) return 2
         *
         * target = -1 target < nums[m], r == m
         * l = 0, r = 4, m = 0 + 2 = 2, -1 < nums[2]
         * l = 0, r = 2, m = 0 + 2 / 2 = 1, -1 < nums[1]
         * l = 0, r = 1, m = 0 + 1 / 2= 0, -1 < nums[1]
         * l = 0, r = 0, [0, 0) return 0
         *
         * target = 7 > nums[m], target > nums[m], l = m + 1
         * l = 0, r = 4, m = 0 + 2 = 2, l = 2 + 1 =3
         * l = 3, r = 4, m = 3 + 0 = 3, l = 3 + 1 = 4
         * l = 4, r = 4 return 4
         *
         */

        return l;

    }
};

int
main(int argc, char** argv)
{

}
