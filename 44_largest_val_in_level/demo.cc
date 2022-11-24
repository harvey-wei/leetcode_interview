#include <queue>
#include <iostream>
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
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;

        /* empty tree! */
        if (nullptr == root) return res;

        queue<TreeNode*> bfs_q;
        bfs_q.push(root);
        int curr_cnt = 1;
        int next_cnt = 0;
        int max_val = INT32_MIN;

        while (!bfs_q.empty())
        {
            TreeNode* front = bfs_q.front();
            bfs_q.pop();
            --curr_cnt;
            max_val = max<int>(max_val, front->val);

            if (nullptr != front->left)
            {
                bfs_q.push(front->left);
                ++next_cnt;
            }

            if (nullptr != front->right)
            {
                bfs_q.push(front->right);
                ++next_cnt;
            }

            if (0 == curr_cnt)
            {
                /* The current level is completely traversed. */
                curr_cnt = next_cnt;
                next_cnt = 0;
                res.push_back(max_val);
                max_val = INT32_MIN;
            }

        }

        return res;
    }
};

class Solution_double_queue{
public:
    vector<int> largestValues(TreeNode* root) {
        vector<int> res;
        if (nullptr == root) return res;

        queue<TreeNode*> curr_q;
        queue<TreeNode*> next_q;
        queue<TreeNode*>* curr_queue = &curr_q;
        queue<TreeNode*>* next_queue = &next_q;

        int max_val = INT32_MIN;  // -2^31
        curr_queue->push(root);

        while (!curr_queue->empty())
        {
            TreeNode* front = curr_queue->front();
            curr_queue->pop();
            max_val = max<int>(front->val, max_val);

            if (nullptr != front->left)
            {
                next_queue->push(front->left);
            }

            if (nullptr != front->right)
            {
                next_queue->push(front->right);
            }

            /* check whether curr_queue is empty. */
            if (curr_queue->empty())
            {
                /* Current level is completely traversed. */
                res.push_back(max_val);
                max_val = INT32_MIN;
                swap(curr_queue, next_queue);
            }

        }

        return res;
    }
};
int main()
{
    return 0;
}
