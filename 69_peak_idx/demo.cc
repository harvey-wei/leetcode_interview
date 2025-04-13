#include <vector>

using namespace std;


class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr)
	{
		/* arr.size() >= 3*/

		int l = 0;
		int r = arr.size(); // [l, r)
		int m = 0;

		while (r > l)
		{
			/* We can approve m >= l && m < r if r > l*/
			/* m in [l, r) if r > l*/
			m = l + (r - l) / 2;

			if (arr[m] > arr[m - 1] && arr[m] > arr[m + 1])
			{
				return m;
			}
			else if (arr[m] < arr[m - 1])
			{
				r = m; // exlusive
			}
			else
			{
				l = m + 1; // inclusive
			}

		}

		return -1;
    }
};
