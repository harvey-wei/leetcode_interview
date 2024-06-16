#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        vector<vector<string>> results;
        unordered_map<string, int> map;

        for (const auto& str : strs)
        {
            string str_key = str;
            std::sort(str_key.begin(), str_key.end());

            if (map.end() == map.find(str_key))
            {
                /* str_key does not exists. */
                int idx = results.size();
                map[str_key] = idx;
                results.push_back({str});
            }
            else
            {
                const int& idx = map[str_key];
                results[idx].push_back(str);
            }
        }

        return results;
    }
};


class Solution_ {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs)
    {
        vector<vector<string>> results;
        unordered_map<string, int> map;

        for (const auto& str : strs)
        {
            std::vector<int> letter2cnt(26, 0);

            for (const auto& ch : str)
            {
                ++letter2cnt[ch - 'a'];
            }

            string str_key = "";
            for (const int& cnt : letter2cnt)
            {
                str_key += "#";
                str_key += std::to_string(cnt);
            }

            if (map.end() == map.find(str_key))
            {
                /* str_key does not exists. */
                int idx = results.size();
                map[str_key] = idx;
                results.push_back({str});
            }
            else
            {
                const int& idx = map[str_key];
                results[idx].push_back(str);
            }
        }

        return results;
    }
};

int
main()
{

}
