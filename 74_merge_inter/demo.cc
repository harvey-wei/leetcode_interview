#include <vector>
#include <algorithm>


using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
		if (intervals.size() == 1) return intervals;

		// Store the online merged intervals when one-pass through sorted intervals
		vector<vector<int>> results;

		// sort intervals in order of ascendig start coorinate
		std::sort(intervals.begin(), intervals.end(),
				[](const vector<int>& lhs, const vector<int>& rhs)
				{
					// Put smaller start coorinate ahead
					return lhs[0] < rhs[0];
				});

		results.push_back(intervals[0]);
		for (int i = 1; i < intervals.size(); ++i)
		{
			auto& temp = results[results.size() - 1];
			if (intervals[i][0] <= temp[1])
			{
				// overlap
				if (intervals[i][1] > temp[1])
				{
					temp[1] = intervals[i][1];
				}
			}
			else
			{
				// not overlap
				results.emplace_back(intervals[i]);

			}
		}

		return results;
    }
};

using namespace std;

class Solution_ {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
		if (intervals.size() <= 1) return intervals;

		std::vector<vector<int>> results;
		/* Sort the intervals in increasing order of start end in place. */
		std::sort(intervals.begin(), intervals.end(),
				[](const vector<int>& lhs, const vector<int>& rhs)
				{
					/* Put the interval with smaller start end in front. */
					return lhs[0] < rhs[0];
				});

		results.push_back({intervals[0][0], intervals[0][1]});
		for (int i = 1; i < intervals.size(); ++i)
		{
			if (intervals[i][0] <= results[results.size()- 1][1])
			{
				if (intervals[i][1] > results[results.size() - 1][1])
				{
					/* Merge ith interval and previous interval */
					results[results.size() - 1][1] = intervals[i][1];
				}
			}
			else
			{
				results.push_back({intervals[i][0], intervals[i][1]});
			}
		}

		return results;
    }
};


int
main(int argc, char** argv)
{
	return 0;
}
