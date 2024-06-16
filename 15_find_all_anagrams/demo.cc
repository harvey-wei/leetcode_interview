#include <vector>
#include <string>
#include <unordered_map>
using namespace std;


class Solution {
public:
    vector<int> findAnagrams(string s, string p)
    {
        vector<int> start_idx;
        if (p.size() > s.size()) return start_idx;

        /* Note that all strings consist of lowercase letters. */
        /* s_map[ch - 'a'] is the count of ch in s*/
        std::vector<int> s_map(26, 0);
        std::vector<int> p_map(26, 0);

        /* Init the window state. */
        for (size_t i = 0; i < p.size(); ++i )
        {
            ++s_map[s[i] - 'a'];
            ++p_map[p[i] - 'a'];
        }

        int match_cnt = 0;
        for (size_t i = 0; i < 26; ++i)
        {
            if (s_map[i] == p_map[i])
            {
                ++match_cnt;
            }
        }

        if (26 == match_cnt)
        {
            start_idx.push_back(0);
        }

        /**
         * [l, l + p.size())
         * l = 1, 2,..., s.size() - p.size()
         */
        for (size_t i = 1; i <= s.size() - p.size(); ++i)
        {
            int l = i - 1;
            int r = i + p.size() - 1;

            /* We only care for the transition point. */
            --s_map[s[l] - 'a'];
            if (p_map[s[l] - 'a'] == s_map[s[l] - 'a'])
            {
                /* Produce a new match. */
                ++match_cnt;

            }
            else if (p_map[s[l] - 'a'] == s_map[s[l] - 'a'] + 1)
            {
                /* Decrement remove an old match. */
                --match_cnt;
            }
            else
            {
                /*Do nothing! */
            }

            ++s_map[s[r] - 'a'];
            if (p_map[s[r] - 'a'] == s_map[s[r] - 'a'])
            {
                /* Produce a new match! */
                ++match_cnt;
            }
            else if (p_map[s[r] - 'a'] == s_map[s[r] - 'a'] - 1)
            {
                /* Increment deletes an old match. */
                --match_cnt;

            }
            else
            {
                /* Do nothing. */
            }

            /* Check if match_cnt == 26. */
            if (26 == match_cnt)
            {
                start_idx.push_back(i);
            }
        }

        return start_idx;
    }
};



int
main(int argc, char** argv)
{
	/* int a = 10; */

    return 0;
}
