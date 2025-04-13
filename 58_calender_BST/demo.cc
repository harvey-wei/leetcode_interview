#include <climits>
#include <limits>
#include <algorithm>
#include <map>


class MyCalendar {
public:
    MyCalendar() {

    }

	/**
	 * Use binary search tree to maintain sorted data structure of dynamic data.
	 * Here, we use std::map (TreeMap) to store startTime as key, endTime as statellite data
	 * Difference from static intervals, here we ensures no overlappoing interval all the way!
	 * KEY: So, for each incoming (startTime, endTime), we search double-sided nearest neighbors by startTime
	 */
    bool book(int startTime, int endTime)
	{
		if (0 == intervals.size())
		{
			intervals[startTime] = endTime;
			return true;
		}
		else
		{
			int left_start_time, right_start_time;
			bool has_left = false, has_right = false;

			find_nearest(startTime, left_start_time, right_start_time, has_left, has_right);

			// [startTime, endTime).
			if (has_left && intervals[left_start_time] > startTime)
			{
				return false;
			}

			if (has_right && right_start_time < endTime)
			{
				return false;
			}

			// Can be inserted to calender  update intervals
			intervals[startTime] = endTime;

			return true;
		}


    }

private:
	std::map<int, int> intervals; // map startTime to endTime

	void find_nearest(int startTime,
			int& left_start_time,
			int& right_start_time,
			bool& has_left,
			bool& has_right)
	{
		// right can be startTime
		auto right = intervals.lower_bound(startTime); // the fist element in increasing order of BST who >= startTime!

		// traversal order is ascending! compare with right
		auto left = right == intervals.begin() ? intervals.end() : std::prev(right);

		if (intervals.end() != right)
		{
			has_right = true;
			right_start_time = right->first;
		}
		else
		{
			has_right = false;
		}


		if (intervals.end() != left)
		{
			has_left = true;
			left_start_time = left->first;
		}
		else
		{
			has_left = false;
		}

	}
};

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(startTime,endTime);
 */
