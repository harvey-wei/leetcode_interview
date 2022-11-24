#include <queue>
#include <vector>
using namespace std;

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;

        for (const auto& num: nums)
        {
            if (min_heap.size() < k)
            {
                min_heap.push(num);
            }
            else
            {
                const int& top = min_heap.top();
                if (num > top)
                {
                    min_heap.pop();
                    min_heap.push(num);
                }
            }
        }

        return min_heap.top();
    }
};

int main()
{
    return 0;
}
