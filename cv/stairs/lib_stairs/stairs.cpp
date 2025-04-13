#include <iostream>
#include <vector>
#include "stairs.h"


int
total_possibilities(int n)
{
    /*
     * 0, 1, ..., (n-1)th step
     * dp[i] is the number of possibilities from 0 to ith step
     * dp[i] = dp[i - 1] + dp[i - 2]
     * dp[0] = 1
     * dp[1] = 2
     * check dp[2] = 1 + 2 = 3
     */
    /* std::vector<int> dp(n, 0); */
    /* dp[0] = 1; */
    /* dp[1] = 2; */

    if (n <= 2)  return n;

    int prev = 1;
    int curr = 2;

    for (int i = 2; i < n; ++i)
    {
        /* dp[i] = dp[i - 1] + dp[i - 2]; */
        int temp = curr;
        curr = prev + curr;
        prev = temp;
    }

    /* return dp[n - 1]; */
    return curr;
}


