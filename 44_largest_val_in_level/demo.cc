#include <vector>
#include <queue>
#include <climits>

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
    vector<int> largestValues(TreeNode* root)
    {
        vector<int> res;
        if (nullptr == root) return res;

        queue<TreeNode*> node_q;
        TreeNode* curr = nullptr;
        node_q.push(root);
        /* res.push_back(root->val); */
        int curr_cnt = 1;
        int next_cnt = 0;
        int max_val = INT_MIN;

        while (!node_q.empty())
        {
            curr = node_q.front();
            node_q.pop();
            --curr_cnt;
            max_val = max(max_val, curr->val);

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
                /* All current level nodes are poped. */
                curr_cnt = next_cnt;
                next_cnt = 0;

                res.push_back(max_val);
                max_val = INT_MIN;
            }
        }

        return res;
    }
};
