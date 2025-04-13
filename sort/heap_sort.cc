#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int left_child(int i)
	{
		return 2 * i + 1;
	}

	int right_child(int i)
	{
		return 2 * i + 2;
	}

	void sift_down(vector<int>& nums, int n, int i)
	{
		/*nums[0, n) is for the heap*/
		int left = left_child(i);
		int right = right_child(i);

		/* Find the max number index of i, left, and rgiht*/
		int max_idx = i;

		if (left < n && nums[left] > nums[max_idx])
		{
			max_idx = left;
		}

		if (right < n && nums[right] > nums[max_idx])
		{
			max_idx = right;
		}

		if (max_idx != i)
		{
			swap(nums[i], nums[max_idx]);

			/* fix down Recursively*/
			sift_down(nums, n, max_idx);
		}
	}

	void build_heap(vector<int>& nums, int n)
	{
		/* nums[0, n) is for the heap */
		/*i = floor(n / 2) - 1 to 0 is for non leaf*/

		/* We build max-heap by sift_down from level to leaf*/
		for (int i = n / 2 - 1; i >= 0; --i)
		{
			sift_down(nums, n, i);
		}
	}

	/* Time: O(nlogn)
	 * Space: stack depth O(logn)
	 */
	void heap_sort(vector<int>& nums)
	{
		build_heap(nums, nums.size());

		for (int i = nums.size() - 1;  i >= 0; --i)
		{
			// get the ith laragest
			swap(nums[0], nums[i]);

			// consider nums[0, i) as heap, nums[i:] already right
			// 0th maight be problemantic fix it by sift_down
			sift_down(nums, i, 0);
		}
	}

    vector<int> sortArray(vector<int>& nums)
	{
		heap_sort(nums);

		return nums;
    }
};

/**
 * \ref https://leetcode.com/problems/sort-an-array/editorial/
 */
class Solution_ {
    // Function to heapify a subtree (in top-down order) rooted at index i.
    void heapify(vector<int>& arr, int n, int i) {
        // Initialize largest as root 'i'.
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // If left child is larger than root.
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        // If right child is larger than largest so far.
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        // If largest is not root swap root with largest element
        // Recursively heapify the affected sub-tree (i.e. move down).
        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    void heapSort(vector<int>& arr) {
        int n = arr.size();
        // Build heap; heapify (top-down) all elements except leaf nodes.
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // Traverse elements one by one, to move current root to end, and
        for (int i = n - 1; i >= 0; i--) {
            swap(arr[0], arr[i]);
            // call max heapify on the reduced heap.
            heapify(arr, i, 0);
        }
    }

public:
    vector<int> sortArray(vector<int>& nums) {
        heapSort(nums);
        return nums;
    }
};



class Solution__ {
public:
 	void heapify(vector<int>& nums, int n, int i)
	{
		/* Max-heap property: for each eadge, the parent node value >= its child values. */
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		int largest = i;

		/* Find the largest node. */
		/* Besure to check the boundary of left and right node index. */
		if (left < n && nums[left] > nums[largest])
		{
			largest = left;
		}

		if (right < n && nums[right] > nums[largest])
		{
			largest = right;
		}

		if (i != largest)
		{
			swap(nums[i], nums[largest]);

			/* Fix the afftected subtrees rooted at index largest */
			heapify(nums, n, largest);
		}
	}

	/* Time: O(nlogn)
	 * Space: stack depth O(logn)
	 */
	void heap_sort(vector<int>& nums)
	{
		/* Build the heap by sift-downing(heapify)gggall elements except leaf nodes. */
		/* Build the max heap from bottom to up. */
		/* Non-leaf node position is n/2 -1 to .. 0 where 0 is the root*/
		int n = nums.size();

		/* Build the heap  from last non-left node from bottom to up. */
		// O(nlogn)
		for (int i = n / 2 - 1; i >= 0; --i)
		{
			heapify(nums, n, i);
		}

		// O(nlogn)
		for (int i = n - 1; i >= 0; --i)
		{
			/* Push the current max to the end */
			swap(nums[0], nums[i]);

			/* sift down the root node at index of 0 */
			/* 0 .... i - 1 is the new heap whose array is of length i */
			heapify(nums, i, 0);
		}
	}

    vector<int> sortArray(vector<int>& nums)
	{
		heap_sort(nums);

		return nums;
    }
};

int main()
{
	return 0;
}
