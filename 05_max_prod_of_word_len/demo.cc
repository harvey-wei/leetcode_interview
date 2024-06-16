#include <iostream>
#include <vector>

using namespace std;


class Solution {
public:
    int maxProduct(vector<string>& words)
    {
        /**
         * 1. Convert each word to a 32-bit integer, where the ith bit is 1 if the word contains the ith letter.
         * 2. Compare each pair of words and find the maximum product of their lengths.
         * 3. The time complexity is O(n^2) and the space complexity is O(n).
         * Note that each word consists of lowercase letters only.
         * So we can use a 32-bit integer to represent the word.
         * If two word does not share common letters, the ith bit of their integer should be 0-0, 0-1 or 1-0 instead of 1-1.
         * That is, bitwise and should be zero.
         */

        std::vector<int> word_hash_tab(words.size(), 0);
        for (size_t i = 0; i < words.size(); ++i)
        {
            for (const auto& ch : words[i])
            {
                /* set word_hash_tab[i]'s [ch - 'a']th bit to 1 */
                word_hash_tab[i] |= 1 << (ch - 'a');
            }
        }

        int max_prod = 0;
        for (size_t i = 0; i < words.size(); ++i)
        {
            for (size_t j = i + 1; j < words.size(); ++j)
            {
                /**
                 * If words[i] and words[j] does not share common letters,
                 * each bit of letter should be 0-0, 0-1, 1-0 instead of 1-1
                 * Bitwise and should be zero
                 */
                if (0 == (word_hash_tab[i] & word_hash_tab[j]))
                {
                    max_prod = std::max<size_t>(max_prod, words[i].size() * words[j].size());
                }
            }
        }

        return max_prod;
    }
};


int
main(int argc, char** argv)
{
    Solution sol;
    vector<string> words = {"abcw","baz","foo","bar","xtfn","abcdef"};
    /* int max_prod = sol.maxProduct_bitmask(words); */
    int max_prod = sol.maxProduct(words);
    cout << "max_prod: " << max_prod << endl;

    return 0;
}


/**
 * Bitwise operator for int
 * 1. How to set the right-most 1 of int to zero?
 *      a & (a - 1)
 * 2. How to halve the int ?
        (a +  1) >> 1 Note plus 1 for negative int
 * 3. How to get the ith bit value of int? (i = 0, 1, 2, ... 31)
        (a >> i) & 1
 * 4. How to set the ith bit to 1?
        a |= (1 << i)
 * 5. How to unset the ith bit to 1?
        a &= ~(1 << i)
 */


        /*
         * (a >> i) & 1 -> get the ith bit of a.
         * a |= (1 << i) -> set the ith bit of a.
         * a &= ~(1 << i) -> unset the ith bit of a.
         * ^ is the XOR operator.
         * ~ is the bitwise NOT operator.
         * ~(1 << i) -> is a mask with all bits set to 1 except the ith bit.
         */
