#include <vector>

using namespace std;

class Solution_ {
public:
    int singleNonDuplicate(vector<int>& nums)
	{
		/**
		 *     (1, 1) (2, 2,) (3,)
		 * 1st  0      2       4=n -1
		 *      0x0    2x1     2x2
		 * k      0      1       2 = (n - 1) / 2
		 * order: same , same, diff, diff
		 * corner case: last single is the single
		 */
		int n = nums.size();

		// Pair ID: [l, r)
		int l = 0;
		int r = (n + 1) / 2; // (n - 1) / 2 + 1
		int m = 0;

		while (r  > l)
		{
			// m is ensure [l, r)
			m = l + (r -l) / 2;

			int first = 2 * m;

			if ((first + 1 == n) || (nums[first] != nums[first + 1]))
			{
				// m is diff group
				if (m -  1 < 0)
				{
					// this diff group is the first group.
					return nums[first];
				}
				else
				{
					// check left group
					// m -  1 > 0
					if (nums[2 * m - 2] == nums[2 * m - 1])
					{
						// left is same group -> m is the first diff group
						return nums[first];
					}
					else
					{
						// search the left half
						r = m; // exclusive

					}
				}

			}
			else
			{
				// first + 1 < n && m is same group
				// go right
				l = m  + 1; // inclusive

			}
		}

		return -1;
    }
};



class Solution {
public:
    int singleNonDuplicate(vector<int>& nums)
	{
		/**
		 *     (1, 1) (2, 2,) (3,)
		 * 1st  0      2       4=n -1
		 *      0x0    2x1     2x2
		 * k      0      1       2 = (n - 1) / 2
		 * order: same , same, diff, diff
		 * corner case: last single is the single
		 */
		int n = nums.size();

		// Pair ID: [l, r)
		int l = 0;
		int r = (n + 1) / 2; // (n - 1) / 2 + 1
		int m = 0;

		while (r  > l)
		{
			// m is ensure [l, r)
			m = l + (r -l) / 2;

			int first = 2 * m;

			if ((first + 1 == n) || (nums[first] != nums[first + 1]))
			{
				// m is diff group
				if (m -  1 < 0 || (nums[2 * m - 2] == nums[2 * m - 1]))
				{
					// this diff group is the first group.
					return nums[first];
				}
				else
				{
						// search the left half
						r = m; // exclusive
				}
			}
			else
			{
				// first + 1 < n && m is same group
				// go right
				l = m  + 1; // inclusive
			}
		}

		return -1;
    }
};
