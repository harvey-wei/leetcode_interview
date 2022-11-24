/* #include <unordered_set> */
#include <set>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

/* struct pair_hash */
/* { */
/*     inline size_t operator()(const pair<int, int>& x) */
/*     { */
/*         return x.first ^ x.second; */
/*     } */
/* }; */

// This is the robot's control interface.
// You should not implement it, or speculate about its implementation
class Robot {
  public:
    // Returns true if the cell in front is open and robot moves into the cell.
    // Returns false if the cell in front is blocked and robot stays in the current cell.
    bool move();

    // Robot will stay in the same cell after calling turnLeft/turnRight.
    // Each turn will be 90 degrees.
    void turnLeft();
    void turnRight();

    // Clean the current cell.
    void clean();
};


class Solution {
public:
    void backtrac(Robot& robot)
    {
        /* reverse the direction */
        robot.turnRight();
        robot.turnRight();

        /* move back*/
        robot.move();

        /* Turn back to parent direction */
        robot.turnRight();
        robot.turnRight();

    }
    void cleanRoomHelper(Robot& robot, int x, int y, int dir, set<pair<int, int>>& visisted)
    {
        pair<int, int> curr_pos(x, y);
        visisted.insert(curr_pos); // don't need to backtrack!
        robot.clean();

        /* Go clockwise: 0 - up, 1 - right, 2 - down, 3 - left */
        vector<vector<int>> dir_offset = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        for (int i = 0; i < 4; ++i)
        {
            /* Cylic -> modulo (% the number of the sections.) */
            /* The direction of robot does not need to be preserved. */
            /* The purpose of unchoosing is to make sure we can exploret the next choice correctly.*/
            int dir_new = (dir + i) % 4;
            int x_new = x + dir_offset[dir_new][0];
            int y_new = y + dir_offset[dir_new][1];

            if (visisted.end() == visisted.find(pair<int, int>(x_new, y_new)) &&
                    robot.move())
            {
                cleanRoomHelper(robot, x_new, y_new, dir_new, visisted);

                /* backtrack */
                backtrac(robot);
            }

            /* Make the next choice have the right direction. */
            robot.turnRight();
        }

    }

    void cleanRoom(Robot& robot) {
        set<pair<int, int>> visisted;
        cleanRoomHelper(robot, 0, 0, 0, visisted);
    }
};

int main()
{
    return 0;
}
