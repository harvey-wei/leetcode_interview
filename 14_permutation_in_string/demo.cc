#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* https://leetcode.com/problems/permutation-in-string/submissions/ */
class Solution {
public:
    bool is_all_zero(const vector<int> nums)
    {
        for (const auto &cnt: nums)
        {
            if (0 != cnt)
            {
                return false;
            }
        }

        return true;
    }

    bool checkInclusion(string s1, string s2)
    {
        if (s2.length() < s1.length())
        {
            return false;
        }
        /* Time: O(|s1|)*/
        vector<int> letter2cnt(26, 0);
        /* for (const auto &ch: s1) */
        /* { */
        /*     letter2cnt[ch - 'a'] += 1; */
        /* } */

        int len_s1 = s1.length();
        /*[ ) s2.length() - 0
          [s, e) length = e - s, s = e - length
          How to calculate the start index of the last window of length len_s1?
          We know end index (exclusive) is s2.length(). Hence, start index (inclusive) is
          s2.length() - len_s1!
          Time: O(|s1||s2|) inefficient.
          Consecutive windows overlap with each other! ->  redundancy!
          We need double pointers to rescue!
        */
        /* for (int i = 0; i <= (s2.length() - len_s1); ++i) */
        /* { */
        /*     for (int j = i; j < i + len_s1; ++j) */
        /*     { */
        /*         letter2cnt[s2[i] - 'a'] -= 1; */
        /*     } */
        /* } */

        /* Double pointers are used to indicate the start and end index of the window with length
           == length of s1. (inclusive, [start, end])
           Key insights: move left pointer to left, cancel the effect of previous left element
           move right pointer to right, add the effect of new end element!
           // But we need a initial window to trigger this. //
           for (right pointer is moving in one direction)
           {
              initialize left pointer <= right pointer
              while (left pointer <= right pointer)
              {
                moving right pointer.
              }
           }

        */
        /*
           check the first window of length equal to s1 in s2.
        */
        for (int i = 0; i < len_s1; ++i)
        {
            letter2cnt[s1[i] - 'a'] += 1;
            letter2cnt[s2[i] - 'a'] -= 1;
        }

        if (is_all_zero(letter2cnt))
        {
            return true;
        }

        for (int right = len_s1; right < s2.length(); ++right)
        {
            int left = right - len_s1;
            letter2cnt[s2[left] - 'a'] += 1;
            letter2cnt[s2[right] - 'a'] -=1;

            if (is_all_zero(letter2cnt))
            {
                return true;
            }
        }

        return false;
    }
};

class SolutionTwo
{
public:
    bool is_all_zero(const std::vector<int>& letter2cnt)
    {
        for (const auto& num : letter2cnt)
        {
            if (0 != num)
            {
                return false;
            }
        }

        return true;
    }

    bool checkInclusion(string s1, string s2) {
        /* both s1 and s2 are ensured to non-empty! */
        /* corner case */
        if (s1.size() > s2.size())
        {
            return false;
        }

        /**
         * Order does not count which leads us to encode s1 into a hashmap from letter to
         * number of occurrences.
         * Given all the keys of hashmap comes from 26 lowercase English letters, we use std::vector
         * to emulate the hashmap.
         */
        std::vector<int> letter2cnt(26, 0);
        for (const auto ch : s1)
        {
            ++letter2cnt[ch - 'a'];
        }
        /**
         * At this point, letter2cnt becomes a target state.
         * The problem reduces to search for a window which can zero the whole letter2cnt.
         */

        /* Initialize the state */
        for(size_t i = 0; i < s1.size(); ++i)
        {
            --letter2cnt[s2[i] - 'a'];
        }

        if (is_all_zero(letter2cnt))
        {
            return true;
        }

        /* why <= s2.size() - s1.size() ?
         * think in semi-open interval [i, j) j - i == length of array.
         * size() - (size() - s1.size()) == s1.size()*/
        for (size_t i = 1; i <= s2.size() - s1.size(); ++i)
        {
            /* update the state */
            ++letter2cnt[s2[i - 1] - 'a'];
            --letter2cnt[s2[i + s1.size() - 1] - 'a'];

            /* check the state */
            if (is_all_zero(letter2cnt))
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    SolutionTwo sol;
    string s1 = "ab", s2 = "eidbaooo";
    /* string s1 = "ab", s2 = "eidboaoo"; */
    cout << (true == sol.checkInclusion(s1, s2) ? "true" : "false") << endl;

    return 0;
}
