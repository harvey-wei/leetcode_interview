#include <iostream>
#include <string>
#include <cctype>
using namespace std;
/*
    https://www.programiz.com/c-programming/library-function/ctype.h
    ref: https://leetcode.com/problems/valid-palindrome-ii/
*/

class Solution {
public:
    bool isPalindrome(const string &s, const int &start, const int &end)
    {
        /* [start, end] */
        int i = start;
        int j = end;

        while (i <= j)
        {
            if (s[i] != s[j]) return false;

            ++i;
            --j;
        }

        return true;
    }

    bool validPalindrome(string s) {
        int left = 0;
        int right = s.length() - 1;
        int max_del_cnt = 1;
        int curr_del_cnt = 0;

        while (left <= right)
        {
            if (tolower(s[left]) != tolower(s[right]))
            {
                bool is_del_left_ok = (left + 1 <= right) && (isPalindrome(s, left + 1, right));
                if (is_del_left_ok)
                {
                    return true;
                }
                else
                {
                    bool is_del_right_ok = (left <= right -1) && (isPalindrome(s, left, right - 1));
                    return is_del_right_ok;
                }
            }

            ++left;
            --right;
        }

        return true;
    }
};

class SolutionTwo
{
public:
    bool is_valid_palindrome(const string& s, int l, int r)
    {
        if (l > r) return true;


        while (l <= r)
        {
            if (s[l] != s[r])
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
    };

    bool validPalindrome(string s)
    {
        /* s is non-empty and consists of lowercase English letters. */
        int l = 0;
        int r = s.size() - 1;

        while (l <= r)
        {
            if (s[l] != s[r])
            {
                int start = l + 1;
                int end = r - 1;

                /* delete left or right */
                return is_valid_palindrome(s, start, r) || is_valid_palindrome(s, l, end);
            }
            else
            {
                ++l;
                --r;
            }
        }

        return true;
    }
};

int main()
{
    SolutionTwo sol;
    /* string s_three = "A man, a plan, a canal: Panama"; */
    /* string s_one = "race a car"; */
    /* string s_two = " "; */

    /* cout << sol.validPalindrome(s_three) << endl; */
    /* cout << sol.validPalindrome(s_one) << endl; */
    /* cout << sol.validPalindrome(s_two) << endl; */

    /* string ss_one = "aba"; */
    /* string ss_two = "abca"; */
    /* string ss_three = "abc"; */

    /* cout << sol.validPalindrome(ss_one) << endl; */
    /* cout << sol.validPalindrome(ss_two) << endl; */
    /* cout << sol.validPalindrome(ss_three) << endl; */


    /* 19 vs 81 c vs u */
    string ss_long =
        "aguokepatgbnvfqmgmlcupuufxoohdfpgjdmysgvhmvffcnqxjjxqncffvmhvgsymdjgpfdhooxfuupuculmgmqfvnbgtapekouga";
    cout << sol.validPalindrome(ss_long) << endl;

    return 0;
}
