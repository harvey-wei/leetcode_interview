#include <climits>
#include <cassert>
#include <iostream>
#include <random>

/* https://leetcode.com/problems/divide-two-integers */

class Solution {
public:
    int divide_smart_naive(int dividend, int divisor) {
        /* Linear Search is too slow because at each step, we only subtract one copy of the divisor
           from the dividend. */
        assert(divisor != 0);

        // Special case: -2^31 / -1 = 2^31 which is out of the range [-2^31, 2^31- 1]
        if (INT_MIN == dividend && -1 == divisor)
        {
            return INT_MAX;
        }

        // To use the largest possible range of integers, we instead work with negatives.
        int num_of_negatives = 2;

        if (dividend > 0)
        {
           --num_of_negatives;
           dividend = -dividend;
        }

        if (divisor > 0)
        {
            --num_of_negatives;
            divisor = -divisor;
        }

        int quotient = 0;
        while (dividend <= divisor)
        {
            dividend -= divisor;
            --quotient; // work with negatives
        }

        if (1 != num_of_negatives)
        {
            return -quotient;
        }

        return quotient;
    }

    int int_divide_exp_search(int dividend, int divisor)
    {
        assert(0 != divisor);

        /* Corner case: Overflow INT_MIN / -1 = INT_MAX + 1*/
        if (INT_MIN == dividend && -1 == divisor)
        {
            return INT_MAX;
        }

        /* Convert both dividend and divisor to negatives to leverage the larger range of neg. */
        int num_of_neg = 2;

        if (dividend > 0)
        {
            dividend = -dividend;
            --num_of_neg;
        }

        if (divisor > 0)
        {
            divisor = -divisor;
            --num_of_neg;
        }

        /* Find the largest powers of two multiple of divisor which can fit into the dividend */
        int quotient =0;

        /* <= is because we work with negatives. */
        /* (x<<y)’ is equivalent to multiplying x with 2^y (2 raised to power y).*/
        /* ‘(x>>y)‘ is equivalent to dividing x by 2^y */
        /* Havling without division.
           Add 1 before doing the bit-shift by 1 bit on a negative number to get the halve*/
        /* Doubling without multiplication. */
        const int half_int_min = (INT_MIN + 1) >> 1; // >> 1 instead of 2
        /* (logn)^2*/
        /* Terminate when dividend < divisor for positive. */
        /* For negative, terminate if dividend > divisor */
        while (dividend <= divisor)
        {
            /* log n*/
            int curr_val = divisor;
            int powers_of_two = -1;

            /* Double should avoid overflow of negatives */
            /* log n*/
            while(curr_val >= half_int_min && (curr_val + curr_val) >= dividend)
            {
                /* Double without multiplication.*/
                curr_val += curr_val;
                powers_of_two += powers_of_two;
            }

            quotient += powers_of_two;
            /* Update the dividend */
            dividend -= curr_val;

            /* Prove by contradiction. If difference is <=  curr_val, then we can double curr_val
               once again! Recall we work with negative but think for positives. */
            assert(dividend > curr_val);
        }

        if (num_of_neg != 1)
        {
            quotient = -quotient;
        }

        return quotient;
    }

    int int_divide_exp_search_precompute(int dividend, int divisor)
    {
        assert(0 != divisor);

        /* Corner case: Overflow INT_MIN / -1 = INT_MAX + 1*/
        if (INT_MIN == dividend && -1 == divisor)
        {
            return INT_MAX;
        }

        /* Convert both dividend and divisor to negatives to leverage the larger range of neg. */
        int num_of_neg = 2;

        if (dividend > 0)
        {
            dividend = -dividend;
            --num_of_neg;
        }

        if (divisor > 0)
        {
            divisor = -divisor;
            --num_of_neg;
        }

        /* Find the largest powers of two multiple of divisor which fit into dividend. */
        /* And then pre-compute the powers_of_two and store them in an array for looking-up. */
        std::vector<int> powers_of_two; // for  quotient
        std::vector<int> doubles; // for double of divisor
        int power_of_two = -1;
        const int half_int_min = (INT_MIN + 1) >> 1;
        int curr_val = divisor; // double of it should >= INT_MIN -> curr_val >= half_int_min
        doubles.push_back(divisor);
        powers_of_two.push_back(power_of_two);
        /*Double before ensuring no overflow! */
        while(curr_val >= half_int_min && (curr_val + curr_val >= dividend))
        {
            curr_val += curr_val;
            power_of_two += power_of_two;
            doubles.push_back(curr_val);
            powers_of_two.push_back(power_of_two);
        }

        /* Key insight: difference = dividend - largest double < largest double if all are
           positives. Think in positives! Hence, we can subtract the doubles from largest to
           smallest. But you should check to see if dividend >= doubles[i]. */
        /* More space-efficiently, we do not need to store them in an array. */

        int quotient = 0;
        for (int i = doubles.size() - 1; i >= 0; --i)
        {
            /* Each double in doubles are used at most once! -> No need to store them all! */
            if (dividend <= doubles[i])
            {
                dividend -= doubles[i];
                quotient += powers_of_two[i];
            }
        }

        if (1 != num_of_neg)
        {
            quotient = -quotient;
        }

        return quotient;
    }

        int divide(int dividend, int divisor)
        {
            assert(divisor != 0);
            /*
               1. double A by A + A;
               2. halve A by
               (A + 1) >> 1 if A is negative
               A >> 1 if A is positive
               3. Key insight: difference = dividend - largest double < largest double if all are
               4. Termination: if |dividend| < |current double of divisors|
               5. Check underflow before double
               2 * neg_int >= INT_MIN => neg_int >= int_min_half (= (INT_MIN + 1) >> 1)

               Work with negatives but Think in positives.
            */

            /* Corner case: INT_MIN / -1 = INT_MAX + 1 -> quotient is overflowing!*/
            if (INT_MIN == dividend && -1 == divisor)
            {
                return INT_MAX;
            }

            /* Work with negatives to leverage the larger range of negatives. */
            int num_of_neg = 2;  // Max. cnt of negs.

            if (dividend > 0)
            {
                dividend = -dividend;
                --num_of_neg;
            }

            if (divisor > 0)
            {
                divisor = -divisor;
                --num_of_neg;
            }

            /* Find the largest double of divisors. Thinking in positives! */
            int largest_double = divisor;
            // INT_MIN / 1 = INT_MIN in which case, largest_power_of_two == INT_MIN.
            // Hence, you can not use 1!
            int largest_power_of_two = -1;
            const int half_int_min = (INT_MIN + 1) >> 1;

            /* 2 * double >= INT_MIN -> double > half_int_min */
            /*
               When to stop?
               largest_double < half_int_min
               OR largest_double + largest_double WILL >= dividend (all in negative )
            */
            while (largest_double >= half_int_min && (largest_double + largest_double) >= dividend)
            {
                largest_double += largest_double;
                largest_power_of_two += largest_power_of_two;
            }

            int quotient = 0;
            /* Key insight: difference = dividend - largest double < largest double if all are
               positives. Think in positives! Hence, we can subtract the doubles from largest to
               smallest. But you should check to see if dividend >= doubles[i]. */
            /* When to terminate? |dividend| < |divisor| */
            /* Here, we maintain the value of divisor and update divident and largest_double*/
            while (divisor >= dividend)
            {
                if (dividend <= largest_double)
                {
                    dividend -= largest_double;
                    quotient += largest_power_of_two;
                }
                /* Even if largest_double is not doubled. No effect */
                largest_double = (largest_double + 1) >> 1;
                largest_power_of_two >>= 1;
            }

            if (1 != num_of_neg)
            {
                quotient = -quotient;
            }

            return quotient;

        }

    int divide_(int dividend, int divisor)
    {
        /* Overflow Case: INT_MIN / -1 = INT_MAX + 1*/
        if (INT_MIN == dividend && -1 == divisor)
        {
            return INT_MAX;
        }

        /* Convert positive to negative to leverage the larger range of negative integer. */
        int num_of_neg = 2;

        if (dividend > 0)
        {
            --num_of_neg;
            dividend = -dividend;
        }

        if (divisor > 0)
        {
            --num_of_neg;
            divisor = - divisor;
        }

        /* Find the largest doubles of divisor not exceeding dividend. */
        int int_min_half = (INT_MIN + 1) >> 1; // using right shift instead of * 0.5
        int largest_double = divisor;
        int largest_power_of_two = -1; // To address the case INT_MIN / 1 = INT_MIN.

        /* Note that we work with negatives from this point on.  Think in absolute values. */
        /* Check out-of-range before doubling! */
        /*largest_double + largest_double may be underflow. Hence, we check the half!*/
        while (largest_double >= int_min_half && (largest_double + largest_double) >= dividend)
        {
            largest_double += largest_double;
            largest_power_of_two += largest_power_of_two;
        }

        /* Subtract from largest double and its haleves. */
        /* Again, we work with negatives. */
        int quotient = 0;
        while (dividend <= divisor)
        {

            /* dividend < largest_double is ensured  but divident can also < largest_double / 2*/
            /* see the example in the leetcode tutorial. */
            if (dividend <= largest_double)
            {
                dividend -= largest_double;
                quotient += largest_power_of_two;
            }

            largest_double = (largest_double + 1) >> 1;
            largest_power_of_two = (largest_power_of_two + 1) >> 1;

        }

        if (1 != num_of_neg)
        {
            quotient = -quotient;
        }

        return quotient;
    }

    void
    stress_test()
    {
        std::random_device rd; // for seeding
        std::mt19937 rng(rd()); // seed the random number generator by calling rd()
        // specify the distribution
        std::uniform_int_distribution<int> uniform_int_dist(INT_MIN, INT_MAX); // inclusive

        while (true)
        {
            /* pass rng instead of calling*/
            int dividend = uniform_int_dist(rng);
            int divisor = uniform_int_dist(rng);
            if (0 == divisor) continue;

            int real_q = divide_smart_naive(dividend, divisor);
            /* int real_q = dividend / divisor; // integer division */
            /* int q = int_divide_exp_search(dividend, divisor); */
            /* int q = int_divide_exp_search_precompute(dividend, divisor); */
            int q = divide(dividend, divisor);

            if (real_q != q)
            {
                std::cout << "Failed on test: " << dividend << " / " << divisor << std::endl;
                break;
            }
            else
            {
                std::cout << "Succeeded on test: " << dividend << " / " << divisor << std::endl;
            }
        }
    }
};


int main()
{
    Solution sol;
    sol.stress_test();
    /* int q = sol.divide_smart_naive(-10, 3); */
    /* int q_ = sol.int_divide_exp_search(-10, 3); */
    /* std::cout << "quotient: " << q << std::endl; */
    /* std::cout << "quotient: " << q_ << std::endl; */

    /* Do the stress_test */
}
