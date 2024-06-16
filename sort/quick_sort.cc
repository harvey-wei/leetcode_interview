#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

class Solution_ {
public:
	int partition(vector<int>& nums, int left, int right)
	{
		/**
		 * [left, right]
		 * # of indices = right - left + 1, start index is left
		 */
		int pivot_idx = rand() % (right - left + 1) + left;

		/* Put the pivot the righg index */
		swap(nums[pivot_idx], nums[right]);

		/* Now pivot_val = nums[right] */
		/* Scan from left to right and swap with nums[low] such that nums[left, ...low] < pivot_val*/
		int low = left - 1;

		for (int i = left; i <= right; ++i)
		{
			if (nums[i] < nums[right])
			{
				++low;
				swap(nums[low], nums[i]);
			}
		}

		/* Put the nums[right] to proper position */
		++low;
		swap(nums[right], nums[low]);

		pivot_idx = low;

		return pivot_idx;
	}

	void quick_sort_helper(vector<int>& nums, int left, int right)
	{
		/* if (left < right) */
		/* { */
		/* 	int pivot_idx = partition(nums, left, right); */
		/* 	quick_sort_helper(nums, left, pivot_idx - 1); */
		/* 	quick_sort_helper(nums, pivot_idx + 1, right); */
		/* } */

		while (left < right)
		{
			int pivot_idx = partition(nums, left, right);
			quick_sort_helper(nums, left, pivot_idx - 1);

			left = pivot_idx + 1;
		}
	}

    vector<int> sortArray(vector<int>& nums)
	{
		quick_sort_helper(nums, 0, nums.size() - 1);

		return nums;
    }
};


int
main(int argc, char** argv)
{
	return 0;
}
