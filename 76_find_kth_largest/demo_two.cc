#include <queue>
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

class Solution_ {
public:
    int findKthLargest(vector<int>& nums, int k) {
		priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

		/* Time: O(nlogk)*/
		/* Space: O(k) with k elements in array*/
		for (const auto& num : nums)
		{
			if (min_heap.size() < k)
			{
				min_heap.push(num);
			}
			else
			{
				/* Loop invariant: top k largest nums up to now. */
				if (num > min_heap.top())
				{
					/*O(logk)*/
					min_heap.pop();
					min_heap.push(num);
				}
			}
		}

		return min_heap.top();
    }
};


class Solution__ {
public:
	int partition(vector<int>& nums, int l, int r)
	{
		/* [l, r] */
		/* len = r - l + 1 , start index is l*/
		/* Note that percentage is modulo operator!! */
		int len = r - l + 1;
		int pivot_idx = rand() % len + l;

		/* put pivot to nums[r]*/
		swap(nums[pivot_idx], nums[r]);

		int m = l - 1;
		/* loop invariant: nums[l---m] < pivot <= nums[m+1 --- r]*/
		for (int i = l; i < r; ++i)
		{
			if (nums[i] < nums[r])
			{
				++m;
				swap(nums[i], nums[m]);
			}
		}

		++m;
		swap(nums[m], nums[r]);

		return m;

	}

    int findKthLargest(vector<int>& nums, int k)
	{
		/* target is to find the (n-k)th num */
		int pivot = -1;
		int l = 0;
		int r = nums.size() - 1;
		int target_idx = nums.size() - k;
		while (l <= r)
		{
			pivot = partition(nums, l, r);

			if (target_idx == pivot)
			{
				break;
			}
			else if (pivot < target_idx)
			{
				l = pivot + 1;
			}
			else
			{
				r = pivot - 1;
			}
		}

		return nums[pivot];
    }
};


class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, k);
    }

    int quickSelect(vector<int>& nums, int k) {
        int pivot = nums[rand() % nums.size()];

        vector<int> left;
        vector<int> mid;
        vector<int> right;

        for (int num: nums) {
            if (num > pivot) {
                left.push_back(num);
            } else if (num < pivot) {
                right.push_back(num);
            } else {
                mid.push_back(num);
            }
        }

        if (k <= left.size()) {
            return quickSelect(left, k);
        }

        if (left.size() + mid.size() < k) {
            return quickSelect(right, k - left.size() - mid.size());
        }

        return pivot;

    }
};


int
main()
{
	std::vector<int> nums = {3, 2, 1, 5, 6, 4};
	int k = 2;
	Solution sol;
	std::cout << k << "th: " << sol.findKthLargest(nums, k) << std::endl;
	return 0;
}
