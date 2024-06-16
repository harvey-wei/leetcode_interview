#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution
{
public:
    string addBinary(string a, string b)
    {
        string sum = ""; // empty

        int bit_sum = 0;
        int carry = 0;

        /* Start at the least significant bit. */
        int a_idx = a.size() - 1;
        int b_idx = b.size() - 1;

        while (a_idx >= 0 || b_idx >= 0)
        {
            /* bit_sum = a[a_idx] + b[b_idx] + carry. */
            /* Work with ASCII code to get the value of digital character. */
            /* Work with ASCII code to convert number char to char. */
            bit_sum = (a_idx >= 0 ? a[a_idx] - '0' : 0) +
                    (b_idx >= 0 ? b[b_idx] - '0' : 0) + carry;

            /*
             * bit_sum = 0 -> carry = 0 curr_sum = 0
             * bit_sum = 1 -> carry = 0 curr_sum = 1
             * bit_sum = 2 -> carry = 1 curr_sum = 0
             * bit_sum = 3 -> carry = 1 curr_sum = 1
             */
            if (2 == bit_sum)
            {
                carry = 1;
                sum.push_back('0');
            }
            else if (3 == bit_sum)
            {
                carry = 1;
                sum.push_back('1');
            }
            else
            {
                carry = 0;
                sum.push_back('0' + bit_sum);
            }

            /* Decrement a_idx and b_idx */
            --a_idx;
            --b_idx;
        }

        /* Check if carry is zero! */
        if (1 == carry)
        {
            sum.push_back('1');
        }

        std::reverse(sum.begin(), sum.end());

        return sum;
    }
};


int
main()
{
    Solution sol;
    string a = "11", b = "1";
    std::cout << "sum: " << sol.addBinary(a, b) << std::endl;

    a = "1010";
    b = "1011";
    std::cout << "sum: " << sol.addBinary(a, b) << std::endl;

    return 0;
}
