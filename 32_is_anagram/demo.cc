#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        if (s.size() != t.size()) return false;

        /* Both s and t are comprised of lowercase. */
        /* Permutation is denoted as a map fromn letter2cnt. */
        std::vector<int> letter2cnt(26, 0);

        for (int i = 0; i < s.size(); ++i)
        {
            letter2cnt[s[i] - 'a'] += 1;
            letter2cnt[t[i] - 'a'] -= 1;
        }

        for (const auto& cnt : letter2cnt)
        {
            if (0 != cnt) return false;
        }

        return true;
    }
};
