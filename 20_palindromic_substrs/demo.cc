#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    int palindrome_grow(const string &s, const int &l, const int &r)
    {
        int count = 0;
        int start = l;
        int end = r;
        while ((start >= 0) && (end < s.length()) && (start <= end))
        {
            if (s[start] == s[end])
            {
                count += 1;
            }
            else
            {
                break;
            }

            --start;
            ++end;
        }

        return count;
    }

    int countSubstrings(string s)
    {
        /* Time: O(N * N)*/
        /* Palindrome growing from one or two center characters. */
        int count = 0;
        for (int i = 0; i < s.length(); ++i)
        {
            /* expand from i */
            count += palindrome_grow(s, i, i);

            /* expand from i and i + 1 ( < s.length())*/
            count += palindrome_grow(s, i, i + 1); // palindrome_grow will check the boundary.
        }

        return count;
    }
};

int main()
{
    Solution sol;
    string s_one = "abc";
    string s_two = "aaa";

    cout << sol.countSubstrings(s_one) << endl;
    cout << sol.countSubstrings(s_two) << endl;


    return 0;
}
