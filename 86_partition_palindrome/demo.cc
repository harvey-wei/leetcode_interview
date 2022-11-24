#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool is_palindrome(const string& str, int start, int end)
    {
        while (start < end)
        {
            if (str[start] != str[end])
            {
                return false;
            }
            else
            {
                ++start;
                --end;
            }
        }

        /* Single-char string is also a palindrome. */
        return true;
    }

    void helper(const string& s, int start, vector<string>& strs, vector<vector<string>>& result)
    {
        if (start == s.size())
        {
            result.push_back(strs);
        }
        else
        {
            for (int i = start; i < s.size(); ++i)
            {
                if (is_palindrome(s, start, i))
                {
                    strs.push_back(s.substr(start, i - start + 1));
                    helper(s, i + 1, strs, result);
                    strs.pop_back();
                }
            }

        }

        return;
    }

    vector<vector<string>> partition(string s) {
        vector<string> strs;
        vector<vector<string>> results;
        helper(s, 0, strs, results);

        return results;
    }
};

int main()
{
    return 0;
}
