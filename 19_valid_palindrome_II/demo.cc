#include <iostream>
#include <string>


using namespace std;

class Solution
{
public:
    bool is_palindrome(const string& s, const int& l, const int& r)
    {
        /* Emtpy */
        if (l > r) return true;

        int left = l;
        int right = r;
        while (left <= right)
        {
            if (s[left] == s[right])
            {
                ++left;
                --right;
            }
            else
            {
                return false;
            }
        }

        return true;
    }

    bool validPalindrome(string s)
    {
        /* s is comprised of lowercase English letters. */
        /* s is not empty*/
        int l = 0;
        int r = s.size() - 1;

        while (l <= r)
        {
            if (s[l] == s[r])
            {
                ++l;
                --r;
            }
            else
            {
                /* Delete s[l] and check s[l+1, r]*/
                /* If delete s[l] is not OK, check [l, r- 1]*/
                if (is_palindrome(s, l + 1, r))
                {

                    return true;
                }
                else if (is_palindrome(s, l, r - 1))
                {
                    return true;
                }
                else
                {
                    return false;
                }

            }
        }

        return true;
    }
};
