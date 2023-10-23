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
                if (s[left] == s[right]) {
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


class SolutionTwo {
public:
    int lengthOfLongestSubstring(string s) {
        /* if (s.empty()) */
        /* { */
            /* Thinking in the edge and corner case! */
        /*     return 0; */
        /* } */

        int max_len = 0;

        /**
         * State of the Window : hashmap from ASCII char to # occurrence.
         *
         * How to update window state: [l, r], ++r include char while ++l to exclude char
         *
         * The one key question is can we ignore visited l after increment r?
         * The another is to when to move and stop moving left pointer?

         * When to increment l and r?
         * For each substring endt at r, we check [l, r] and increment l until window has no
         * duplicates.
         * If one corrent l is found, no need to ++l furhter since we find longest one! And we don't
         * need consider smaller l again for end index > r as duplicates in shorter makes duplicates
         * in super-string.
         *
         */
        std::vector<int> char2cnt(256, 0);
        int dup_cnt = 0;

        int l = 0;
        for (int r = 0; r < s.size(); ++r)
        {
            /* Append s[r] to the window and update char2cnt. */
            ++char2cnt[s[r]];

            /*Check whether s[r] makes a duplicate! */
            if (2 == char2cnt[s[r]])
            {
                ++dup_cnt;
            }

            /* Increment l to remove the duplicates. */
            /* l is ensured <= r implicitly! */
            while (dup_cnt > 0)
            {
                --char2cnt[s[l]];
                if (1 == char2cnt[s[r]])
                {
                    --dup_cnt;
                }
                ++l;
            }

            max_len = std::max<int>(max_len, r - l + 1);
        }


        /* max_len at least one s is not empty! */
        return max_len;
    }

    int lengthOfLongestSubstring_(string s) {
        if (0u == s.size())
        {
            return 0;
        }

        /**
         * State of the window: hashset of chars.
         * Key observations:
         * 1. If s[l, r] is a substring w/o repeating chars, no need to increment l since we find
         * longest one. Instead, we increment r.
         * 2. if l is a start index for a longest target ending at r, (0, 1,..., l-1) could not be
         * optimal start index for end index > r. prove by contradiction! -> Once we find a answer,
         * increment right index.
         *
         * How to verify the property of no-repeating characters in constant time?
         * In light of the total of 256 ASCII chars, we could use a int array of 256 elements to
         * count the number of chars in the window
         */

        /* Value of char is ASCII code value which can act as index! */
        std::vector<int> charset(256, 0);
        bool count_dup = 0;
        int max_len = -1;

        /* Increment r to include new char while increment l to exclude oldest char. */
        int l = 0;
        for (int r = 0; r < s.size(); ++r)
        {
            /* update charset and check whether s[r] is repeated! */
            ++charset[s[r]];

            if (2 == charset[s[r]])
            {
                count_dup += 1;
            }

            /* Increment l until count_dup = 0 */
            /* if l == r, no duplicate*/
            while (count_dup > 0)
            {
                --charset[s[l]];

                if (charset[s[r]] == 1)
                {
                    count_dup -= 1;
                }

                ++l;
            }

            /* count_dup == 0 */
            max_len = std::max<int>(max_len, r - l + 1);
        }

        return max_len;

    }
};

int main()
{
    SolutionTwo sol;
    string s_one = "abcabcbb";
    string s_two = "bbbbb";
    string s_three = "pwwkew";

    /* Pre-defined array is much faster than dynamically allocated hash table! */
    cout << sol.lengthOfLongestSubstring(s_one) << endl;
    cout << sol.lengthOfLongestSubstring(s_two) << endl;
    cout << sol.lengthOfLongestSubstring(s_three) << endl;

    /* cout << sol.lengthOfLongestSubstring_hashmap(s_one) << endl; */
    /* cout << sol.lengthOfLongestSubstring_hashmap(s_two) << endl; */
    /* cout << sol.lengthOfLongestSubstring_hashmap(s_three) << endl; */
    return 0;
}
