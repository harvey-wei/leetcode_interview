#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        /*
           Common property for a group a anagrams: they have the same number of the same characters
           HashMap or Array needs to compare character by character.
           32-bit int or string can be tested for equality in constant time.
           but 32-bit only applies to existence.
           string can be used to count the number of occurrences.
        */
        vector<vector<string>> ans;
        unordered_map<string, int> groups;

        for (const auto & str: strs)
        {
            /* we assume each string consists of lowercase English letters. */
            vector<int> lc2cnt(26, 0);
            string str_key;
            for (const auto& ch: str)
            {
                lc2cnt[ch - 'a'] += 1;
            }

            for (const auto& cnt: lc2cnt)
            {
                str_key.push_back('#');
                str_key += std::to_string(cnt);
            }

            if (groups.end() == groups.find(str_key))
            {
                int idx = ans.size();
                /* groups[str_key] = {str}; */
                groups[str_key] = idx;
                vector<string> temp = {str};
                ans.push_back(std::move(temp));
            }
            else
            {
                int idx = groups[str_key];
                ans[idx].push_back(str);
            }
        }

        return ans;
    }


    vector<vector<string>> groupAnagrams_sort(vector<string>& strs)
    {
        vector<vector<string>> ans;
        unordered_map<string, int> anagram2idx;

        for (const auto& str: strs)
        {
            string temp = str;
            std::sort(temp.begin(), temp.end()); // in-place

            if (anagram2idx.end() == anagram2idx.find(temp))
            {
                int idx = ans.size();
                vector<string> vec_str = {str};
                ans.push_back(std::move(vec_str));
                anagram2idx[temp] = idx;
            }
            else
            {
                int idx = anagram2idx[temp];
                ans[idx].push_back(std::move(str));
            }
        }

        return ans;
    }
};

int main()
{
    return 0;
}
