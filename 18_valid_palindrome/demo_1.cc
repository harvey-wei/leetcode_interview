#include <iostream>
#include <string>
#include <cctype>
using namespace std;
/*
   https://www.programiz.com/c-programming/library-function/ctype.h
   ref:https://leetcode.com/problems/valid-palindrome/
*/

class Solution {
public:
    bool isPalindrome_recur(const string& s, int l, int r)
    {
        /* base case */
        if (l == r) return true;

        /* skip non alphanumeric char*/
        while (l <= r && !isalnum(s[l]))
        {
            ++l;
        }

        /* skip non alphanumeric char */
        while (l <= r && !isalnum(s[r]))
        {
            --r;
        }

        /* At least one of s[l] and s[r] can not be alphanumeric!  Single Char is still palindrome*/
        if (l > r) return true;

        if (tolower(s[l]) == tolower(s[r]))
        {
            return isPalindrome_recur(s, ++l, --r);
        }
        else
        {
            return false;
        }
    }

    bool isPalindrome(string s)
    {
        return isPalindrome_recur(s, 0, s.size() - 1);
    }

    bool isPalindrome___(string s)
    {
        int l = 0;
        int r = s.size() -1;

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
                return false;
            }
            else
            {
                /* s[l] == s[r] */
                /* Do not forget to update l and r pointers! */
                ++l;
                --r;
            }

        }

        return true;
    }

    bool isPalindrome__(string s) {
        int left = 0;
        int right = s.length() - 1;

        while (left <= right)
        {
            /*skip non-alphanumeric charcters. */
            while (left <= right)
            {
                if (isalnum(s[left]))
                {
                    break;
                }
                else
                {
                    ++left;
                }
            }

            while (left <= right)
            {
                if (isalnum(s[right]))
                {
                    break;
                }
                else
                {
                    --right;
                }
            }

            if (left > right)
            {
                break;
            }

            if (tolower(s[left]) != tolower(s[right]))
            {
                return false;
            }

            ++left;
            --right;
        }

        return true;
    }
};

class SolutionTwo {
public:
    bool isPalindrome(string s)
    {
        if (s.empty())
        {
            return false;
        }

        int l = 0;
        int r = s.size();

        while (l <= r)
        {
            /* Using if-else ensures l and r are updated only once! */
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
                return false;
            }
            else
            {
                ++l;
                --r;
            }
        }

        return true;
    }

    bool isPalindrome_(string s) {
        if (s.empty())
        {
            return false;
        }

        int l = 0;
        int r = s.size() - 1;

        while (l <= r)
        {

            /* Skip chars which are not alphanumeric (decimal digit, letters)*/
            /* Since we need to increment, we use l < r instead of l <= r */
            while (l < r && !isalnum(s[l]))
            {
                ++l;
            }

            while (l < r && !isalnum(s[r]))
            {
                --r;
            }

            if (tolower(s[l]) != tolower(s[r]))
            {
                return false;
            }


            /* update l and r! */
            ++l;
            --r;
        }

        return true;
    }
};
int main()
{
    SolutionTwo sol;
    string s = "A man, a plan, a canal: Panama";
    string s_one = "race a car";
    string s_two = " ";

    cout << sol.isPalindrome(s) << endl;
    cout << sol.isPalindrome(s_one) << endl;
    cout << sol.isPalindrome(s_two) << endl;

    return 0;
}
