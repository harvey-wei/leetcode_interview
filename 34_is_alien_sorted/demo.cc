#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool is_sorted(const string& lhs, const string& rhs, const vector<int>& letter2order)
    {
        /* aa, aab is ok*/
        int i = 0;
        for (; i < lhs.size() && i < rhs.size(); ++i)
        {
            char l = lhs[i];
            char r = rhs[i];

            if (letter2order[l - 'a'] < letter2order[r - 'a']) return true;

            if (letter2order[l - 'a'] > letter2order[r - 'a']) return false;
        }

        /* lhs == rhs[0:lhs.size()) means being sorted! */
        return i == lhs.size();
    }

    bool isAlienSorted(vector<string>& words, string order)
    {
        vector<int> letter2order(26, 0); // Small means front.

        for (int i = 0; i < order.size(); ++i)
        {
            letter2order[order[i] - 'a'] = i;
        }

        for (int i = 0; i < words.size() - 1; ++i)
        {
            if (!is_sorted(words[i], words[i + 1], letter2order))
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    return 0;
}
