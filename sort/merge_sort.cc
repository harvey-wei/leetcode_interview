#include <vector>
#include <iostream>
#include <algorithm>


using namespace std;

class Solution
{
	public:
		void merge(vector<int>& nums, int l, int m, int r)
		{
			// copy nums[l, m) and nums[m, r)
			vector<int> left_array(m - l, 0);
			vector<int> right_array(r - m, 0);

			for (int i = 0; i < m - l; ++i)
			{
				left_array[i] = nums[l + i];
			}

			for (int i = 0; i < r - m; ++i)
			{
				right_array[i] = nums[m + i];
			}

			int ptr = r;

			int ptr_left = left_array.size() - 1;
			int ptr_right = right_array.size() - 1;

			while (ptr_left >= 0 && ptr_right >= 0)
			{
				// compare
				if (left_array[ptr_left] > right_array[ptr_right])
				{
					--ptr;
					nums[ptr] = left_array[ptr_left];
					--ptr_left;
				}
				else
				{
					--ptr;
					nums[ptr] = right_array[ptr_right];
					--ptr_right;

				}
			}

			// Move the remaining left OR right array to nums
			while (ptr_left >=0 )
			{
				--ptr;
				nums[ptr] = left_array[ptr_left];
				--ptr_left;
			}

			while (ptr_right >= 0)
			{
				--ptr;
				nums[ptr] = right_array[ptr_right];
				--ptr_right;
			}
		}

		void merge_sort(vector<int>& nums, int l, int r)
		{
			/* nums[l, r) is to be sorted in ascending order. */
			if (r - l > 1)
			{
				int m = l + (r - l) / 2;

				merge_sort(nums, l, m); // sort nums[l, m)
				merge_sort(nums, m, r); // sort nums[m, r)

				merge(nums, l, m, r);
			}
		}


		vector<int> sortArray(vector<int>& nums)
		{
			merge_sort(nums, 0, nums.size());

			return nums;
		}
};

class Solution_ {
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

        vector<int> res = sol.sortArray(array_);

        for (int i = 0; i < num_cnt; ++i)
        {
            if (array[i] != res[i])
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
	/* std::vector<int> nums{6, 5, 12, 10, 9, 1}; */
	/**/
	/* Solution sol; */
	/**/
	/* nums = sol.sortArray(nums); */
	stress_test();
}


