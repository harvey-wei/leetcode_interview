#include <vector>
#include <stack>


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

class TreeTraversal
{
    public:
        /* The general pattern should match the first iteration of the tree traversal! */
        /* Hence, you can generilize from the first iteration. */
        vector<int> preorderTraversal(TreeNode* root)
        {
            if (nullptr == root) return {};

            /* Root -> Left -> Right */
            vector<int> res;
            stack<TreeNode*> stack_nodes;
            TreeNode* curr = root;

            while (nullptr != curr || !stack_nodes.empty())
            {
                if (nullptr != curr)
                {
                    /* Process and go left */
                    res.push_back(curr->val);

                    /* We need process curr->right after traverse all its left. */
                    /* So we only need to push its right */
                    if (nullptr != curr->right)  stack_nodes.push(curr->right);

                    curr = curr->left;
                }
                else
                {
                    /* Left subtree of most recent processed root is traversed */
                    /* Now process its right */
                    curr = stack_nodes.top();
                    stack_nodes.pop();
                }
            }

            return res;
        }


        vector<int> inorderTraversal(TreeNode* root)
        {
            if (nullptr == root) return {};

            vector<int> res;
            stack<TreeNode*> stack_nodes;
            TreeNode* curr = root;

            /* Left -> Root -> Right */
            while (nullptr != curr || !stack_nodes.empty())
            {
                if (nullptr != curr)
                {
                    /* We need to process curr and its right subtree later. */
                    /* So we need push curr */
                    stack_nodes.push(curr);
                    curr = curr->left;
                }
                else
                {
                    /* Left is traversed  and process its parent, go right */
                    curr = stack_nodes.top();
                    stack_nodes.pop();
                    res.push_back(curr->val);

                    curr = curr->right;
                }
            }

            return res;
        }

        vector<int> postorderTraversal(TreeNode* root)
        {
            if (nullptr == root) return {};

            /* Left -> Right -> Parent */
            vector<int> res;
            TreeNode* curr = root;
            TreeNode* prev = nullptr;
            stack<TreeNode*> tree_stack;

            while (nullptr != curr || !tree_stack.empty())
            {
                if (nullptr != curr)
                {
                    /* We need to process curr and curr->right. */
                    tree_stack.push(curr);
                    curr = curr->left;
                }
                else
                {
                    /* Left is processed. Now check its parent's right  */
                    curr = tree_stack.top(); // left's parent
                    if (nullptr == curr->right || prev == curr->right)
                    {
                        /* No right subtree or right subtree is already processed. */
                        tree_stack.pop();
                        res.push_back(curr->val);
                        prev = curr;
                        curr = nullptr; // make tree_stack further pop in the next iteration.
                    }
                    else
                    {
                        /* right subtree is not traversed. */
                        curr = curr->right;
                    }
                }
            }

            return res;
        }
};


























/* https://www.shubo.io/iterative-binary-tree-traversal/ */
/* https://www.enjoyalgorithms.com/blog/iterative-binary-tree-traversals-using-stack */
class SolutionInIter {
public:
    vector<int> inorderTraversal(TreeNode* root)
    {
        if (nullptr == root) return {};

        vector<int> res;
        /* Order of push to result: L -> Curr_Root -> R. */
        /* We need a pointer to memorize the Curr_Root. */
        // Note the difference between going order and pop order.

        stack<TreeNode*> stack_nodes;
        TreeNode* curr = root;
        while (nullptr != curr || !stack_nodes.empty())
        {
            /* We need further check the case */
            if (nullptr != curr)
            {
                /* Push to stack before go left first */
                stack_nodes.push(curr) ;
                curr = curr->left;
            }
            else
            {
                /* Left or Right is traversed */
                TreeNode* parent = stack_nodes.top();
                stack_nodes.pop();
                res.push_back(parent->val);

                /* Go to right */
                curr = parent->right;
            }
        }

        return res;
    }
};


class SolutionPreRecur {
public:
    void preorderTraversalRecur(TreeNode* root, vector<int>& res)
    {
        if (nullptr == root) return;

        res.push_back(root->val);
        preorderTraversalRecur(root->left, res);
        preorderTraversalRecur(root->right, res);

        /* No extra operations after the final recusion. */
        /* Hence, this recusion call is tail-recursive. */

        return;
    }

    vector<int> preorderTraversal(TreeNode* root)
    {
        vector<int> res;
        preorderTraversalRecur(root, res);

        return res;
    }
};


class SolutionPreorderIter {
public:
    vector<int> preorderTraversal(TreeNode* root)
    {
        if (nullptr == root)
        {
            return {};
        }

        vector<int> res;

        stack<TreeNode*> stack_node;
        stack_node.push(root);
        TreeNode* top;

        while (!stack_node.empty())
        {
            /***** repeated *****/
            top = stack_node.top();
            stack_node.pop();

            res.push_back(top->val);
            /***** repeated *****/

            /* stack is FILO, we need pop from stack top-bottom, left-right order to result*/
            /* We need push right first to stack. */
            /* Then right is popped lastly. */
            // We must push right first ->right is visted last
            if (nullptr != top->right)
            {
                stack_node.push(top->right);
            }

            // Left will be poped ealier than right.
            if (nullptr != top->left)
            {
                stack_node.push(top->left);
            }
        }

        return res;
    }
};
