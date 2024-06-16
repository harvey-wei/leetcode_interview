#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target)
	{
		/* nums is sorted in ascending order. */
		int l = 0;
		int r = nums.size();

		/* [l, r), m = l + (r -l) / 2 */

		while (r > l)
		{
			int m = l + (r - l) / 2;

			if (nums[m] == target)
			{
				return m;
			}
			else if (nums[m] > target)
			{
				r = m; // exclusive
			}
			else
			{
				l = m + 1; // inclusive
			}
		}

		return -1;
    }
};
