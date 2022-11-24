#include <iostream>
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
    /*
       subprolem: max_gain(root) = max_gain of length when including node root and maybe one of
       its subtrees.
       relate: max_gain(root) = root->val + max(max(max_gain(root->left), 0),
            max(max_gain(root-right), 0))
       If the gain is negative, we just stop there.
       topological order: post-order traversal
       base case: max_gain(null) = 0;
       original problem: max_gain(Root of the given tree)
       time: O(|V|)

       However, we can start a new path at any node. Via this recurrence, we can track the max sum.
    */
    int max_gain(TreeNode* root, int& curr_max_sum)
    {
        /* base cases */
        if (nullptr == root)
        {
            return 0;
        }

        /* Negative gain is not included. */
        int max_left = max<int>(max_gain(root->left, curr_max_sum), 0);
        int max_right = max<int>(max_gain(root->right, curr_max_sum), 0);

        /* Keep track of the real max sum. */
        /* The length of starting a new path. zero is not inlcuded.
           After traverse all nodes, we try all possible max paths.
        */
        int len_new = root->val + max_left + max_right;
        curr_max_sum = max(curr_max_sum, len_new);


        /* For the recurrence */
        return root->val + max<int>(max_left, max_right);

    }

    int maxPathSum(TreeNode* root)
    {
        int max_sum = INT_MIN;

        max_gain(root, max_sum);
        return max_sum;
    }
};
