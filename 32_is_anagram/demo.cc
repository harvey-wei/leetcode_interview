#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t)
    {
        if ((s == t) || (s.size() != t.size())) return false;

        /* s and t consist of lowercase English letters. */
        int lc_num = 26;
        vector<int>  lc2cnt(lc_num, 0);

        for (int i = 0; i < s.size(); ++i)
        {
            lc2cnt[s[i] - 'a'] += 1;
        }

        for (int i = 0; i < t.size(); ++i)
        {
            /* New char in t or more of the chars from s exists in t.
               You have to make sure that s and t are of the same length.
            */
            if (0 == lc2cnt[t[i] - 'a']) return false;

            lc2cnt[t[i] - 'a'] -= 1;
        }

        return true;
    }
};

int main()
{
    return 0;
}
