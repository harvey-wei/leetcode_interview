#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <climits> // INT_MAX, INT_MIN


using namespace std;

class Solution
{
public:
    int findMinDifference(vector<string>& timepoints)
    {
        /* timepoints.size() >= 2 */
        const int tp_cnt = 24 * 60;
        std::vector<bool> tp_map(tp_cnt, false);

        int min_tp = INT_MAX;
        int max_tp = INT_MIN;
        for (const auto& tp : timepoints)
        {
            int minutes = std::stoi(tp.substr(0, 2)) * 60 + std::stoi(tp.substr(3, 2));
            min_tp = min(min_tp, minutes);
            max_tp = max(max_tp, minutes);

            if (tp_map[minutes])
            {
                // same time point
                return 0;
            }
            else
            {
                tp_map[minutes] = true;
            }
        }

        int min_diff = INT_MAX;
        // compare adjacent
        int i = min_tp;
        int j;

        while (i < max_tp)
        {
            /* Find the next true */
            j = i + 1;

            while (j <= max_tp && !tp_map[j])
            {
                ++j;
            }

            if (j <= max_tp && tp_map[j])
            {
                min_diff = min(j - i, min_diff);
            }

            i = j;
        }

        // min + 24 * 60 - max;
        return  min(min_diff, min_tp + tp_cnt - max_tp);
    }
};


class Solution_
{
public:
    int findMinDifference(vector<string>& timepoints)
    {
        const int time_point_cnt = 24 * 60;
        vector<int> tp_m;
        for (const auto& tp : timepoints)
        {
            int minis = stoi(tp.substr(0, 2)) * 60 + stoi(tp.substr(3, 2));
            tp_m.push_back(minis);
        }

        std::sort(tp_m.begin(), tp_m.end()); // non-descending order and in-place

        // diff of adjacent time points
        // [i, i + 1]  i + 1 < size()
        int min_diff = INT_MAX;
        for (int i = 0; i < tp_m.size() - 1; ++i)
        {
            min_diff = min(min_diff, tp_m[i + 1] - tp_m[i]);
        }

        // Diff of min + time_point_cnt - max
        return min(min_diff, tp_m[0] + time_point_cnt - tp_m[tp_m.size() - 1]);
    }

};
