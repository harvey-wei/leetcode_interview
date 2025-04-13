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

		// [l, r)
		int l = 0;
		int r = nums.size();

		/* Put right number at position at target_idx in the array*/
		/*nums(m1, m2] == pivot*/
		int m1, m2;
		partition3(nums, l, r, m1, m2);

		while (!(target_idx > m1 && target_idx <= m2))
		{
			if (target_idx <= m1)
			{
				r = m1 + 1; //  exlusive
				partition3(nums, l, r, m1, m2);
			}
			else if (target_idx > m2)
			{
				l = m2 + 1; // inclusive
				partition3(nums, l, r, m1, m2);
			}
		}

		return nums[target_idx];
    }

private:
	void partition3(vector<int>& nums, int l, int r, int& m1, int& m2)
	{
		/**
		 * nums[l, r) is to partitioned into 3 parts.
		 * nums[l, m1] < pivot, nums(m1, m2] == pivot , nums(m2, r) >
		 */
		int pivot_idx = rand() % (r - l) + l;

		// Move pivot to  nums[r - 1]
		swap(nums[pivot_idx], nums[r - 1]);

		m1 = l - 1;
		m2 = m1;

		for (int i = l; i < r; ++i)
		{
			if (nums[i] < nums[r - 1])
			{
				++m1;
				++m2;

				swap(nums[i], nums[m1]);

				if (m2 - m1 > 0)
				{
					/* pivot is swaped to ith position */
					/* swap to m2*/
					swap(nums[i], nums[m2]);
				}
			}
			else if (nums[i] == nums[r - 1])
			{
				++m2;
				swap(nums[i], nums[m2]);
			}
		}
	}
};


class Solution_ {
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
	void partition3(vector<int>& nums, int l, int r, int& m1, int& m2)
	{
		/**
		 * nums[l, r) is to partitioned into 3 parts.
		 * nums[l, m1] < pivot, nums(m1, m2] == pivot , nums(m2, r) >
		 */
		int pivot_idx = rand() % (r - l) + l;

		// Move pivot to  nums[r - 1]
		swap(nums[pivot_idx], nums[r - 1]);

		m1 = l - 1;
		m2 = m1;

		for (int i = l; i < r; ++i)
		{
			if (nums[i] < nums[r - 1])
			{
				++m1;
				++m2;

				swap(nums[i], nums[m1]);

				if (m2 - m1 > 0)
				{
					/* pivot is swaped to ith position */
					/* swap to m2*/
					swap(nums[i], nums[m2]);
				}
			}
			else if (nums[i] == nums[r - 1])
			{
				++m2;
				swap(nums[i], nums[m2]);
			}
		}
	}

	/* If not considering the equal elements, this bi-partition is quite slow!*/
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
