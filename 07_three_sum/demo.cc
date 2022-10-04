#include <iostream>
#include <algorithm> // sort
#include <vector>

using namespace std;

class Solution {
public:
    void twoSum(const vector<int> & nums, const int &fixed_num_idx, const int &target,
            vector<vector<int>> &result)
    {
        /* assert(nums.size() >= 3); */
        /* for (int i = 0; i < nums.size() - 1; ++i) */
        /* { */
        /*     if (nums[i + 1] > nums[i]) */
        /*     { */
        /*         cout << "The input array was not sorted in non-descending order!" << endl; */
        /*         break; */
        /*     } */
        /* } */

        /* Look forward!*/
        int left = fixed_num_idx + 1;
        int right = nums.size() - 1;

        while (left < right)
        {
            int curr_sum = nums[left] + nums[right];
            if (target == curr_sum)
            {
                vector<int> curr_three = {nums[left], nums[right], nums[fixed_num_idx]};
                result.push_back(std::move(curr_three));

                /* remove duplicates  Work an example by hand! */
                /*1122 1111*/
                /* Move the left pointer to the right-most of the same integers. */
                while (left + 1 < right && nums[left] == nums[left + 1])
                {
                    ++left;
                }

                /*Move left pointer to the left by 1 position!*/
                ++left;
            }
            else if (curr_sum > target)
            {
                --right;
            }
            else
            {
                ++left;
            }
        }

    }

    /*
       sort -> fixe one integer -> call two_sum
       How to remove duplicate triplets?
       You need to work an example by hand to find why there is a duplicate!
       Each of the triplet should only meet each other once! Look forward!!! Don't backtrack!
       And we need to check the numbers of the same value only once!
    */
    vector<vector<int>> threeSum(vector<int>& nums) {
        assert(nums.size() >= 3u);
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;
        for (int i =0; i < nums.size(); ++i)
        {
            int target = -nums[i];
            twoSum(nums, i, target, result);

            /* remove duplicates */
            while (i + 1 < nums.size() && nums[i] == nums[i + 1])
            {
                ++i;
            }
        }

        return result;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {-1,0,1,2,-1,-4};
    vector<vector<int>> result;
    result = sol.threeSum(nums);
    cout << "[";
    for (const auto &vec: result)
    {
        cout << "[";
        for (const auto &entry: vec)
        {
            cout << entry << " ";
        }
        cout << "]";
    }
    cout << "]";

    return 0;
}
