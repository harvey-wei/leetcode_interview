#include <iostream>
#include <vector>

using namespace std;

int max_square(std::vector<std::vector<int>>& mat)
{
    /* 1 for s */
    int rows = mat.size();
    int cols = mat[0].size();

    std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, 0));
    int max_len = 0;

    /* Handle the boundary. */
    for (int c = 0; c < cols; ++c)
    {
        if (mat[0][c] == 0)
        {
            dp[0][c] = 1;
            max_len = 1;
        }
    }

    for (int r = 0; r < rows; ++r)
    {
        if (mat[r][0] == 0)
        {
            dp[r][0] = 1;
            max_len = 1;
        }
    }

    for (int r = 1; r < rows; ++r)
    {
        for (int c = 1;  c < cols; ++c)
        {
            if (0 == mat[r][c])
            {
                dp[r][c] = 1 + min(min(dp[r-1][c], dp[r-1][c-1]), dp[r][c-1]);
                max_len = max(dp[r][c], max_len);
            }
        }
    }

    return max_len;
}

int main()
{
    return 0;
}
