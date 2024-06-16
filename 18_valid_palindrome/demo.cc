#include <iostream>
#include <string>
#include <cctype> //


using namespace std;

class SolutionIter {
public:
    bool isPalindrome(string s)
    {
        int l = 0;
        int r = s.size() - 1;

        /* Instead of skipp all non-alphanumerics. */
        /* We could move one step at a time to use the while condition. */
        while (l <= r)
        {
            if (!isalnum(s[l]))
            {
                ++l;
            }
            else if (!isalnum(s[r]))
            {
                --r;
            }
            else if (tolower(s[l]) != tolower(s[r]))
            {
                // Both s[l] and s[r] are alphanumerics;
                return false;
            }
            else
            {
                // Both s[l] and s[r] are alphanumerics and identical.
                ++l;
                --r;
            }
        }

        return true;
    }
};


class Solution
{
    public:
    bool isPalindromeRecur(const string& s, int l , int r)
    {
        // base case
        if (l >= r)
        {
            // Single alphanumeric is palindrome
            // skip non-alphanumeric -> empty is palindrome.
            return true;
        }
        else if (!isalnum(s[l]))
        {
            return isPalindromeRecur(s, ++l, r);
        }
        else if (!isalnum(s[r]))
        {
            return isPalindromeRecur(s, l, --r);
        }
        else if (tolower(s[l]) == tolower(s[r]))
        {
            return isPalindromeRecur(s, ++l, --r);
        }
        else
        {
            return false;
        }
    }

    bool isPalindrome(string s)
    {
        if (s.size() == 0) return true;

        return isPalindromeRecur(s, 0, s.size() - 1);
    }
};
