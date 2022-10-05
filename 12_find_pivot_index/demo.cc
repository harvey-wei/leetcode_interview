#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums)
    {
        /* We also check the boundary element. */
        int prefix_sum = 0;
        int total_sum = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            total_sum += nums[i];
        }

        /* When we are at index i, left_sum = old prefix_sum.
           right_sum = total_sum - old_prefix_sum - nums[i]
        */
        for (int i = 0; i < nums.size(); ++i)
        {
            int left_sum = prefix_sum;
            int right_sum = total_sum - prefix_sum -nums[i];

            if (left_sum == right_sum)
            {
                return i;
            }

            /*update the prefix_sum*/
            prefix_sum += nums[i];
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    /* vector<int> nums = {1,7,3,6,5,6}; */
    vector<int> nums = {1, 2, 3};
    int pivot = sol.pivotIndex(nums);
    cout << "pivotIndex " << pivot << endl;

    return 0;
}
