#include <climits>
#include <limits>
#include <algorithm>


class Solution_
{
public:
    int mySqrt(int x)
	{
		/**
		 * sqrt(x) = y and x  = y * y
		 * y in [0, x + 1) which is in ascending order.
		 * by compare y * y with x, we can use binar search
		 *
		 * How to deal with the rounding down?
		 * for [l ,r) when stop l is the imaginative position for true answer
		 * hence, we l - 1
		 *
		 * y * y will be overflow
		 * except x ==0, y * y > x <=> y > x / y
		 * what if integer division
		 * x // m = x / m - 0.n
		 * x // m == m -> x == m*m + 0.n *m return m
		 * x // m > m -> x > m * m + 0.n* m > m * m  -> l = m + 1
		 * x // m < m => x < m * m + 0.n * m => x <= m *m  == has been ruled out before hand -> x  <
		 m * m r == m
		 */
		if (0 == x || 1 == x) return x;

		int l = 0;
		int r = x;
		int m = 0; // reduce the memory access

		while (r > l)
		{
			m = l + (r - l) / 2;


			if (x / m == m)
			{
				return m;
			}
			else if (x / m < m)
			{
				r = m; // exclusive
			}
			else
			{
				// x > m_square
				l = m + 1; // inclusive
			}
		}

		return l - 1;

    }
};




class Solution
{
public:
    int mySqrt(int x)
	{
		/**
		 * sqrt(x) = y and x  = y * y
		 * y in [0, x + 1) which is in ascending order.
		 * by compare y * y with x, we can use binar search
		 *
		 * How to deal with the rounding down?
		 * for [l ,r) when stop l is the imaginative position for true answer
		 * hence, we l - 1
		 *
		 * y * y will be overflow
		 * except x ==0, y * y > x <=> y > x / y
		 * what if integer division
		 * x // m = x / m - 0.n
		 * x // m == m -> x == m*m + 0.n *m return m
		 * x // m > m -> x > m * m + 0.n* m > m * m  -> l = m + 1
		 * x // m < m => x < m * m + 0.n * m => x <= m *m  == has been ruled out before hand -> x  <
		 m * m r == m
		 */

		// special case to avoid overlfow of x + 1
		if (0 == x || 1 == x)
		{
			return x;
		}

		// [l, r), m = l + (r - l) / 2 in [l, r)
		int l = 0;
		int r = x;
		int m = 0; // predefined to reduce memory access

		while (r > l)
		{
			m = l + (r - l) / 2;

			if (m == (x / m))
			{
				return m;
			}
			else if (m < (x / m))
			{
				l = m + 1; // inclusive
			}
			else
			{
				r = m; // exclusive
			}

		}

		// l is the right position but we need to round down
		return l - 1;

    }
};
