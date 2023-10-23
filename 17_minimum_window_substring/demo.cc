#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

#define INT_MAX (std::numeric_limits<int>::max())

/* ref: https://leetcode.com/problems/minimum-window-substring/ */
class Solution {
public:
    string minWindow(string s, string t)
    {
        unordered_map<char, int> t_char2cnt;
        int bool_sum = 0;

        if (s.length() < t.length())
        {
            return "";
        }

        for (const auto &ch: t)
        {
            if (t_char2cnt.end() == t_char2cnt.find(ch))
            {
                t_char2cnt[ch] = 1;
            }
            else {
                t_char2cnt[ch] += 1;
            }
        }

        int left = 0;
        int min_len = INT_MAX;
        int min_win_start_idx = -1;

        for (int right = 0; right < s.length(); ++right)
        {
            if (t_char2cnt.end() != t_char2cnt.find(s[right]))
            {
                /* s[right] is the character in t */
                if (1 == t_char2cnt[s[right]])
                {
                    /* 1->0 */
                    bool_sum += 1;
                }

                t_char2cnt[s[right]] -= 1;
            }

            if (t_char2cnt.size() == bool_sum)
            {
                /* good sub-string */
                if (right - left + 1 < min_len)
                {
                    min_len = right - left + 1;
                    min_win_start_idx = left;
                }
            }

            /* Shorten the good sub-string by ++left. */
            while ((left <= right) && (t_char2cnt.size() == bool_sum))
            {
                if (t_char2cnt.end() != t_char2cnt.find(s[left]))
                {
                    if (0 == t_char2cnt[s[left]])
                    {
                        /* 0 -> 1 */
                        --bool_sum;
                    }
                    t_char2cnt[s[left]] += 1;
                }

                if (t_char2cnt.size() == bool_sum)
                {
                    /* Still a good sub-string */
                    if (right - left < min_len)
                    {
                        min_len = right - left;
                        min_win_start_idx = left + 1;
                    }
                }

                ++left;
            }
        }

        return INT_MAX == min_len ? "" : s.substr(min_win_start_idx, min_len);
    }
};


class SolutionTwo {
public:
    string minWindow(string s, string t)
    {
        if (s.size() < t.size()) return "";

        /*
         * For the sequence of subarrays ending at r, we should increment l until window is not
         wanted or l > r;
         */

        /* state of the window */
        std::unordered_map<int, int> char2cnt; // ASCII code value to number of occurences.
        for (size_t i = 0; i < t.size(); ++i)
        {
            if (char2cnt.end() == char2cnt.find(t[i]))
            {
                char2cnt[t[i]] = 1;
            }
            else
            {
                ++char2cnt[t[i]];
            }
        }

        int min_len = s.size() + 1;
        int min_l = -1;
        int min_r = -1;

        int l = 0;
        int count = char2cnt.size(); // The # of kinds of chars remaining to be filled!
        for (int r = 0; r < s.size(); ++r)
        {
            /* Insert s[r] to the window and update state */
            if (char2cnt.end() != char2cnt.find(s[r]))
            {
                --char2cnt[s[r]];

                /* 1-> 0 */
                if (0 == char2cnt[s[r]]) --count;
            }

            /* Increment l until a answer is found or l > r */
            while (l <= r && 0 == count)
            {
                if ((r - l + 1) < min_len)
                {
                    min_len = r - l + 1;
                    min_l = l;
                    min_r = r;
                }

                if (char2cnt.end() != char2cnt.find(s[l]))
                {
                    ++char2cnt[s[l]];

                    /* 0 -> 1 */
                    if (1 == char2cnt[s[l]]) ++count;

                }

                ++l;
            }
        }

        return min_l == -1 ? "" : s.substr(min_l, min_len);
    }

    /**
     *  Input: s = "a", t = "aa"
     *  Output: ""
     *  Explanation: Both 'a's from t must be included in the window.
     *  Since the largest window of s only has one 'a', return empty string.
     *
     */

    /* state: hashmap from char in t to cnt of occurence!
     * window : [l, r] ending at r
     * Increment r to add char to window, update hashmap
     * Increment l to exclude leftmost char until window is not desired!
     *
     */
    string minWindow_(string s, string t)
    {
        if (s.size() < t.size()) return "";

        int l = 0;
        int r = 0;

        std::unordered_map<char, int> char2cnt;
        for (size_t i = 0; i < t.size(); ++i)
        {
            if (char2cnt.end() == char2cnt.find(t[i]))
            {
                char2cnt[t[i]] = 1;
            }
            else
            {
                ++char2cnt[t[i]];
            }
        }

        /* Each time the value of one key in char2cnt goes from 1 to 0, --count!*/
        /* If gets from 0 to 1, ++count. */
        /* If count == 0, all chars in t are included in window from s. */
        int count = char2cnt.size();
        int min_len = s.size() + 1;
        int min_l = -1;
        int min_r = -1;

        for (; r < s.size(); ++r)
        {
            /* Include s[r] and update char2cnt */
            if (char2cnt.end() != char2cnt.find(s[r]))
            {
                --char2cnt[s[r]];

                if (0 == char2cnt[s[r]])
                {
                    --count;
                }
            }

            /* Increment l until count is not zero. */
            while (l <= r && 0 == count)
            {
                if ((r - l + 1) < min_len)
                {
                    min_len = r - l  + 1;
                    min_l = l;
                    min_r = r;
                }

                if (char2cnt.end() != char2cnt.find(s[l]))
                {
                    ++char2cnt[s[l]];

                    /* 0 to 1*/
                    if (1 == char2cnt[s[l]])
                    {
                        ++count;
                    }
                }

                ++l;
            }
        }

        return min_l == -1 ? "" : s.substr(min_l, min_r  - min_l + 1);
    }
};
int main()
{
    SolutionTwo sol;
    string s_one = "ADOBECODEBANC", t_one = "ABC";
    string s_two = "a", t_two = "a";
    string s_three = "a", t_three = "aa";
    string s = "cabwefgewcwaefgcf", t = "cae";
    cout << sol.minWindow(s_one, t_one) << endl;
    cout << sol.minWindow(s_two, t_two) << endl;
    cout << sol.minWindow(s, t) << endl;
    return 0;
}
