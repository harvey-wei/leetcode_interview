#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;



class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost)
	{
		vector<int> dp = {cost[0], cost[1]};
		int curr_dp = 0;

		for (int i = 2; i< cost.size(); ++i)
		{
			// Here we do not need to differentiate the recentness of dp[0] and dp[1]
			// We can use modulo operator
			/* dp[i % 2] = cost[i] + min(dp[0], dp[1]); */
			// dp[0] -> d[1]
			// dp[0] <- dp[1]
			// dp[1] <- dp[i]
			curr_dp = cost[i] + min(dp[0], dp[1]);
			dp[0] = dp[1];
			dp[1] = curr_dp;
		}

		return min(dp[0], dp[1]);
    }
};

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
		/**
		 * SRTBOT
		 * dp[i] is the accumulative cost from 0th and jump from ith step
		 * dp[i] = cost[i] + min(dp[i -1], dp[i-2])
		 * dp[0] = cost[0]
		 * dp[1] = cost[1]
		 */
		vector<int> dp = {cost[0], cost[1]};

		for (int i = 2; i < cost.size(); ++i)
		{
			/* i % 2 replace the older one of the last two in the dp*/
			dp[i % 2] = cost[i] + min(dp[0], dp[1]);
		}

		/* note that dp[1] is not necessarily dp[cost.size() - 1]*/
		return min(dp[0], dp[1]);
    }
};

int main()
{
	return 0;
}
