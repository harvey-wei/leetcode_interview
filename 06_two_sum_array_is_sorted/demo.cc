#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
public:
    /* Ignore the key property that the array is sorted. We can use hash set to do membership. */
    /* Time: O(Nd) with N being the total count of numbers and d the count of occurrences of the
       same value.
       Space: O(N + d)
    */
    vector<int> twoSum_hashmap(vector<int>& numbers, int target)
    {
        /* You can not use the same number twice!
           But the same number might appear more then once!
           Why to use hashmap!
           number as key, vector of indices as values!
           we can also use set of pair(number, index)
           but we need define the hash function for it!
        */
        unordered_map<int, vector<uint>> num2idx;
        vector<int> indices(2);

        for (uint i = 0; i < numbers.size(); ++i)
        {
            num2idx[numbers[i]].push_back(i);
        }

        for (uint i = 0; i < numbers.size(); ++i)
        {
            int addend = target - numbers[i];
            if (num2idx.find(addend) != num2idx.end())
            {
                int j = -1;

                for (const auto &idx: num2idx[addend])
                {
                    if (i != idx)
                    {
                        j = idx;
                    }
                }

                if (i > j)
                {
                    indices[0] = j + 1;
                    indices[1] = i + 1;
                }
                else
                {
                    indices[0] = i + 1;
                    indices[1] = j + 1;
                }
                break;
            }

        }

        return indices;
    }

    int binar_search(const vector<int> &nums, const int &target, const int &excluded_idx)
    {
        /* Time: O(logN)
           Space: O(1)
        */
        assert(nums.size() >= 1);
        for (int i = 0; i < nums.size() - 1; ++i)
        {
            if (nums[i] > nums[i + 1])
            {
                cout << "The input array is not sorted in non-descending order! " << endl;
                return -1;
            }
        }

        /* [l, r) -> interval length = r - l ->  m = (r -l) / 2 + l
           [2, 3) -> m = (3 - 2) / 2 + 2 = 2
           [2, 2) -> interval_length == 0;
        */
        int l = 0;
        int r = nums.size();

        while (true)
        {
            /* interval_length ==0 means the target is NOT FOUND! */
            if (r == l) return -1;

            int m = l + (r - l) / 2;
            if ((excluded_idx != m) && target == nums[m])
            {
                return m;
            }
            else if ((excluded_idx == m) && target == nums[m])
            {
                // the same number might be to the right of nums[m]
                l = m + 1;
            }
            else if (target > nums[m])
            {
                l = m + 1; // Beware [l, r)
            }
            else
            {
                /* target < nums[m]*/
                r = m; // Beware [l, r]
            }
        }
    }

    /* Leverage the key property that the array is sorted. We can use binary search. */
    vector<int> twoSum_binary_search(vector<int>& numbers, int target) {
        /*Time: O(n log n)
          Space: O(1)
        */
        vector<int> indices(2);
        for (int i = 0; i < numbers.size(); ++i)
        {
            int addend = target - numbers[i];
            int addend_idx = binar_search(numbers, addend, i);
            if (-1 != addend_idx)
            {
                /* More compact! */
                indices[0] = 1 + min(i, addend_idx);
                indices[1] = 1 + max(i, addend_idx);
                break;
            }
        }

        return indices;
    }

    /* Leverage the sorted array and double pointers.
       Time: O(n)
       Space: O(1)
    */
    vector<int> twoSum(vector<int>& numbers, int target) {
        /* Time: O(n)
           Space: O(1)
        */
        int left = 0, right = numbers.size() - 1;
        vector<int> indices(2, 1);
        while (left < right)
        {
            int curr_sum = numbers[left] + numbers[right];
            if (target == curr_sum)
            {
                indices[0] += left;
                indices[1] += right;
                break;
            } else if (curr_sum > target)
            {
                /*why not --left?
                  The left pointer goes from left to right!
                  The right pointer moves from right to left!
                */
                --right;
            } else if (curr_sum < target)
            {
                ++left;
            }
        }

        return indices;
    }
};

void print_vec(const vector<int> & vecs)
{
    for (const auto vec: vecs)
    {
        cout << vec << ", ";
    }

    cout << endl;
}

int main()
{
    Solution sol;
    /* vector<int> numbers = {2,7,11,15}; */
    /* int target = 9; */

    vector<int> numbers = {1, 3, 4, 4};
    int target = 8;

    /* vector<int> numbers = {2,7,11,15}; */
    /* int target = 9; */

    /* vector<int> indices = sol.twoSum_hashset(numbers, target); */
    vector<int> indices = sol.twoSum(numbers, target);
    print_vec(indices);

    return 0;
}
