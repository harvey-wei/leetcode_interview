#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
public:
    void two_sum(const vector<int>& nums, const int& pivot_idx,
            vector<vector<int>>& result)
    {
        /* Assume nums is sorted in non-descending order. */
        int left = pivot_idx + 1;
        int right = nums.size() - 1;

        int sum = 0;

        while (left < right)
        {
            sum = nums[left] + nums[right];

            if (sum == -nums[pivot_idx])
            {
                result.push_back(std::vector<int>{nums[pivot_idx], nums[left],
                        nums[right]});

                /* Skip the same numbers to remove the duplicate triplets. */
                int temp = nums[left];
                while (left < right && temp == nums[left])
                {
                    ++left;
                }
            }
            else if (sum < -nums[pivot_idx])
            {
                ++left;
            }
            else
            {
                --right;
            }
        }
    }

    vector<vector<int>> threeSum(vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for (int i = 0; i < nums.size(); ++i)
        {
            /* Note that negatives fall to the left of sorted nums. */
            if ((i == 0 || (nums[i - 1] != nums[i])) && (nums[i] <= 0))
            {
                two_sum(nums, i, result);
            }
        }

        return result;
    }
};

int
main(int argc, char** argv)
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
