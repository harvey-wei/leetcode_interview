#include <vector>
#include <iostream>

class Solution
{
    public:
        int mySqrt(int x)
        {
            /**
             * x is non-negative integer.
             * floor(sqrt(x))
             * y = sqrt(x) <-> y * y == x
             * int y means y * y <= x AND (y + 1) * (y + 1) > x
             */
            if (0 == x || 1 == x) return x;

            /* x >= 2 */
            /* y >= 1 AND y < x */
            /* [l, r) */
            long int l = 1;
            long int r = x;
            long int m;

            while (r - l > 0)
            {
                m = l + (r - l ) / 2;

                // Treat m as left
                if (m * m <= x)
                {
                    if ((m + 1) * (m + 1) > x)
                    {
                        return m;
                    }
                    else
                    {
                        // (m + 1)^2 <= x, l = m + 1 is inclusive
                        l = m + 1;
                    }
                }
                else
                {
                    /* m * m > x, m is exclusive. */
                    r = m;
                }

            }

            return -1;
        }

};

class Solution_ {
public:
    int mySqrt(int x) {
        /* x is non-negative integer 0 */
        /* y = sqrt(x) <-> y * y = x */

        if (0 == x || 1 == x) return x;

        /* x >= 1 */
        /* y >=1 and <= x */
        /* We need find y such that y * y  == x */
        /* y * y is monotonically increasing for positve ints */

        /* [l, r)  we take int <= sqrt(x) */
        int l = 1;
        int r = x;

        /* Ideally, l ==  sqrt(x)*/

        while (r - l > 0)
        {
            int m = l + (r - l) / 2; // m >= l

            if (m * m <= x)
            {
                // [m, m + 1)
                if (x < (m + 1) * (m + 1))
                {
                    return m;
                }
                else
                {
                    // m is too small, m + 1 is inclusive
                    l = m + 1;
                }
            }
            else
            {
                /* m * m > x, r is exclusive*/
                r = m;
            }

        }
    return  -1;
    }
};


int
main()
{
    Solution sol;

    int x = 0;
    std::cout << "sqrt of " << x << " is " << sol.mySqrt(x) << std::endl;

    x = 1;
    std::cout << "sqrt of " << x << " is " << sol.mySqrt(x) << std::endl;

    x = 2;
    std::cout << "sqrt of " << x << " is " << sol.mySqrt(x) << std::endl;

    x = 4;
    std::cout << "sqrt of " << x << " is " << sol.mySqrt(x) << std::endl;

    x = 2147395599;
    std::cout << "sqrt of " << x << " is " << sol.mySqrt(x) << std::endl;
}
