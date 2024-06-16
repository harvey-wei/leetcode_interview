#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Solution_
{
public:
    int lengthOfLongestSubstring(string s)
    {
        /* ASCII code 256 chars*/
        /* Hence, char value acts as index. */
        std::vector<int> char2cnt(256, 0);
        int max_len = 0;

        /* Each character will be visisted at most once. */
        /* Hence Time Complexity: O(N)*/
        int left = 0;
        int right = 0;

        // [l, r]
        while (right < s.size())
        {
            ++char2cnt[s[right]];

            /* If s[right] has duplicates. ++left until remove the duplicate */
            while (char2cnt[s[right]] > 1)
            {
                /* Duplicate of s[right] must occur to the left of s[right]. */
                --char2cnt[s[left]];
                ++left;
            }

            /* char2cnt[s[right]] == 1*/

            max_len = std::max<int>(max_len, right - left + 1);

            /* Increment right. */
            ++right;
        }

        return max_len;
    }
};


class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        /**
         * ASCII code has 256 characters.
         * A 256-element array serve as a hashmap
         */
        // char's literal value acts as key.
        std::vector<int> char2idx(256, -1);

        int left = 0;
        int right = 0;
        int max_len = 0;

        while (right < s.size())
        {
            /* Check to see if s[right] is the [left, right) */
            int index = char2idx[s[right]];
            if (-1 != index && left <= index)
            {
                /* left is < right */
                left = index + 1;
            }

            max_len = std::max<int>(max_len, right - left + 1);

            /* Only right update the hashmap char2idx. */
            char2idx[s[right]] = right;
            ++right;
        }

        return max_len;
    }
};


int
main()
{
    return 0;
}
