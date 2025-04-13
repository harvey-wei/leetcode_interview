#include <vector>
#include <limits>

using namespace std;


class Solution{
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2)
	{
		std::vector<int> counts(1001, 0);

		for (const auto& num: arr1)
		{
			counts[num] += 1;
		}

		int arr1_ptr = -1;
		for (int i = 0; i < arr2.size(); ++i)
		{
			while (counts[arr2[i]] > 0)
			{
				++arr1_ptr;
				arr1[arr1_ptr] = arr2[i];

				--counts[arr2[i]];
			}
		}

		for (int i = 0; i < counts.size(); ++i)
		{
			while (counts[i] > 0)
			{
				++arr1_ptr;
				arr1[arr1_ptr] = i;

				--counts[i];
			}

		}


		return arr1;
	}
};


class Solution__ {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2)
	{
		std::vector<int> counts(1001, 0);

		for (const auto& num : arr1)
		{
			++counts[num];
		}

		int i = 0;
		for (const auto& num : arr2)
		{
			while (counts[num] > 0)
			{
				arr1[i++] = num;
				--counts[num];
			}
		}

		for (int num = 0; num <= 1000; ++num)
		{
			while (counts[num] > 0)
			{
				arr1[i++] = num;
				--counts[num];
			}
		}

		return arr1;
	}
};
class Solution_ {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2)
	{
		int min_int = std::numeric_limits<int>::max();
		int max_int = std::numeric_limits<int>::min();

		int i = 0;
		while (i < arr1.size() && (i + 1) < arr1.size())
		{
			if (arr1[i] > arr1[i + 1])
			{
				max_int = max(max_int, arr1[i]);
				min_int = min(min_int, arr1[i + 1]);
			}
			else
			{
				max_int = max(max_int, arr1[i + 1]);
				min_int = min(min_int, arr1[i]);
			}

			i += 2;
		}

		if (i == arr1.size() - 1)
		{
			max_int = max(max_int, arr1[i]);
			min_int = min(min_int, arr1[i]);
		}

		std::vector<int> counts(max_int - min_int + 1, 0);

		for (const auto& num: arr1)
		{
			++counts[num - min_int];
		}

		int j = 0;
		for (int idx = 0; idx < arr2.size(); ++i)
		{
			while (counts[arr2[idx] - min_int] > 0)
			{
				arr1[j++] = arr2[idx];
				--counts[arr2[idx] - min_int];
			}
		}

		for (int num = min_int; num <= max_int; ++num)
		{
			while (counts[num - min_int] > 0)
			{
				arr1[j++] = num;
				--counts[num - min_int];
			}
		}

		return arr1;
    }
};


int
main(int argc, char** argv)
{
	return 0;
}
