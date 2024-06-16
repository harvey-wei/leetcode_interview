#include <iostream>
#include <vector>

using namespace std;

void
print_vector(const std::vector<int>& vec)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

class Solution
{
public:
    vector<int> countBits(int n)
    {
        /**
         * The key insight: i & (i - 1) set the rightmost 1 to zero if i is unsigned or
         * positve.
         * Index is unsigned int.
         * one_cnt of i = one_cnt of (i & (i - 1)) + 1
         */
        std::vector<int> ones_cnt(n + 1, 0);

        /* Note that ones_cnt[0] = 0 */
        for (size_t i = 1; i < ones_cnt.size(); ++i)
        {
            ones_cnt[i] = 1 + ones_cnt[i & (i - 1)];
        }

        return ones_cnt;
    }
};

int
main(int argc, char** argv)
{
    Solution sol;
    int n = 2;

    print_vector(sol.countBits(n));

    n = 5;
    print_vector(sol.countBits(n));

    return 0;
}
