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
            lowercase_cnt[s[left_prev] - 'a'] += 1; // cancel the effect of the deleted char
            lowercase_cnt[s[right] - 'a'] -= 1; // change state.

            if (is_all_zero(lowercase_cnt))
            {
                start_idxs.push_back(left_prev + 1);
            }

            /* When the window slide the preivous anogram entirely, the orignal state is recovered!  */
        }

        return start_idxs;
    }
};


class SolutionTwo {
public:
    bool is_all_zero(const std::vector<int>& letter2cnt)
    {
        for (const auto& cnt : letter2cnt)
        {
            if (0 != cnt)
            {
                return false;
            }
        }

        return true;
    }

    vector<int> findAnagrams(string s, string p)
    {
        std::vector<int> result;
        if (p.size() > s.size())
        {
            return result;
        }

        /* both s and p consist of lowercase English letters. */
        std::vector<int> letter2cnt(26, 0);  // store the state of the window of size |p|

        for (size_t i = 0; i < p.size(); ++i)
        {
        /* The effect of the p on the state of window. positve effect */
            ++letter2cnt[p[i] - 'a'];

        /* Integrate effect of first window on the state . negative effect */
            --letter2cnt[s[i] - 'a'];
        }

        /* Check the new state! */
        if (is_all_zero(letter2cnt)) result.push_back(0);

        for (size_t i = 1; i <= s.size() - p.size(); ++i)
        {
            /* cancel the effect of the previous leftmost char */
            ++letter2cnt[s[i - 1] - 'a'];

            /* Add the effect of the new rightmost char */
            --letter2cnt[s[i + p.size() - 1] - 'a'];

            /* Check the new state. */
            if (is_all_zero(letter2cnt)) result.push_back(i);

            /* Note that the letter2cnt's initial state is recovered when the window slides over
             * the whole current windowing substring.
             */
        }

        return result;
    }
};

int main()
{
    SolutionTwo sol;
    string s = "abab", p = "ab";
    vector<int> result = sol.findAnagrams(s, p);

    for (const auto &idx: result)
    {
        cout << idx << " ";
    }
    cout << endl;

    return 0;
}
