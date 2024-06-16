#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums)
    {
        int total_sum = 0;
        for (const auto& num : nums)
        {
            total_sum += num;
        }

        /**
         * Left_sum = acc_sum until i - 1
         * left + pivot + right = total_sum
         */
        int pivot_idx = -1;
        int left_sum = 0;
        /* Chec each element to see if it could be the pivot. */
        for (size_t i = 0; i < nums.size(); ++i)
        {
            if (left_sum == (total_sum - nums[i] - left_sum))
            {
                pivot_idx = i;
                break;
            }
            else
            {
                // update left_sum
                left_sum += nums[i];
            }
        }

        return pivot_idx;
    }
};


int
main(int argc, char** argv)
{
    Solution sol;
    vector<int> nums = {1,7,3,6,5,6};
    /* vector<int> nums = {1, 2, 3}; */
    int pivot = sol.pivotIndex(nums);
    cout << "pivotIndex " << pivot << endl;


    return 0;
}
