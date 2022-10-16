#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {
        /* Time: O(N)
           Space: O(1)  256 ASCII characters!
        */
        /* ASCII value acts as the index!
           Key idea: ASCII char is of length 8 bits!
           https://www.rapidtables.com/code/text/ascii-table.html
        */
        if (0 == s.length())
        {
            return 0;
        }

        vector<int> char2cnt(256, 0);
        int left = 0;
        bool is_no_repeat = true;
        int max_len = 1;

        for (int right = 0; right < s.length(); ++right)
        {
            /* ++right to try longer sub-string!*/
            if (char2cnt[s[right]] > 0)
            {
                is_no_repeat = false;
            }

            char2cnt[s[right]] += 1;

            if (is_no_repeat)
            {
                max_len = max<int>(right - left + 1, max_len);
            }

            /* If the current sub-string is not OK, ++left until OK.
               In the worst case, good sub-string is s[right] itself!
               Some key observations:
               1. No need to consider the characters to the left of left pointer.
               2. s[right] is the character leading to bad sub-string.
               3. Only if the s[left] == s[right], the sub-string can become good again.
               4. char2cnt's count is <= 2! Prove by contradiction. And at most one is = 2.
               A char variable has its own ASCII value. So the characters are compared according
               to the ASCII values.
            */
            while ((left <= right) && (!is_no_repeat))
            {
                if (s[left] == s[right])
                {
                    is_no_repeat = true;
                    max_len = max<int>(right - left, max_len);
                }
                char2cnt[s[left]] -= 1;
                ++left;
            }
        }

        return max_len;
    }

    int lengthOfLongestSubstring_hashmap(string s)
    {
        /* Empty string returns 0!*/
        if (0 == s.length()) return 0;

        unordered_map<char, int> char2cnt;

        int left = 0;
        int max_len = 1;
        bool is_substr_good = true;

        for (int right = 0; right < s.length(); ++right)
        {
            if ((char2cnt.end() != char2cnt.find(s[right])) && (char2cnt[s[right]] > 0))
            {
                is_substr_good = false;
                char2cnt[s[right]] += 1;
            }
            else
            {
                /* No exist or count == 0*/
                char2cnt[s[right]] = 1;
            }

            if (true == is_substr_good)
            {
                max_len = max<int>(right - left + 1, max_len);
            }

            while ((left <= right) && (!is_substr_good))
            {
                if (s[left] == s[right])
                {
                    is_substr_good = true;
                    max_len = max<int>(right -left, max_len);
                }
                char2cnt[s[left]] -= 1;
                ++left;
            }
        }

        return max_len;

    }
};


int main()
{
    Solution sol;
    string s_one = "abcabcbb";
    string s_two = "bbbbb";
    string s_three = "pwwkew";

    /* Pre-defined array is much faster than dynamically allocated hash table! */
    /* cout << sol.lengthOfLongestSubstring(s_one) << endl; */
    /* cout << sol.lengthOfLongestSubstring(s_two) << endl; */
    /* cout << sol.lengthOfLongestSubstring(s_three) << endl; */

    cout << sol.lengthOfLongestSubstring_hashmap(s_one) << endl;
    cout << sol.lengthOfLongestSubstring_hashmap(s_two) << endl;
    cout << sol.lengthOfLongestSubstring_hashmap(s_three) << endl;
    return 0;
}
