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

        queue<TreeNode*> curr_q;
        queue<TreeNode*> next_q;
        queue<TreeNode*>* curr_queue = &curr_q;
        queue<TreeNode*>* next_queue = &next_q;

        curr_queue->push(root);
        while (!curr_queue->empty())
        {
            TreeNode* front = curr_queue->front();
            curr_queue->pop();

            if (front->left != nullptr)
            {
                next_queue->push(std::move(front->left));
            }

            if (front->right != nullptr)
            {
                next_queue->push(std::move(front->right));
            }

            if (curr_queue->empty())
            {
                res.push_back(std::move(front->val));
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
