#include <vector>
#include <algorithm>

using namespace std;


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



class Solution {
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
