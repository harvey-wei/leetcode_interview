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

class SolutionTwo {
public:
    int pivotIndex_(vector<int>& nums) {
        /* Space complexity O(N) which can be optimized! */
        std::vector<long int> presum(nums.size() + 1, 0);
        for (size_t i = 0; i < nums.size(); ++i)
        {
            presum[i + 1] = presum[i] + nums[i];
        }

        /* Note that the index j is in the augmented array! */
        for (int j = 1; j < presum.size(); ++j)
        {
            if (presum[j - 1] == presum[presum.size() - 1] - presum[j])
            {
                return j - 1; // Minus one to recover the index in the orignal array
            }
        }

        return -1;
    }

    int pivotIndex(vector<int>& nums)
    {
        long int total_sum = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            total_sum += nums[i];
        }

        long int left_sum = 0;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            /* Chech to see if left and right sum are equal! */
            if (left_sum == (total_sum - left_sum - nums[i]))
            {
                return i;
            }

            /* update left_sum */
            left_sum += nums[i];
        }

        return -1;
    }
};

int main()
{
    SolutionTwo sol;
    vector<int> nums = {1,7,3,6,5,6};
    /* vector<int> nums = {1, 2, 3}; */
    int pivot = sol.pivotIndex(nums);
    cout << "pivotIndex " << pivot << endl;

    return 0;
}
