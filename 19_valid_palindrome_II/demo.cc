#include <iostream>
#include <string>
#include <cctype>
using namespace std;
/*
   https://www.programiz.com/c-programming/library-function/ctype.h
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

int main()
{
    Solution sol;
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
