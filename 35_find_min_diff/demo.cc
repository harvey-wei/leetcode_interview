#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int parse_time_to_minutes(const string& time)
    {
        /*HH: MM*/
        bool is_colon_visited = false;
        vector<int> hour;
        vector<int> minute;
        for (int i = 0; i < time.size(); ++i)
        {
            if (':' == time[i])
            {
                is_colon_visited = true;
            }
            else if (time[i] >= '0' && time[i] <= '9')
            {
                if (!is_colon_visited)
                {
                    hour.push_back(time[i] - '0');
                }
                else
                {
                    minute.push_back(time[i] - '0');
                }
            }
        }

        int mins = (hour[0] * 10 + hour[1]) * 60 + minute[0] * 10 + minute[1];

        return mins;
    }

    int findMinDifference(vector<string>& timePoints)
    {
        /*
            00:00 - 23:59
            24 * 60  = 1440

            Observation 1: In sorted time point series, min diff is in between two successive
            points OR 00:00 and HH:MM. Hence, you need to convert 00:00 to 24:00= 1420

            comparison-based sort: O(nlogn)
            linear sort: O(n) + 1440-elment vector
        */
        const int time_len = 24 * 60; // we don't use 0
        if (timePoints.size() > time_len) return 0;

        vector<bool> time_point(time_len + 1, false); // put zero to the end.
        int min_time = INT32_MAX;
        int max_time = -INT32_MAX;

        for (const auto& point: timePoints)
        {
                int mins = parse_time_to_minutes(point);
                if (0 == mins)
                {
                    mins = time_len;
                }

                if (time_point[mins]) return 0;

                time_point[mins] = true;
                min_time = min(min_time, mins);
                max_time = max(max_time, mins);
        }

        /* Note that timePoints.size() >= 2*/
        int32_t min_diff = min_time + 24 * 60 - max_time;
        int prev = 1;
        int next = 1;

        while (prev < time_point.size())
        {
            if (time_point[prev])
            {
                next = prev + 1;

                if (next >= time_point.size()) break;

                while (next < time_point.size() && !time_point[next])
                {
                    ++next;
                }

                if (next < time_point.size() && time_point[next])
                {
                    min_diff = min(next - prev, min_diff);
                    prev = next;
                }
                else
                {
                    break;
                }
            }
            else
            {
                ++prev;
            }
            /* Don't forget to update prev and next pointers. */
        }

        /* Need to rectify! */
        return min_diff;
    }
};

int main()
{
    Solution sol;
    /* string time = "23:59"; */
    string time = "00: 00";
    std::cout << "time to minutes: " << sol.parse_time_to_minutes(time) << std::endl;
    /* vector<string> timePoints = {"23: 59", "00: 00", "00:00"}; */
    /* vector<string> timePoints = {"00: 00", "04: 00", "22:00"}; */
    vector<string> timePoints = {"05:31","22:08","00:35"}; 
    int min_diff = sol.findMinDifference(timePoints);
    std::cout << "min_diff: " << min_diff << std::endl;

    return 0;
}
