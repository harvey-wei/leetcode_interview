#include <iostream>
#include <vector>
using namespace std;


class Solution {
public:
    int singleNumber(vector<int>& nums)
    {
        /*
         * How to extract the ith bit of int? i = 0, 1, 2,..., 31
         * Here 0 -> 31 corresponds to LSB to MSB
         * (int >> i) & 1
         */
        const size_t int_bit_cnt = sizeof(int) * 8;
        std::vector<int> bit_sums(int_bit_cnt, 0);

        for (size_t i = 0; i < nums.size(); ++i)
        {
            /* We start at sign bit (MSB)*/
            /* j goes from 0 -> 31 => int_bit_cnt - 1 - j varies from 31 to 0*/
            for (size_t j = 0; j < int_bit_cnt; ++j)
            {
                bit_sums[j] += (nums[i] >> (int_bit_cnt - 1 - j)) & 1;
            }
        }


        /* 0 -> 31 corresponds to MSB -> LSB */
        /**
         * How to recover the int from the vector of bit value?
         * Start at MSB and add bit value to one-bit-left-shifted result.
         */
        int result = 0;
        for (int j = 0; j < int_bit_cnt; ++j)
        {
            result = (result << 1) + bit_sums[j] % 3;
        }

        return result;
    }
};


int
main(int argc, char** argv)
{
    Solution sol;

    std::vector<int> nums = {2, 2, 3, 2};
    std::cout << "singleNumber: " << sol.singleNumber(nums) << std::endl;

    return 0;
}
