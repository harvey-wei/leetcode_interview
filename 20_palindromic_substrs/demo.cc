#include <iostream>
#include <string>
using namespace std;

/*
 * \ref https://leetcode.com/problems/palindromic-substrings/
 */
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
            /* It is OK to check the boundary before or after increment the  index variable. */
            count += palindrome_grow(s, i, i + 1); // palindrome_grow will check the boundary.
        }

        return count;
    }
};

class SolutionTwo {
public:
    /* Grow the Palindrome from center */
    int palindrome_grow(const string& s, int start, int end)
    {
        int count = 0;

        /* start <= end is ensured in the input! */
        while (start >=0 && end < s.size())
        {
            if (s[start] == s[end])
            {
                ++count;

                --start;
                ++end;
            }
            else
            {
                break;
            }
        }

        return count;
    }

    int countSubstrings(string s)
    {
        /* string is ensured to be non-empty! */
        int count = 0;

        for (size_t i = 0; i < s.size(); ++i)
        {
            /* odd-length Palindrome */
            count += palindrome_grow(s, i, i);

            /* even-length Palindrome */
            count += palindrome_grow(s, i, i + 1);
        }

        return count;
    }
};


int main()
{
    SolutionTwo sol;
    string s_one = "abc";
    string s_two = "aaa";

    cout << sol.countSubstrings(s_one) << endl;
    cout << sol.countSubstrings(s_two) << endl;


    return 0;
}
