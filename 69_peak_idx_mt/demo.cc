#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        /* [l, r)  r - l >= 3*/
        int l = 0;
        int r = arr.size();
        int m;

        while (r - l > 1)
        {
            /* Length of [l, r) >= 2. m >= l + 1 */
            /* Hence, m will not be out of range! */
            m = l + (r - l) / 2; // m >= l

            /* Note that adjacent numbers are distinct. */
            if (arr[m] > arr[m - 1])
            {
                // m should be inclusive. [left, right)
                l = m;
            }
            else
            {
                // m can be exclusive [left, right)
                r = m;
            }
        }

        /* r - l == 1 */
        return l;
    }
};

int
main(int argc, char** argv)
{
    Solution sol;
    std::vector<int> arr{0, 1, 0};
    std::cout << sol.peakIndexInMountainArray(arr) << std::endl;

    arr = {0, 2, 1, 0};
    std::cout << sol.peakIndexInMountainArray(arr) << std::endl;

    arr = {0, 10, 5, 2};
    std::cout << sol.peakIndexInMountainArray(arr) << std::endl;

    return 0;
}
