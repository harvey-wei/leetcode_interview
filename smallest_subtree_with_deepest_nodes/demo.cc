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

struct Result
{
    TreeNode* node; // The root of the smallest subtree containing all the deepest leaves.
    int depth; // The depth of the subtree.

    Result(TreeNode* _node, int _depth)
        : node(_node), depth(_depth)
    {}
};

class Solution {
public:
    /*
     * \param[in] root The root of the subtree.
     * \method The depth of a tree and the smalles subtree with all the deepest ndoes follow the
     *         same recursion rules.
     **/
    Result helper(TreeNode* root)
    {
        if (nullptr == root) return Result(nullptr, -1);

        Result left_result = helper(root->left);
        Result right_result = helper(root->right);

        if (left_result.depth > right_result.depth)
        {
            return Result(left_result.node, 1 + left_result.depth);
        }
        else if (left_result.depth < right_result.depth)
        {
            return Result(right_result.node, 1 + right_result.depth);
        }
        else
        {
             /* If the left subtree and right subtree have the same depth, the result is current root.
              **/
            return Result(root, right_result.depth + 1);
        }


    }

    TreeNode* subtreeWithAllDeepest(TreeNode* root) {

        return helper(root).node;
    }
};
