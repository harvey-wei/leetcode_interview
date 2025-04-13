#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;


class Solution {
public:

	int getID(long x, long w)
	{
		// if x is negative and x == NEG_MIN, then x + 1 is overlow. hence we need long!
		return x >= 0? x / w : (x + 1) / w -1;
	}

    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
	{
        if (t < 0) return false;
		/* Image all numbers in nums are distributed in contiguous bucketes with size w
		 * w = t + 1 is the number of days in one month.
		 * nums[i] is your birthday, you want know if theres is someone else who has birthday w days
		 later or earlier than you.
		 * Linear scan to unconver buckets
		 * we only consider previous k integers. -> need
		 */
		unordered_map<long, long> buckets;
		long w = t + 1;

		// bucket for nums[i] exists, return true.
		// if buckets for nums[i] does exists, insert to hash map buckets for future check.
		// once future number falls into this new buckets, return agains.
		for (int i = 0; i < nums.size(); ++i)
		{
			long bucket_id = getID(nums[i], w);

			// Assure buckets only consider i-1, i-2, ... i-k
			// case 1: if bucket_id aleady exists, true
			if (buckets.end() != buckets.find(bucket_id)) return true;

			// case 2: if bucket_id - 1 exists, and inequality holds, true
			if (buckets.end() != buckets.find(bucket_id - 1) &&
					std::abs(nums[i] - buckets[bucket_id - 1]) <= t)
			{
				return true;
			}

			// case 3: if bucket_id + 2 exists, and inequality holds, true
			if (buckets.end() != buckets.find(bucket_id + 1) &&
					std::abs(nums[i] - buckets[bucket_id + 1]) <= t)
			{
				return true;
			}

			// Now bucket with bucket_id is empty create a new one.
			buckets[bucket_id] = nums[i];

			if (i >= k)
			{
				// (k+1) was pushed into window, we need remove left most one in window
				buckets.erase(getID(nums[i - k], w));
			}
		}

        return false;
    }
};

class Solution_
{
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff)
	{
		/*
		 * For i, we consider j = i-1, i-2, i - indexDiff
		 * |nums[i] - nums[j]| <= valueDiff
		 *  -valueDiff <=  n_i - n_j <= valueDiff
		 *    n_i - valueDiff <= n_j <= n_i +valueDiff
		 */
		std::multiset<int> window; // we need to use std::multiset to allow duplicates.
		for (int i = 0; i < nums.size(); ++i)
		{
			// if i == indexDiff, window already tracks indexDiff previous integers.
			// if i > indexDiff, we need delete nums[i - indexDiff - 1]
			if (i > indexDiff)
			{
				auto to_erase = window.find(nums[i - indexDiff -1]);
				if (to_erase != window.end())
				{
					window.erase(to_erase); // only remove one
				}
			}

			auto lower = window.lower_bound(nums[i] - valueDiff);

			if (window.end() != lower && (*lower) <= (nums[i] + valueDiff))
			{
				return true;
			}


			window.insert(nums[i]);
		}

		return false;

    }
};


int main_() {
    std::set<int> s = {1, 3, 5, 7, 9};

    auto lb = s.lower_bound(4);  // points to 5
    auto ub = s.upper_bound(4);  // points to 7

    if (lb != s.end())
        std::cout << "lower_bound(4): " << *lb << "\n";

    if (ub != s.end())
        std::cout << "upper_bound(4): " << *ub << "\n";

    return 0;
}


#include <iostream>
#include <set>
#include <iterator>

int main() {
    std::set<int> s = {10, 20, 30, 40, 50};
    int target = 60;

    auto right = s.lower_bound(target);  // first element >= target
    auto left = (right == s.begin()) ? s.end() : std::prev(right);  // element < target

    if (left != s.end())
        std::cout << "Left of " << target << ": " << *left << "\n";
    else
        std::cout << "No element less than " << target << "\n";

    if (right != s.end())
        std::cout << "Right of " << target << ": " << *right << "\n";
    else
        std::cout << "No element greater than or equal to " << target << "\n";

    return 0;
}
