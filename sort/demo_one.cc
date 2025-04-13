#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

class Solution
{
	public:
		void swap_num(vector<int>& nums, int i , int j)
		{
			int temp = nums[i];
			nums[i] = nums[j];
			nums[j] = temp;
		}

		int partition(vector<int>& nums, int l, int r)
		{
			/**
			 * We consider nums[l, r).
			 */

			// randomly generate pivot_idx
			int pivot_idx = rand() % (r - l) + l; // pivot_idx in [l, r)

			// Move the pivot number to the end by swapping
			swap_num(nums, pivot_idx, r - 1);

			// One-pass scan from l to r) to move all numbers < pivot_number to left of current subarray
			int lower = l - 1;

			for (int i = l; i < r; ++i)
			{
				if (nums[i] < nums[r - 1])
				{
					++lower;
					swap_num(nums, i, lower);
				}
			}

			// Now: nums[l, lower] < nums[r - 1] if lower >= l
			// Move the pivot number back to back of all numbers < pivot_number
			++lower;
			swap_num(nums, lower, r - 1);

			// return current index of pivot_number
			return lower;
		}

		void partition3(vector<int>& nums, int l, int r,int& m1, int& m2)
		{
			/**
			 * pivot == 5
			 * 3 4 2 5 5 5 6 1 5
			 *    m1    m2 i
			 */
			int pivot_idx = rand() % (r - l) + l;
			swap_num(nums, pivot_idx, r - 1);

			m1 = l - 1;
			m2 = m1;

			for (int i = l; i < r; ++i)
			{
				if (nums[i] < nums[r - 1])
				{
					++m1;
					++m2;
					swap_num(nums, i, m1); // swap nums[i] and nums[m1]

					if (m2 - m1 >0)
					{
						swap_num(nums, i, m2);
					}
				}
				else if (nums[i] == nums[r - 1])
				{
					++m2;
					swap_num(nums, i, m2);
				}
				else
				{
					/* Do nothing*/
				}
			}

			// (m1, m2]
		}

		void quick_sort_helper_3(vector<int>& nums, int l, int r)
		{
			if (r - l > 1)
			{
				int m1, m2;
				partition3(nums, l, r, m1, m2);

				// nums[l, m1] < pivot, nums(m1, m2] == pivot, nums(m2, r] > pivot
				quick_sort_helper_3(nums, l, m1 +1);
				quick_sort_helper_3(nums, m2 + 1, r);
			}
		}

		void quick_sort_helper(vector<int>& nums, int l, int r)
		{
			// nums[l, r) is of concern.
			if (r - l > 1)
			{
				int pivot_idx = partition(nums, l, r);
				quick_sort_helper(nums, l, pivot_idx); // pivot_idx is exclusive
				quick_sort_helper(nums, pivot_idx + 1, r);
			}
		}

		void quick_sort_helper_tail_elimination(vector<int>& nums, int l, int r)
		{
			// nums[l, r) is of concern.
			while (r - l > 1)
			{
				int pivot_idx = partition(nums, l, r);
				if ((pivot_idx - l) < (r - pivot_idx - 1))
				{
					quick_sort_helper(nums, l, pivot_idx); // pivot_idx is exclusive
					l = pivot_idx + 1;
				}
				else
				{
					quick_sort_helper(nums, pivot_idx + 1, r);
					r = pivot_idx;
				}
			}
		}

        void quick_sort(vector<int>& nums)
        {
            /* quick_sort_helper_tail_elimination(nums, 0, nums.size()); */
            quick_sort_helper_3(nums, 0, nums.size());
        }
};

class Solution_
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
			// use percentage sign instead of / for modulo operation
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
    Solution sol;
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
