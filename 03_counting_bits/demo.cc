#include <iostream>
#include <vector>
#include <cassert>
#include <random> // for random device
using namespace std;


class Solution {
public:
    vector<int> countBits_naive(int n)
    {
        assert(n >= 0); // leading bit is zero.
        std::vector<int> one_cnt(n + 1, 0);

        for (int i = 1; i <= n; ++i)
        {
            int num = i;
            while (num)
            {
                one_cnt[i] += num & 1;

                /* Shift bits of i to right until i becomes zero. */
                num >>= 1;
            }
        }

        return one_cnt;
    }

    vector<int> countBits_efficient(int n)
    {
        /*O(nk) with k as the count of bits. */
        assert(n >= 0);
        std::vector<int> one_cnt(n + 1, 0);

        /* Key insight: i & (i - 1) set the right-most 1 to zero if i is unsigned int or positive.*/
        for (int i = 1; i <= n; ++i)
        {
            int num = i;

            /* Set the right-most 1 to zero until num reaches zero. */
            while (num)
            {
                num = num & (num -1);
                one_cnt[i] += 1;
            }
        }


        return one_cnt;
    }

    vector<int> countBits_recuisve(int n)
    {
        std::vector<int> one_cnt(n + 1, 0);
        /*Key insight: one_cnt[i] = one_cnt[i & (i - 1)] + 1for i = 1, 2, 3, .., n */

        for (int i = 1; i <= n; ++i)
        {
            one_cnt[i] = one_cnt[i & (i - 1)] + 1;
        }

        return one_cnt;
    }

    vector<int> countBits(int n)
    {
        std::vector<int> one_cnt(n + 1, 0);
        assert(n >= 0);
        /* num = sum_{i = 0}^{i = n-1} a_{i} 2^{i}
           // for positive!
           If num is even, num and num / 2 has the same number of 1.
           If num is odd, num has one more 1 than num / 2;
        */
        /* Key insight: one_cnt[i] = one_cnt[i >> 2] + i & 1 if i > 0*/
        for (int i = 1; i <= n; ++i)
        {
            one_cnt[i] = one_cnt[i >> 1] + (i & 1);
        }

        return one_cnt;
    }

    void print_vec(const vector<int> &vec)
    {
        for (const auto &v: vec)
        {
            std::cout << v << std::endl;
        }
    }

    bool is_two_vecs_equal(const vector<int> &vec_one, const vector<int> &vec_two)
    {
        if (vec_one.size() != vec_two.size()) return false;

        for (uint i = 0; i < vec_one.size(); ++i)
        {
            if (vec_one[i] != vec_two[i]) return false;
        }

        return true;

    }

    void stress_test()
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> uniform_int_dist(0, 100000);

        Solution sol;

        while (true)
        {
            int n = uniform_int_dist(rng);
            std::vector<int> one_cnt_gt = sol.countBits_naive(n);
            /* std::vector<int> one_cnt_efficient = sol.countBits_efficient(n); */
            std::vector<int> one_cnt_efficient = sol.countBits(n);

            if (!is_two_vecs_equal(one_cnt_gt, one_cnt_efficient))
            {
                std::cout << "Failed on test case: " << n << std::endl;
                break;
            }
            else
            {
                std::cout << "Succeed on test case: " << n << std::endl;
            }
        }
    }
};

int main()
{
    Solution sol;
    /* std::vector<int> one_cnt = sol.countBits_naive(0); */
    /* std::vector<int> one_cnt_ = sol.countBits_naive(100000); */
    /* sol.print_vec(one_cnt); */
    /* sol.print_vec(one_cnt_); */

    sol.stress_test();

    return 0;
}
