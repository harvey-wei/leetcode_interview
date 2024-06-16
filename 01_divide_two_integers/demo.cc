#include <iostream>
#include <climits> // INT_MIN and INT_MAX
#include <cassert>
// https://leetcode.com/problems/divide-two-integers/
class Solution
{
public:
    int divide(int dividend, int divisor)
    {
        /*
         * 1. Halving a by (a + 1) >> 1
         * 2. Doubling a by a += a
         * 3. |INT_MIN| = INT_MAX + 1 -> Work with negatives to leverage the larger range of
         INT_MIN.
         * INT_MIN / -1 = INT_MAX + 1. INT_MIN / 1 = INT_MIN
         */
        assert(0 != divisor);

        /* Corner case: dividend = INT_MIN and divisor = -1 -> overflow. */
        if (INT_MIN == dividend && -1 == divisor)
        {
            return INT_MAX;
        }

        /* Convert positive to negative. */
        int neg_cnt = 2;

        if (dividend > 0)
        {
            dividend = -dividend;
            --neg_cnt;
        }

        if (divisor > 0)
        {
            divisor = -divisor;
            --neg_cnt;
        }

        /* Find the largest possible doubles of divisor to fit into the dividend. */
        int largest_double = divisor;
        int largest_powers_of_two = -1; // Address the case INT_MIN / 1 = INT_MIN

        /* Halve by +1 followed by right-shift. */
        int int_min_half = (INT_MIN + 1) >> 1;

        /* Check overflow/underflow before doubing. */
        while (largest_double >= int_min_half &&
                (largest_double + largest_double) >= dividend)
        {
            largest_double += largest_double;
            largest_powers_of_two += largest_powers_of_two; // track 2^k
        }

        std::cout << "The largest_double " << largest_double << std::endl;
        std::cout << "The largest_powers_of_two " << largest_powers_of_two << std::endl;
        std::cout << "The dividend " << dividend << std::endl;
        std::cout << "The divisor " << divisor << std::endl;

        /* Keep subtracting largest_double from dividend until |dividend| < divisor. */
        int quotient = 0;
        while (divisor >= dividend)
        {
            if (largest_double >= dividend)
            {
                dividend -= largest_double;
                quotient += largest_powers_of_two;
            }

            /* Key insight: diff = |dividend| - |largest_double| < |largest_double| */
            /* Note that largest_double might need to iteratively halved! */
            largest_double = (largest_double + 1) >> 1;
            largest_powers_of_two = (largest_powers_of_two + 1) >> 1;
        }

        if (1 != neg_cnt)
        {
            quotient = -quotient;
        }

        return quotient;
    }
};


int
main(int argc, char** argv)
{
    Solution sol;
    int dividend = 7;
    int divisor = -3;
    int quotient = sol.divide(dividend, divisor);

    std::cout << "The quotient is " << quotient << std::endl;

    dividend = 10;
    divisor = 3;
    quotient = sol.divide(dividend, divisor);

    std::cout << "The quotient is " << quotient << std::endl;
    return 0;
}
