#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool is_no_common_char(const string &s1, const string &s2)
    {
        unordered_set<char> char_set;

        for (uint i = 0; i < s1.length(); ++i)
        {
            char_set.insert(s1[i]);
        }

        for (uint i = 0; i < s2.length(); ++i)
        {
            /* O(1) WHP */
            if (char_set.end() != char_set.find(s2[i])) return false;
        }

        return true;
    }

    int maxProduct_hashset_naive(vector<string>& words)
    {
        int max_prod = 0;
        // O(n^2k)
        for (uint i = 0; i < words.size() - 1; ++i)
        {
            for (uint j = i + 1; j < words.size(); ++j)
            {
                /* O(k) we can pre-compute to save this time.*/
                /* Each word is inserted to a set words.size() - 1 times -> redundancy */
                if (is_no_common_char(words[i], words[j]))
                {
                    int prod = words[i].length() * words[j].length();
                    max_prod = max(prod, max_prod);
                }
            }
        }

        return max_prod;
    }

    int maxProduct_hashset_efficient(vector<string> &words)
    {
        /* Key insight: trade space for time!
           Store the letters in a set for each word and then look up.
        */
        int max_prod = 0;

        vector<unordered_set<char>> letters(words.size());

        for (uint i = 0; i < words.size(); ++i)
        {
            for (uint j = 0; j < words[i].length(); ++j)
            {
                letters[i].insert(words[i][j]);
            }
        }

        for (uint i = 0; i < words.size(); ++i)
        {
            for (uint j = i + 1; j < words.size(); ++j)
            {
                bool is_no_common_char = true;
                for (int k = 0; k < words[i].length(); ++k)
                {
                    if (letters[j].end() != letters[j].find(words[i][k]))
                    {
                        is_no_common_char = false;
                        break;
                    }
                }

                if (is_no_common_char)
                {
                    int curr_prod = words[i].length() * words[j].length();
                    max_prod = max(curr_prod, max_prod);
                }
            }
        }

        return max_prod;

    }

    int maxProduct_array(vector<string> &words)
    {
        /*Insight: All letters are in lower case!
          -> Maintain an array of length 26 to label the existence of a certain letter.
          You need to use this information: There are 26 lower-case letters in total.

          Compute when you need to use it -> might compute the same thing multiple times.
          Pre-compute all you need in advance and then look up the table -> trade space for time.
          -> similar to memoization!
        */
        int max_prod = 0;
        const int lc_cnt = 26;

        vector<vector<bool>> flags(words.size(), vector<bool>(lc_cnt, false));

        /*Time: O(nk)
        */
        for (uint i = 0u; i < words.size(); ++i)
        {
            for (uint j = 0u; j < words[i].length(); ++j)
            {
                flags[i][words[i][j] - 'a'] = true;
            }
        }

        /* Time: O(n^2)*/
        for (uint i = 0; i < words.size(); ++i)
        {
            for (uint j = i + 1; j < words.size(); ++j)
            {
                /*
                   Instead of comparing each letter in a word with another word, we check if each of
                   26 lower case letters exist in both words[i] and words[j].
                   > Time: O(1) instead fo O(k) with k the max length of word.
                */
                bool is_no_common_char = true;

                for (int k = 0; k < lc_cnt; ++k)
                {
                    if (true == flags[i][k] && true == flags[j][k])
                    {
                        is_no_common_char = false;
                        break;
                    }
                }

                if (is_no_common_char)
                {
                    int curr_prod = words[i].length() * words[j].length();
                    max_prod = max(curr_prod, max_prod);
                }
            }

        }

        return max_prod;

    }

    int maxProduct_bitmask(vector<string> &words)
    {
        int max_prod = 0;

        vector<int> flags(words.size(), 0);
        const int lc_cnt = 26;

        for (uint i = 0; i < words.size(); ++i)
        {
            for (uint j = 0; j < words[i].length(); ++j)
            {
                /* LSB indicates 'a'*/
                flags[i] |= (1 << (words[i][j] - 'a'));
            }
        }

        /* Time: O(n^2)*/
        for (uint i = 0; i < words.size(); ++i)
        {
            for (uint j = i + 1; j < words.size(); ++j)
            {
                /*
                   Instead of comparing each letter in a word with another word, we check if each of
                   26 lower case letters exist in both words[i] and words[j].
                   > Time: O(1) instead fo O(k) with k the max length of word.
                */

                /* Key insight: if ith word and jth word have letters in common, bitwise-and of
                   their bitmasks should be > 0. */
                if (0 == (flags[i] & flags[j]))
                {
                    int curr_prod = words[i].length() * words[j].length();
                    max_prod = max(curr_prod, max_prod);
                }

                /* int is_no_common_char = true; */
                /* for (int k = 0; k < lc_cnt; ++k) */
                /* { */
                /*     if ((1 == ((flags[i] >> k) & 1)) && (1 == ((flags[j] >> k) & 1))) */
                /*     { */
                /*         is_no_common_char = false; */
                /*         break; */
                /*     } */
                /* } */

                /* if (is_no_common_char) */
                /* { */
                /*     int curr_prod = words[i].length() * words[j].length(); */
                /*     max_prod = max(curr_prod, max_prod); */
                /* } */
            }

        }

        return max_prod;
    }
};

int main()
{
    Solution sol;
    vector<string> words = {"abcw","baz","foo","bar","xtfn","abcdef"};
    int max_prod = sol.maxProduct_bitmask(words);
    cout << "max_prod: " << max_prod << endl;

    int a = 1;
    int b = a << 3;
    cout << "a " << a << endl;
    cout << "b " << b << endl;

    return 0;
}
