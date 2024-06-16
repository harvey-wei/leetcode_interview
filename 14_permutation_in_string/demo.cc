#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool is_all_zero(const std::vector<int>& nums)
    {
        for (const auto& num : nums)
        {
            if (0 != num)
            {
                return false;
            }
        }

        return true;

    }

    bool checkInclusion_(string s1, string s2)
    {
        if (s1.size() > s2.size()) return false;

        /* All letters are lowcase. 26 letters */
        std::vector<int> letter2cnt(26, 0);

        /* State of s1. */
        for (int i = 0; i < s1.size(); ++i)
        {
            letter2cnt[s1[i] - 'a'] += 1;

            /* The first window */
            letter2cnt[s2[i] - 'a'] -= 1;
        }

        if (is_all_zero(letter2cnt)) return true;

        /* Check subsring [l, l + s1.size()) */
        /* l_min = 0, l_max = s2.size - s1.size()*/
        /* l == 0 is already checked. */
        for (int l = 1; l <= s2.size() - s1.size(); ++l)
        {
            /* update window state. l - 1 is removed, l + s1.size() - 1 is inserted. */
            letter2cnt[s2[l - 1] - 'a'] += 1;
            letter2cnt[s2[l + s1.size() - 1] - 'a'] -= 1;

            /* Check if letter2cnt is all zero */
            if (is_all_zero(letter2cnt))
            {
                return true;
            }
        }

        return false;
    }

    bool checkInclusion(string s1, string s2)
    {
        if (s1.size() > s2.size()) return false;

        std::vector<int> s1_ch2cnt(26, 0);
        std::vector<int> s2_ch2cnt(26, 0);

        for (size_t i = 0; i < s1.size(); ++i)
        {
            ++s1_ch2cnt[s1[i] - 'a'];
            ++s2_ch2cnt[s2[i] - 'a'];
        }

        /* For 26 letters, count tracks the number of *frequence matches*. */
        /* Initial Count of Matches. */
        int count = 0;
        for (int i = 0; i < 26; ++i)
        {
            if (s1_ch2cnt[i] == s2_ch2cnt[i])
            {
                ++count;
            }
        }

        if (26 == count) return true;

        /**
         * Slide a window over s2.
         * [i, i + s1.size())
         */
        for (size_t i = 1; i <= s2.size() - s1.size(); ++i)
        {
            int l = i - 1; // left_removed
            int r = i + s1.size() - 1; // right_inserted


            /* Decrement the frequence of s2[l]. */
            --s2_ch2cnt[s2[l] - 'a'];
            if (s1_ch2cnt[s2[l] - 'a'] == s2_ch2cnt[s2[l] - 'a'])
            {
                /* Produce a new match. */
                ++count;
            }
            else if (s1_ch2cnt[s2[l] - 'a'] == s2_ch2cnt[s2[l] - 'a'] + 1)
            {
                /* Remove a old match by removeing one letter occurence */
                /* Which means s2_ch2cnt[s2[l] - 'a'] gets one less than target. */
                --count;
            }
            else
            {
                /* Do nothing. */
            }

            /* Increment the frequence of s2[r]. */
            ++s2_ch2cnt[s2[r] - 'a'];
            if (s1_ch2cnt[s2[r] - 'a'] == s2_ch2cnt[s2[r] - 'a'])
            {
                /* Produce a new match. */
                ++count;
            }
            else if(s1_ch2cnt[s2[r] - 'a'] == s2_ch2cnt[s2[r] - 'a'] - 1)
            {
                /* Delete a old match by adding one more letter occurence. */
                /* It means s2_ch2cnt[s2[r] - 'a'] is one more than target. */
                --count;
            }
            else
            {
                /* Do nothing. */

            }

            if (26 == count)
            {
                return true;
            }
        }

        return false;
    }
};
