#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>


using namespace std;

class RandomizedSet
{
    private:
        std::vector<int> nums;
        std::unordered_map<int, int> num2idx; // Map number to its index in nums.
    public:
        RandomizedSet()
        {
        }

        bool insert(int val)
        {
            if (num2idx.end() == num2idx.find(val))
            {
                int idx = nums.size();
                nums.push_back(val);
                num2idx[val] = idx;

                return true;
            }
            else
            {
                return false;
            }
        }

        bool remove(int val)
        {
            if (num2idx.end() != num2idx.find(val))
            {
                int idx = num2idx[val];
                num2idx.erase(val);

                if (idx == nums.size() - 1)
                {
                    nums.pop_back();

                    /* End int is removed */
                }
                else
                {
                    swap(nums[idx], nums[nums.size() - 1]);
                    nums.pop_back();

                    /* Change the idx of original end int to idx */
                    num2idx[nums[idx]] = idx;
                }


                return true;
            }
            else
            {
                return false;
            }

        }

        int getRandom()
        {
            /* initialize random seed: */
            /* srand (time(0)); */

            int idx = rand() % nums.size(); // [0, nums.size() - 1]

            return nums[idx];
        }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
