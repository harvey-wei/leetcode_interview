#include <iostream>
#include <algorithm> // sort
#include <vector>

using namespace std;

/**
 * \ref: https://leetcode.com/problems/3sum/description/
 */
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
        /* assert(nums.size() >= 3u); */
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


class Solution_ {
public:
    void two_sum(vector<int>& nums, const int& fixed_num_idx, vector<vector<int>>& results)
    {
        /**
         * \notes
         * 1. nums is sorted in non-descending order.
         * 2. All the integers before nums[fixed_num_idx] have been checked. Hence, the left
         *    pointer should start at fixed_num_idx + 1.
         * 3. To avoid the duplicate triplet, we need to make the next left pointer point to a
         *    different value from the current element which make a corrent answer.
         * For example, in the sub-array 2 2 2 3 3 3 (2, 3) is part of corrent triplet.
         * By making left pointer point to next different value 3, the duplicate 3's are also
         * removed
         * 4. Make left is in the index range before indexing!
         */

        /**
         * fixed_num_idx < nums.size() - 2  means we only consider nums[0,..., nums,size() - 2)
         * nums.size() - k means stripping the trailing k elements from the array.
         */

        std::cout << "fixed_num_idx: " << fixed_num_idx << std::endl;
        int l = fixed_num_idx + 1;
        int r = nums.size() - 1;
        int s = 0;

        while (l < r)
        {
            s = nums[fixed_num_idx] + nums[l] + nums[r];

            if (0 == s)
            {
                std::cout << "nums[l]: " << nums[l] << std::endl;
                /* results.emplace_back(nums[fixed_num_idx], nums[l], nums[r]); */
                results.push_back(std::vector<int>{nums[fixed_num_idx], nums[l], nums[r]});

                /* Since the sum of two numbers is fixed, one is not repeated means another can not
                be repeatd. b = s - a*/
                /* Move the left pointer forward such that left points to a different value or
                 * out of the index bound (l == r ).
                 */
                int temp = nums[l];

                while (l < r && (temp == nums[l]))
                {
                    ++l;
                }
            }
            else if (s > 0)
            {
                --r;
            }
            else
            {
                /* s < 0 */
                ++l;
            }

        }

        return;
    }

    vector<vector<int>> threeSum(vector<int>& nums)
    {
        vector<vector<int>> results;

        /* Note that the std::sort sorts the array in non-descending order in place. */
        sort(nums.begin(), nums.end());

        /* Make sure the subarray on the left of the nums[fixed_num_idx] has no fewer than 2
           elements. */
        int fixed_num_idx = 0;

        /* Updating the loop count variable at multiple places is error-prone! */
        while (fixed_num_idx < nums.size() - 2)
        {

            two_sum(nums, fixed_num_idx, results);

            int temp = nums[fixed_num_idx];

            /* fixed_num_idx is incremented at least once! */
            while (fixed_num_idx < (nums.size() - 2) && (temp == nums[fixed_num_idx]))
            {
                ++fixed_num_idx;
            }

            /* nums.size() - i indicates the position one past the front (nums.size() - i) elements. */
            /* At this point, fixed_num_idx == nums.size() - 2 or  nums[fixed_num_idx] != temp */
        }

        return results;
    }
};

class SolutionTwo
{
public:
    void two_sum(const vector<int>& sorted_nums, const int& fixed_num_idx,
            vector<vector<int>>& results)
    {
        int l = fixed_num_idx + 1;
        int r = sorted_nums.size() - 1;

        while (l < r)
        {
            if (-sorted_nums[fixed_num_idx] == sorted_nums[l] +  sorted_nums[r])
            {
                /* Store the indices: fixed_num_idx, l, r and remove duplicates. */
                /* std::vector<int>{fixed_num_idx, l, r} is a temporary object, i.e. rvalue
                   Hence, the move constructor is called!
                */
                results.push_back(std::vector<int>{sorted_nums[fixed_num_idx],
                        sorted_nums[l], sorted_nums[r]});
                /* results.emplace_back(fixed_num_idx, l, r); */

                /* Make l point to a different value if possible. */
                int temp = sorted_nums[l];

                while (l < r && (temp == sorted_nums[l]))
                {
                    ++l;
                }

                /* l == r -> while is ove! or l points to another value. Or, even both. */
            }
            else if (sorted_nums[l] + sorted_nums[r] > -sorted_nums[fixed_num_idx])
            {
                --r;
            }
            else
            {
                ++l;
            }
        }

    }

    vector<vector<int>> threeSum(vector<int>& nums)
    {
        /* sort the nums in non-descending order in place! */
        std::sort(nums.begin(), nums.end());

        std::vector<std::vector<int>> result;
        int fixed_num_idx = 0;

        while (fixed_num_idx < nums.size())
        {
            two_sum(nums, fixed_num_idx, result);

            /* Make fixed_num_idx point to different value */
            int temp = nums[fixed_num_idx];
            while (fixed_num_idx < nums.size() && temp == nums[fixed_num_idx])
            {
                ++fixed_num_idx;
            }
        }

        return result;
    }
};


int main()
{
    SolutionTwo sol;
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
