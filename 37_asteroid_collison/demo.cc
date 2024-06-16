#include <iostream>
#include <vector>

using  namespace std;


class Solution
{
public:
    vector<int> asteroidCollision(vector<int>& asteroids)
    {
        vector<int> ast_stack;

        for (int i = 0; i < asteroids.size(); ++i)
        {
            if (ast_stack.empty() || asteroids[i] > 0)
            {
                // push current asteroid
                ast_stack.push_back(asteroids[i]);
            }
            else
            {
                /* ast_stack is not empyt and current is < 0 */
                bool is_current_destroyed = false;

                while (!is_current_destroyed && !ast_stack.empty() && ast_stack.back() > 0)
                {
                    if (abs(asteroids[i]) < ast_stack.back())
                    {
                        is_current_destroyed = true;
                    }
                    else if (abs(asteroids[i]) == ast_stack.back())
                    {
                        is_current_destroyed = true;
                        ast_stack.pop_back();
                    }
                    else
                    {
                        /* back is destroyed */
                        ast_stack.pop_back();
                    }
                }

                // push current if not destroyed
                if (!is_current_destroyed) ast_stack.push_back(asteroids[i]);
            }
        }


        return ast_stack;
    }

};
