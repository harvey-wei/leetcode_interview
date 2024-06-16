#include <queue>


using namespace std;
/**
 * Definition for a binary tree node.
 */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    void dfs(TreeNode* curr, int depth, int& max_depth, int& leftmost)
    {
        if (nullptr == curr)
        {
            /* base case: leaf */
            return;
        }
        else
        {
            if (depth > max_depth)
            {
                /* Reach a new level. */
                leftmost = curr->val;
                max_depth = depth;
            }

            dfs(curr->left, depth + 1, max_depth, leftmost);
            dfs(curr->right, depth + 1, max_depth, leftmost);
        }

    }

    int findBottomLeftValue(TreeNode* root)
    {
        int leftmost = 0;
        int max_depth = -1; // root is level 0

        dfs(root, 0, max_depth, leftmost);

        return leftmost;
    }
};

class SolutionIter {
public:
    int findBottomLeftValue(TreeNode* root)
    {
        /* root is ensured not to be null. */
        queue<TreeNode*> node_q;
        TreeNode* curr = nullptr;
        node_q.push(root);
        int curr_cnt = 1;
        int next_cnt = 0;
        int leftmost = root->val;

        while (!node_q.empty())
        {
            curr = node_q.front();
            node_q.pop();
            --curr_cnt;

            if (nullptr != curr->left)
            {
                node_q.push(curr->left);
                ++next_cnt;
            }

            if (nullptr != curr->right)
            {
                node_q.push(curr->right);
                ++next_cnt;
            }

            if (0 == curr_cnt)
            {
                /**
                 * Current level are completely popped out.
                 * The front in queue is the leftmost in the NEXT level.
                 */
                curr_cnt = next_cnt;
                next_cnt = 0;

                /* Access front before check empty */
                if (!node_q.empty())
                {
                    leftmost = node_q.front()->val;
                }
            }
        }

        return leftmost;
    }
};
