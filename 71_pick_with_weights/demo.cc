#include <vector>
#include <random>
#include <iostream>

using namespace std;


/**
 * Seven-steps from problem to code.
 */
class Solution {
    public:
        Solution(vector<int>& w)
        {
            sums.resize(w.size(), 0);
            int curr_sum = 0;
            for (int i = 0; i < w.size(); ++i)
            {
                curr_sum += w[i];
                sums[i] = curr_sum;
            }

            /**
             * Work an example by hand.
             * w = [1, 3, 4]
             * sums = [1, 4, 8] is sorted in ascending order.
             * [0, 1), [1, 4), [4, 8)
             * Generate random integer [0, 7] and determined the interval
             * If random_int 3,
             * if random_int < sums[m], update r = m
             */
        }

        int pickIndex()
        {
            int p = rand() % sums[sums.size() - 1];

            int l = 0;
            int r = sums.size() - 1;

            // [l, r]
            // Our goal is to find l and r such that p >= sums[l] and < sums[r]

            while (r - l + 1 > 1)
            {
                int m = l + (r - l + 1) / 2;

                if (p < sums[m])
                {
                    // treat m as right end
                    if (0 == m || p >= sums[m - 1])
                    {
                        return m;
                    }
                    else
                    {
                        // sums[m] is too large
                        r = m - 1;
                    }

                }
                else
                {
                    /* p >= sums[m] */
                    l = m;

                }

            }

            return l;
        }

    private:
        std::vector<int> sums;
};

int
main()
{
    std::vector<int> w{1, 2, 3, 4};
    Solution* obj = new Solution(w);
    int param_1 = obj->pickIndex();

    std::cout << "param_1: " << param_1 << std::endl;
}

