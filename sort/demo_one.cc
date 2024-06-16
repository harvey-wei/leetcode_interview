#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

class Solution
{
    public:
        void swap_num(vector<int>& nums, int i, int j)
        {
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }

        int partition(vector<int>& nums, int left, int right)
        {
            /* nums[left...right] is of interest. */
            /* pivot_idx in [left, right]*/
            /* # of possible index = right - left + 1 */
            /* start = left */
            int pivot_idx = rand() % (right - left + 1) + left;

			/* put pivot nubmer to the end by swapping*/
			/* Now the pivot value is nums[right]*/
            swap_num(nums, pivot_idx, right);

            int low = left - 1;

			/* */
            /* Loop invariant: nums[0...low] < pivot_val */
            for (int i = left; i <= right; ++i)
            {
                if (nums[i] < nums[right])
                {
					/* Find one number < pivot_val*/
                    ++low;
                    swap_num(nums, i, low);
                }
            }

            /* Make nums[low] == pivot_val */
            ++low;
            swap_num(nums, low, right);

            return low;
        }

        void quick_sort_helper_(vector<int>& nums, int left, int right)
        {
            /* recursion */
            /**
             * Since there is no extra operation after the final recursion,
             * this recursion is a tail-recusive call.
             * Optimized version: eliminate the tail-recursion.
             */
            if (left < right)
            {
                int pivot_idx = partition(nums, left, right);
                quick_sort_helper(nums, left, pivot_idx - 1);
                quick_sort_helper(nums, pivot_idx + 1, right);
            }
            else
            {
                /* base case */
            }
        }

        void quick_sort_helper(vector<int>& nums, int left, int right)
        {
            /* recursion */
            /**
             * Since there is no extra operation after the final recursion,
             * this recursion is a tail-recusive call.
             * Optimized version: eliminate the tail-recursion.
             */
            while (left < right)
            {
                int pivot_idx = partition(nums, left, right);
                quick_sort_helper(nums, left, pivot_idx - 1);
                left = pivot_idx + 1;
                /* quick_sort_helper(nums, pivot_idx + 1, right); */
            }
        }

        void quick_sort(vector<int>& nums)
        {
            quick_sort_helper(nums, 0, nums.size() - 1);
        }

};

void stress_test()
{
    while (true)
    {
        std::vector<int> array;
        int num_cnt = 20;
        srand(time(0));

        for (int i = 0; i < num_cnt; ++i)
        {
            array.push_back(rand());
        }

        std::vector<int> array_(array);

        std::sort(array.begin(), array.end());

        Solution sol;
        sol.quick_sort(array_);

        for (int i = 0; i < num_cnt; ++i)
        {
            if (array[i] != array_[i])
            {
                std::cout << "Test failed!" << std::endl;
                return;
            }
        }

        std::cout << "Test succeeded!" << std::endl;
    }

    return;
}

int main()
{
    stress_test();
}
