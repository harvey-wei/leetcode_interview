#include <string>


using namespace std;

class Solution {
public:
    int palindrome_grow(const string& s, int start, int end)
    {
        int count = 0;
        while (start >= 0 && end < s.size())
        {
            /* When while-condition is true, */
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
        int count = 0;
        for (int i = 0; i < s.size(); ++i)
        {
            /* odd-length: s[i] is center */
            count += palindrome_grow(s, i, i);

            /* even-length: s[i] and s[i+1] are center i  < s.size(0 -1*/
            /* Or leave the boundary check to palindrome_grow() */
            count += palindrome_grow(s, i, i + 1);
        }

        return count;
    }
};
