#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>
using namespace std;

/* ref: https://www.geeksforgeeks.org/stdstring-class-in-c/ */
class Solution {
public:
    string addBinary(string a, string b)
    {
        assert(a.length() >= 1u && b.length() >= 1u);

        string s="";

        int idx_a = a.length() - 1;
        int idx_b = b.length() - 1;
        int carry = 0;
        while (true)
        {
            /*Terminate when both idx are < 0*/
            if (idx_a < 0 && idx_b < 0) break;

            /* Perform bitwise addition of binary. */
            int a_val = idx_a >= 0 ? a[idx_a] - '0' : 0;
            int b_val = idx_b >= 0 ? b[idx_b] - '0' : 0;
            int bit_sum = a_val + b_val + carry;
            if (3 == bit_sum)
            {
                carry = 1;
                s.push_back('1');
            }
            else if (2 == bit_sum)
            {
                carry = 1;
                s.push_back('0');
            }
            else
            {
                /* bit_sum == 0 or 1 no caryy */
                carry = 0;
                s.push_back(char('0'+ (bit_sum)));
            }

            /*update the idx */
            --idx_a;
            --idx_b;
        }

        /* Might produce more one bit. */
        if (1 == carry)
        {
            s.push_back('1');
        }

        std::reverse(s.begin(), s.end());

        return s;
    }
};

int main()
{
    Solution sol;
    /* string a ="1010"; */
    /* string b = "1011"; */
    string a = "1111";
    string b = "1111";
    string s = sol.addBinary(a, b);
    std::cout << a << " + " << b << " = " << s << std::endl;

    /* https://stackoverflow.com/questions/4951796/how-to-reverse-an-stdstring */
    /* https://www.geeksforgeeks.org/stdstring-class-in-c/ */
    /* string a = "12344"; */
    /* a[0] = 'b'; */
    /* /1* a = ""; *1/ */
    /* /1* a.resize(20);  // Will change the length of string! *1/ */
    /* std::cout << a << std::endl; */
    /* std::cout << "a.length() " << a.length() << std::endl; */

    /* for (int i = a.length() -1; i >= 0; --i) */
    /* { */
    /*     std::cout << a[i] << std::endl; */
    /* } */

    /* char char_var = 'a'; */
    /* std::cout << "char_var: " << char(char_var + 2) << std::endl; */

    /* std::reverse(a.begin(), a.end()); */
    /* std::cout << "a.reserve() " << a << std::endl; */

    return 0;
}
