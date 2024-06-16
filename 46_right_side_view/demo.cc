#include <iostream>
#include <queue>
#include <vector>
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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;

        if (nullptr == root) return res;

        /* In BFS, push the end node of each level to res */
        queue<TreeNode*> node_q;
        TreeNode* curr;
        node_q.push(root);

        int curr_cnt = 1;
        int next_cnt = 0;

        while (!node_q.empty())
        {
            curr = node_q.front(); // oldest
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
                res.push_back(curr->val);
                curr_cnt = next_cnt;
                next_cnt = 0;
            }
        }

        return res;
    }
};

int main()
{
    return 0;
}
