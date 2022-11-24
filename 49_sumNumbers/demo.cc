#include <stack>
using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution_iter {
public:
    struct TreeNodeSum
    {
        TreeNodeSum(TreeNode* _node = nullptr, int _sum = 0)
            : node(_node), sum(_sum)
        {}
        TreeNode* node;
        TreeNodeSum* left;
        TreeNodeSum* right;
        int sum;
    };

    int sumNumbers(TreeNode* root)
    {
    /*
       SRTBOT:
       Subproblem:
       f(x) = the path sum from root to x
       Relate:
       f(x) = f(x.parent) * 10 + x.val;
       Topological Order: preorder traversal
       Base:
       f(root) = root.val
       Original Problem;
       sum all f(leaf)
       Time:
       cnt of subproblems: O(|V|)
       work per subproblem: O(1)
       O(|V|)
    */
        if (nullptr == root)
        {
            return 0;
        }

        int total_sum = 0;

        stack<TreeNodeSum*> stack_tree;
        TreeNodeSum* curr = new TreeNodeSum(root, root->val);
        TreeNodeSum* parent = new TreeNodeSum(nullptr, 0);

        while (curr != nullptr || stack_tree.empty())
        {
            while (curr != nullptr)
            {
                stack_tree.push(curr);
                curr->sum = parent->sum * 10 + curr->sum;
                parent = curr;
                if (curr->node->left != nullptr)
                {
                    curr->left = new TreeNodeSum(curr->node->left, curr->node->left->val);
                }
                else
                {
                    curr->left = nullptr;
                }
                curr = curr->left;
            }

            curr = stack_tree.top();
            if (curr->node->left == nullptr && curr->node->right == nullptr)
            {
                total_sum += curr->sum;
                parent = curr;
                curr = nullptr;
            }
            else if (curr->node->right != nullptr)
            {
                curr->right = new TreeNodeSum(curr->node->right, curr->node->right->val);
                parent = curr;
                curr = curr->right;
            }
            else
            {
                curr = nullptr;
            }

            stack_tree.pop();
        }

        return total_sum;
    }
};

class Solution {
public:
    /*
       S: f(x, path_sum_top) is the total sum of tree x
       path_sum_top is the path sum from root to x's parent
       path_sum_curr = path_sum_top * 10 + x.val
       R: f(x, path_sum_top) = f(x.left, path_sum_curr) +
          f(x.right, path_sum_curr)
          Note we should pass path_sum_top by value since the recurrence will change the reference!
       T: pre-order
       B: f(nullptr) = 0, f(leaf, path_sum_leaf) = path_sum_leaf
       work an example by hands
    */
    int sumNumbers_helpr(TreeNode* root, int path_sum)
    {
        if (nullptr == root) return 0;
        path_sum = path_sum * 10 + root->val;

        if (nullptr == root->left && nullptr == root->right)
        {
            return path_sum;
        }

        /* */
        return sumNumbers_helpr(root->left, path_sum) + sumNumbers_helpr(root->right, path_sum);
    }

    int sumNumbers(TreeNode* root) {
        return sumNumbers_helpr(root, 0);
    }
};
