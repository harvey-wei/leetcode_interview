#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t)
    {
        if (s == t) return false;
        /* s and t consist of lowercase English letters. */
        int lc_num = 26;
        vector<int>  lc2cnt(lc_num, 0);

        for (int i = 0; i < s.size(); ++i)
        {
            lc2cnt[s[i] - 'a'] += 1;
        }

        for (int i = 0; i < t.size(); ++i)
        {
            if (0 == lc2cnt[t[i] - 'a']) return false;

            lc2cnt[t[i] - 'a'] -= 1;
        }

        for (int i = 0; i < lc2cnt.size(); ++i)
        {
            if (lc2cnt[i] != 0) return false;
        }

        return true;
    }
};

int main()
{
    return 0;
}
