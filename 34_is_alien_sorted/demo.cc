#include <vector>
#include <unordered_map>
#include <string>

using namespace std;


class Solution {
public:

    bool isAlienSorted(vector<string>& words, string order)
    {
        unordered_map<char, int> letter2idx; // fron letter has small index
        for (int i = 0; i < order.size(); ++i)
        {
            letter2idx[order[i]] = i;
        }

        for (int i = 0; i <= words.size() - 2; ++i)
        {
            const auto& w1 = words[i];
            const auto& w2 = words[i + 1];

            bool is_sorted = false;

            int j = 0;
            for (j = 0; j < w1.size() && j < w2.size(); ++j)
            {
                if (letter2idx[w1[j]] < letter2idx[w2[j]])
                {
                    // correct order and check the next pair of words
                    is_sorted = true;
                    break;
                }
                else if (letter2idx[w1[j]] > letter2idx[w2[j]])
                {
                    // wrong order
                    return false;

                }
                else
                {
                    // same char and check the next pair of char
                }
            }

            if (!is_sorted && j != w1.size())
            {
                return false;
            }

        }

        return true;
    }
};
