#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

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
            else
            {
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

int main()
{
    Solution sol;
    string s_one = "ADOBECODEBANC", t_one = "ABC";
    string s_two = "a", t_two = "a";
    string s_three = "a", t_three = "aa";
    string s = "cabwefgewcwaefgcf", t = "cae";
    cout << sol.minWindow(s_one, t_one) << endl;
    cout << sol.minWindow(s_two, t_two) << endl;
    cout << sol.minWindow(s, t) << endl;
    return 0;
}
