#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target)
	{
		/**
		 * [l,r), m = l + (r - l) / 2
		 * (r -l) = length of search interval.
		 * Hence r > l -> continue search
		 * if no target, l is the proper postion, check by an example
		 */
		int l = 0;
		int r = nums.size();
		int m = 0;

		while (r > l)
		{
			m = l + (r - l) / 2;

			if (nums[m] == target)
			{
				return m;
			}
			else if (nums[m] < target)
			{
				l = m + 1; // inclusive
			}
			else
			{
				/*nums[m] > target */
				r = m; //inclusive
			}
		}

		return l;

    }
};
