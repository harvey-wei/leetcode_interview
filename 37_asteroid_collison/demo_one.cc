#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        /*
           + ->
           - <-
           + -> <- -
           if current is - <-, we need decide whether it will collide with top.
           if current is + <-, push to stack directly.
           if stack is empty, push to stack

           Note that: vector<int> can simulate stack push_back and pop_back O(1)
           Recall that: we can swap with the back and then delete.
        */
        vector<int> stack;

        for (int i = 0; i < asteroids.size(); ++i)
        {
            if (stack.empty())
            {
                stack.push_back(std::move(asteroids[i]));
            }
            else
            {
                /* not empty */
                if (asteroids[i] > 0)
                {
                    stack.push_back(std::move(asteroids[i]));
                }
                else
                {
                    /* current is < 0. */
                    bool is_curr_destroyed = false;

                    while (!is_curr_destroyed && !stack.empty() && stack.back() > 0)
                    {
                        if (abs(asteroids[i]) > abs(stack.back()))
                        {
                            stack.pop_back();
                        }
                        else if (abs(asteroids[i]) == abs(stack.back()))
                        {
                            is_curr_destroyed = true;
                            stack.pop_back();
                        }
                        else
                        {
                            is_curr_destroyed = true;
                        }
                    }

                    if (!is_curr_destroyed)
                    {
                        stack.push_back(std::move(asteroids[i]));
                    }
                }

            }
        }

        return stack;

    }
};

int main()
{
    return 0;
}
