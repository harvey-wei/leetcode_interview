#include <vector>
#include <iostream>


using namespace std;

class Solution {
public:
	void merge(vector<int>& nums, int l, int m, int r)
	{
		/**
		 * nums[l...m) and nums[m, ...r) are sorted in non-descending order.
		 */

		int l_n = m - l;
		int r_n = r - m;

		/* Copy both left and right sorted array. */
		std::vector<int> left_array(l_n);
		std::vector<int> right_array(r_n);

		for (int i = 0; i < l_n; ++i)
		{
			left_array[i] = nums[l + i];
		}

		for (int i = 0; i < r_n; ++i)
		{
			right_array[i] = nums[m + i];
		}

		int l_ptr = 0;
		int r_ptr = 0;
		int k = l;

		while (l_ptr < l_n && r_ptr < r_n)
		{
			if (left_array[l_ptr] < right_array[r_ptr])
			{
				nums[k] = left_array[l_ptr];
				++l_ptr;
			}
			else
			{
				nums[k] = right_array[r_ptr];
				++r_ptr;
			}

			++k;
		}

		while (l_ptr < l_n)
		{
			nums[k] = left_array[l_ptr];
			++l_ptr;
			++k;
		}

		while (r_ptr < r_n)
		{
			nums[k] = right_array[r_ptr];
			++r_ptr;
			++k;
		}
	}

	void merge_sort(vector<int>& nums, int  l, int r)
	{
		if (r - l > 1)
		{
			/* note the length > 1 */
			/* num size > 1 and need to sort */
			/* [left, right)*/
			/* [l, l+1] -> m = l no out of bound error */
			int m = l + (r - l) / 2;

			/* return; */

			/* [l, m) and [m, r)*/
			merge_sort(nums, l, m);
			merge_sort(nums, m, r);

			merge(nums, l, m, r);
		}
		else
		{
			/* base case: one element and no need to sort. */
		}

	}

    vector<int> sortArray(vector<int>& nums)
	{
		merge_sort(nums, 0, nums.size());

		return nums;
    }
};

int main()
{
	std::vector<int> nums{6, 5, 12, 10, 9, 1};

	Solution sol;

	nums = sol.sortArray(nums);
}


