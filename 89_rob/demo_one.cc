#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(2);
        dp[0] = nums[0];

        if (n > 1)
        {
            dp[1] = max<int>(nums[0], nums[1]);
        }

        for (int i = 2; i < n; ++i)
        {
            dp[i % 2] = max<int>(nums[i] + dp[(i - 2) % 2], dp[(i - 1) % 2]);
        }

        return dp[(n - 1) % 2];
    }
};
