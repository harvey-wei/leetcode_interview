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
				/* If the heap size < k, push! */
                min_heap.push(num);
            }
            else
            {
				/* If the min-heap size hits k, we only push what is larger than curent min.*/
                const int& top = min_heap.top();
                if (num > top)
                {
					/* current top is ruled out. */
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
