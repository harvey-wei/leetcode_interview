#include <vector>
using namespace std;


class Solution {
public:
    int rob(vector<int>& nums)
	{
		/**
		 * S: f(i) = max money from 0 to i
		 * f(0) = nums[0], f(1) = max(f(0), nums[1])
		 * R: f(i) = max(f(i - 2) + nums[i], f(i - 1))
		 */
		if (1 == nums.size())  return nums[0];

		/* nums.size >= 2 */
		vector<int> dp = {nums[0], max(nums[0], nums[1])};

		for (int i = 2; i < nums.size(); ++i)
		{
			/* Modulo overwirtting acts a queue FIFO */
			dp[i % 2] = max(dp[(i - 2) % 2] + nums[i], dp[(i- 1) % 2]);
		}

		return dp[(nums.size() - 1) % 2];
    }
};
