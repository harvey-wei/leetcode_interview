#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	void combine_helper(const int& n, const int& k, int curr, vector<int>& com,
			vector<vector<int>>& results)
	{
		if (com.size() == k)
		{
			results.push_back({com});
		}
		else if (curr <= n)
		{
			/* We must check curr == n */
			/* choose explore unchoose */

			/* case 1: not choose curr */
			combine_helper(n, k, curr + 1, com, results);

			/* case 2: choose curr */
			com.push_back(curr);
			combine_helper(n, k, curr +  1, com, results);
			com.pop_back();
		}

	}

    vector<vector<int>> combine(int n, int k)
	{
		/* Choose k ints from [1, n] */
		vector<vector<int>> results;
		vector<int> com;
		combine_helper(n, k, 1, com, results);

		return results;

    }
};
