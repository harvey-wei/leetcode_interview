#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        /*
         * numbers is sorted in non-descending order.
         */
        assert(numbers.size() > 1);

        vector<int> result;

        int left = 0;
        int right = numbers.size() - 1;
        int sum = 0;

        while (left < right)
        {
            sum = numbers[left] + numbers[right];
            if (target == sum)
            {
                result.push_back(left + 1);
                result.push_back(right + 1);

                break;
            }
            else if (sum < target)
            {
                ++left;
            }
            else
            {
                /* sum > target */
                --right;
            }
            // update left and right
        }

        return result;
    }
};

int
main(int argc, char** argv)
{
    return 0;
}
