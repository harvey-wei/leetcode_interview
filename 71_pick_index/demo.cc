#include <vector>
#include <random>
#include <iostream>

using namespace std;

class Solution {
public:
	vector<long int> presum;
	long int total;

    Solution(vector<int>& w) {
		/* presum.reserve(w.size()); */
		/*  https://stackoverflow.com/questions/7397768/choice-between-vectorresize-and-vectorreserve */
		presum.resize(w.size());
		total = 0;
		for (int i = 0; i < w.size(); ++i)
		{
			total += w[i];
			presum[i] = total;
		}
    }

    int pickIndex() {
		int p = rand() % total; // 0, 1, ..., total - 1

		// if presum[i-1] =< (or no left)  p < presum[i] -> return i.
		// we need to finde the least ^ upper bound for p.
		// Find loose upper bound and then narraw down
		// branch and bound?
		int l = 0;
		int r = presum.size();
		int m =0;


		while (r > l)
		{
			// m in [l, r) m could be zero
			m = l + (r - l) / 2;

			if (presum[m] > p)
			{
				// check left <= p?
				if (m == 0 || presum[m - 1] <= p)
				{
					return m;
				}
				else
				{
					// search tight upper bound by go left
					r = m; // exclusive
				}

			}
			else
			{
				// presum[m] < p
				l = m + 1; // inclusive
			}

		}

		return -1;
    }
};


int main()
{
	vector<int> w = {1};
	Solution* obj = new Solution(w);
	int param_1 = obj->pickIndex();

	std::cout << "param_1 " << param_1 << std::endl;
}
/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */
