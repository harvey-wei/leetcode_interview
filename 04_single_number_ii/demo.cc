#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    /*
       Time Complexity: O(N)
       Space Complexity: O(N) to keep the hashmap of N/3 elements
    */
    int singleNumber_hash_map(vector<int>& nums)
    {
        int single_num;
        unordered_map<int, int> int2cnt;
        for (const auto &num: nums)
        {
            if (int2cnt.end() == int2cnt.find(num))
            {
                /* num is not found */
                int2cnt[num] = 1;
            }
            else
            {
                ++int2cnt[num];
            }
        }

        for (const auto &it: int2cnt)
        {
            if (1 == it.second)
            {
                single_num = it.first;
            }
        }

        return single_num;
    }

    /* We care about the 1 in the binary representation only. */
    int singleNumber_sum(vector<int>& nums)
    {
        /* How to select the ith bit of int?
           (int >> i) & 1 for i = 0, 1, ...  (we can terminate until int >> i == 0)
           or bool(int & (1 << 1))
            Add the bits of the same place value for all numbers. Store the respective sum in sums.
            sums[0] = sum of bits at 0th bit
            If the sums[0] divide 3, then the 1's come from numbers which appears three times.
            Otherwise, the remainder 1 comes from the number which occurs only once.
        */
        const int int_bit_cnt = sizeof(int) * 8;

        vector<int> sums(int_bit_cnt, 0);

        /* precompute the sum of bits to save time. */
        for (auto &num: nums)
        {
            // Here we start at sign bit!
            for (uint i = 0; i < int_bit_cnt; ++i)
            {
                sums[i] += (num >> (int_bit_cnt - 1 - i)) & 1;
            }
        }

        // We must start at sign bit to avoid overflow and then shift to left bit by bit
        // single_num += 1 << 31 (1 << 31 = 2^31 is out of the int range [-2^31, 2^31 - 1])
        int single_num = 0;
        for (uint i = 0; i < int_bit_cnt; ++i)
        {
            single_num = (single_num << 1) + sums[i] % 3;
        }

        return single_num;
    }

    int singleNumber(vector<int> &nums)
    {
        /*
           Let's start from XOR operator which could be used to detect the bit which appears odd
           number of times: 1, 3, 5, etc.

           But we can design the logical operator.
           https://lenchen.medium.com/leetcode-137-single-number-ii-31af98b0f462
           For each bit, the 1 may occur 1 * k + 3 * n
           The count of occurrence: 1, 2, 3, 4,  when we scan the array of numbers.
           Hence, we need at least 2 bits to indicate it.
           00 -> 01 -> 10 -> 00
        */

        int low_bit =0, high_bit = 0;

        for (const auto &num: nums)
        {
            int low_bit_prev = low_bit;
            low_bit = (~high_bit & low_bit & ~num) | ( ~high_bit & ~low_bit & num);
            high_bit = (high_bit & ~low_bit_prev & ~num) | (~high_bit & low_bit_prev & num);
        }

        return low_bit;
    }


    int singleNumber_(vector<int> nums)
    {
        /* bit_sums[i] indicate the ith bit to the left of int */
        /* 0th bit is the MSB while 31th bit is the LSB */
        vector<int> bit_sums(32, 0);

        for (const auto& num : nums)
        {
            for (size_t i = 0; i < 32; ++i)
            {
                /* Note that the result of bitwise is still an int! */
                bit_sums[i] += (num & (1 << (31 - i))) ? 1 : 0;
            }
        }

        /* std::cout << "bit_sums: \n"; */
        /* for (const auto& s : bit_sums) */
        /* { */
        /*     std::cout << s << ","; */
        /* } */
        /**/
        /* std::cout << std::endl; */

        int result = 0;

        for (size_t i = 0; i < 32; ++i)
        {
            result = result | ((bit_sums[i] % 3) << (31 - i));
        }

        return result;
    }

};

int main()
{
    Solution sol;
    vector<int> nums = {2, 2, 3, 2};
    int sn = sol.singleNumber_(nums);
    cout << "single number is " << sn << std::endl;

    return 0;
}
