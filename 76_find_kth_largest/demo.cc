#include <vector>
#include <iostream>
#include <random>
#include <algorithm>
#include <utility>

using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k)
	{
		/* target_idxth element in sorted nums by in non-decreasing order*/
		int target_idx = nums.size() - k;

		int left = 0;
		int right = nums.size() - 1;

		int idx = partition(nums, left, right);

		while(target_idx != idx)
		{
			if (idx < target_idx)
			{
				idx = partition(nums, idx + 1, right);
			}
			else
			{
				/* idx > target_idx */
				idx = partition(nums, left, idx - 1);
			}
		}

		return nums[target_idx];
    }

private:
	int partition(vector<int>& nums, int left, int right)
	{
		/* Picup pivot index from [left...right] */
		int pivot_idx = rand() % (right - left + 1) + left;
		int pivot_val = nums[pivot_idx];

		/* Put pivot to position indexed by right*/
		swap(nums[pivot_idx], nums[right]);

		/**
		 * Loop invariant: nums[left...smaller] < pivot_val for nums[left..i]
		 * nums[smaller + 1,...i] >= pivot_val
		 */
		int smaller = left - 1;
		for (int i = left; i < right; ++i)
		{
			if (nums[i] < pivot_val)
			{
				++smaller;
				swap(nums[smaller], nums[i]);
			}
		}

		swap(nums[++smaller], nums[right]);

		// smaller is the correct index for pivot_val
		return smaller;

	}
};

int
main()
{
	return 0;
}
