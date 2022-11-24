#include <queue>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int findBottomLeftValue(TreeNode* root)
    {
        /* Assert: There are at least one node in the given binary tree. */
        int bottom_left;
        queue<TreeNode*> q;
        int curr_cnt = 0;
        int next_cnt = 0;

        q.push(std::move(root));
        ++curr_cnt;
        bottom_left = root->val;

        while (!q.empty())
        {
            TreeNode* front = q.front();
            q.pop();
            --curr_cnt;

            if (nullptr != front->left)
            {
                q.push(std::move(front->left));
                ++next_cnt;
            }

            if (nullptr != front->right)
            {
                q.push(std::move(front->right));
                ++next_cnt;
            }

            /* Check to see if the current level is completely traversed. */
            if (0 == curr_cnt)
            {
                curr_cnt = next_cnt;
                next_cnt = 0;

                if (!q.empty())
                {
                    bottom_left = q.front()->val;
                }
            }
        }

        return bottom_left;
    }
};
