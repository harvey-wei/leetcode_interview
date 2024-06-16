#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility> // std::pair, std::make_pair


using namespace std;

class Solution_ {
public:
    string minWindow(string s, string t)
    {
        if (s.size() < t.size()) return "";

        std::unordered_map<char, int> t_char2cnt;
        for (const auto& ch : t)
        {
            if (t_char2cnt.end() == t_char2cnt.find(ch))
            {
                /* ch is not present in t_char2cnt. */
                t_char2cnt[ch] = 1;
            }
            else
            {
                ++t_char2cnt[ch];
            }
        }

        /* Our objective is to find a minWindow of s which have the same # of chs in t_char2cnt. */
        /* In other words, we need zero all cnt in t_char2cnt.*/
        /* [left, right]*/

        int left = 0;
        int right = 0;
        int zero_cnt = 0;  // target_zero_cnt = t_char2cnt.size();
        int min_len = s.size() + 1;
        int l = -1, r = -1;

        // We should ignore
        while (right < s.size())
        {
            // s[right] is inserted into window
            if (t_char2cnt.end() != t_char2cnt.find(s[right]))
            {
                /* Decrement cnt of s[right]*/
                if (1 == t_char2cnt[s[right]])
                {
                    ++zero_cnt;
                }

                --t_char2cnt[s[right]];
            }


            // Since we use [left, right], left <= right.
            while (zero_cnt == t_char2cnt.size() && left <= right)
            {
                /* Find a match. */
                if (right - left + 1 < min_len)
                {
                    l = left;
                    r = right;
                    min_len = right - left + 1;
                }

                // effect of ++left
                if (t_char2cnt.end() != t_char2cnt.find(s[left]))
                {
                    /* Increment cnt of s[left] */
                    if (0 == t_char2cnt[s[left]])
                    {
                        --zero_cnt;
                    }

                    ++t_char2cnt[s[left]];
                }

                // increment left
                ++left;
            }

            // udpate right
            ++right;
        }

        return min_len == s.size() + 1 ? "" :s.substr(l, r - l + 1);
    }
};

// Late Optimization!

class Solution {
public:
    string minWindow(string s, string t)
    {
        if (s.size() < t.size() || 0 == s.size() || 0 == t.size())
        {
            return "";
        }

        unordered_map<int, int> t_char2cnt;
        for (const auto& ch : t)
        {
            if (t_char2cnt.end() == t_char2cnt.find(ch))
            {
                t_char2cnt[ch] = 1;
            }
            else
            {
                ++t_char2cnt[ch];
            }
        }

        // Map index of char present in t to char in s.
        // We need the matatin the order and access in O(1)
        // Hence, treeMap is ruled out since O(lgn)
        // We can adopt the array of pair of (index, char)
        std::vector<std::pair<int, char>> s_filterd;
        for (int i = 0; i < s.size(); ++i)
        {
            if (t_char2cnt.end() != t_char2cnt.find(s[i]))
            {
                s_filterd.push_back(std::make_pair(i, s[i]));
            }
        }

        int r = 0;
        int l = 0;
        int zero_cnt = 0;
        int min_len = s.size() + 1;
        int min_l = -1;
        int min_r = -1;
        while (r < s_filterd.size())
        {
            const auto& r_idx = s_filterd[r].first;
            const auto& r_char = s_filterd[r].second;
            // s_filterd[r].second is inserted to the window
            // --t_char2cnt[s_filterd[second]]
            if (1 == t_char2cnt[r_char])
            {
                ++zero_cnt;
            }
            --t_char2cnt[r_char];

            while (l <= r && (t_char2cnt.size() == zero_cnt))
            {
                const auto& l_idx = s_filterd[l].first;
                const auto& l_char = s_filterd[l].second;
                if (r_idx - l_idx + 1 < min_len)
                {
                    min_l = l_idx;
                    min_r = r_idx;
                    min_len = r_idx - l_idx + 1;
                }

                // update t_char2cnt;
                if (0 == t_char2cnt[l_char])
                {
                    --zero_cnt;
                }
                ++t_char2cnt[l_char];

                // update l
                ++l;
            }


            // Increment r
            ++r;
        }

        return min_len == s.size() + 1 ? "" : s.substr(min_l, min_len);
    }
};

