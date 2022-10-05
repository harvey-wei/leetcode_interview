#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool is_all_zero(const vector<int> &nums)
    {
        for (const auto & num: nums)
        {
            if (0 != num) return false;
        }

        return true;
    }

    vector<int> findAnagrams(string s, string p) {
        vector<int> start_idxs;
        if (p.length() > s.length())
        {
            return start_idxs;
        }

        /* Emulate the hash table to record the frequency of the lowercase letters.*/
        vector<int> lowercase_cnt(26, 0);

        /* The first window of length equal to string p */
        for (int i = 0; i < p.length(); ++i)
        {
            lowercase_cnt[p[i] - 'a'] += 1;
            lowercase_cnt[s[i] - 'a'] -= 1;
        }

        if (is_all_zero(lowercase_cnt))
        {
            start_idxs.push_back(0);
        }

        /* right is the next right index */
        for (int right = p.length(); right < s.length(); ++right)
        {
            int left_prev = right - p.length();
            lowercase_cnt[s[left_prev] - 'a'] += 1;
            lowercase_cnt[s[right] - 'a'] -= 1;

            if (is_all_zero(lowercase_cnt))
            {
                start_idxs.push_back(left_prev + 1);
            }
        }

        return start_idxs;
    }
};

int main()
{
    Solution sol;
    string s = "abab", p = "ab";
    vector<int> result = sol.findAnagrams(s, p);

    for (const auto &idx: result)
    {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}
