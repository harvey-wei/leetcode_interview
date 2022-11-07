#include <iostream>
#include <unordered_map>
#include <vector>
#include <random>

using namespace std;

void show_vec(vector<int>& vec)
{
    for (int i = 0; i < vec.size(); ++i)
    {
        cout << " " <<  vec[i];
    }

    cout << endl;

}

class RandomizedSet {
private:
        unordered_map<int, int> int2idx;
        vector<int> nums;

public:
    RandomizedSet() {

    }

    bool insert(int val) {
        if (int2idx.end() == int2idx.find(val))
        {
            /* not exists */
            int idx = nums.size();
            nums.push_back(val);
            int2idx.insert({val, idx});

            return true;
        }
        else
        {
            return false;
        }
    }

    bool remove(int val) {
        if (int2idx.end() != int2idx.find(val))
        {
            /* val exists. */
            int idx = int2idx[val];
            int2idx.erase(val); // erase by key

            if (*nums.end() == val)
            {
                nums.pop_back();
                return true;
            }

            /* erase val from a vector
               step 1: swap val with the element at the end.
               step 2: erase the end element.
               O(1).
            */
            swap(nums[idx], nums[nums.size() - 1]);

            if (int2idx.end() != int2idx.find(nums[idx]))
            {
                int2idx[nums[idx]] = idx;
            }

            nums.pop_back();
            return true;
        }
        else
        {
            /* not exists */
            return false;
        }
    }

    int getRandom() {

    /* step 1: set up an engine */
    /* std::random_device rd; */
    /* std::mt19937 rng(rd()); // mt stands for Mersenne twister. */

    /* step 2: specify the distribution type. */
    /* std::uniform_int_distribution<> uniform_int_dist(1, 6);  // inclusive */
    /* std::uniform_real_distribution<> uniform_real_dist(10, 20); // inclusive */
    /* std::normal_distribution<> normal_dist(0, 1); // mean = 1, std_dev = 1 */

    /* step 3: get random numbers */
    /* const int cnt = 5; */
    /* for (int i = 0; i < cnt; ++i) */
    /* { */
    /*     std::cout << uniform_int_dist(rng) << " "; */
    /* } */

    /* step 1: set up an engine */
    /* std::random_device rd; */
    /* std::mt19937 rng(rd()); */

    /* step 2: specify the distribution type. */
    /* std::uniform_int_distribution<> uni_int(0, nums.size() -1); // inclusive */

    /* step 3: */
    /* int idx = uni_int(rng); */

    int idx = rand() % nums.size();

    return nums[idx];
    }
};

int main()
{
    RandomizedSet * obj = new RandomizedSet();
    bool ret;
    ret = obj->remove(0);
    cout << "remove " << ret << endl;
    ret = obj->remove(0);
    cout << "remove " << ret << endl;
    ret = obj->insert(0);
    cout << "insert " << ret << endl;
    obj->getRandom();
    ret = obj->remove(0);
    cout << "remove " << ret << endl;
    ret = obj->insert(0);
    cout << "insert " << ret << endl;

    delete obj;
    return 0;
}
