#include <iostream>
#include <string>
#include <cctype>
using namespace std;
/*
   https://www.programiz.com/c-programming/library-function/ctype.h
*/

class Solution {
public:
    bool isPalindrome(string s) {
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

int main()
{
    Solution sol;
    string s = "A man, a plan, a canal: Panama";
    string s_one = "race a car";
    string s_two = " ";

    cout << sol.isPalindrome(s) << endl;
    cout << sol.isPalindrome(s_one) << endl;
    cout << sol.isPalindrome(s_two) << endl;

    return 0;
}
