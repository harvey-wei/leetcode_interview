#include <iostream>
#include <vector>
#include <stack>
#include <queue>

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
       https://leetcode.com/problems/binary-tree-inorder-traversal/solution/
    */
    void inorderTraversal_helper(const TreeNode * const root, vector<int> &result)
    {
        if (nullptr == root)
            /* Return to the calling function and proceed to its next line. */
            return;

        inorderTraversal_helper(root->left, result);
        result.push_back(std::move(root->val));
        inorderTraversal_helper(root->right, result);

        return;
    }

    vector<int> inorderTraversal_recur(TreeNode* root) {
        vector<int> result;
        inorderTraversal_helper(root, result);
        return result;
    }

    vector<int> inorderTraversal(TreeNode* root)
    {
        vector<int> result;
        stack<TreeNode*> stack_trees;
        TreeNode * curr = root;

        while (nullptr != curr || !stack_trees.empty())
        {
            /* traverse the left subtree of curr.*/
            while (nullptr != curr)
            {
                stack_trees.push(std::move(curr));
                curr = curr->left;
            }

            /* pop the parent node. */
            curr = stack_trees.top();
            stack_trees.pop();
            result.push_back(std::move(curr->val));

            /* traverse the right sub-tree. */
            curr = curr->right;
        }

        return result;
    }

    void post_order_traversal_helper(TreeNode* root, vector<int>& result)
    {
        /* base case and return to the calling position and proceed to the next line. */
        if (nullptr == root) return;

        post_order_traversal_helper(root->left, result);
        post_order_traversal_helper(root->right, result);
        result.push_back(std::move(root->val));
    }

    vector<int> postorderTraversal_recur(TreeNode* root)
    {
        vector<int> result;
        post_order_traversal_helper(root, result);
        return result;
    }

    vector<int> postorderTraversalOld(TreeNode* root)
    {
        vector<int> result;

        TreeNode * curr = root;

        /* The previous traversed right sub-tree. */
        TreeNode * prev = nullptr; /* TODO: revise?*/

        stack<TreeNode*> stack_tree;
        /*
           push curr into stack
           pop means traversed!
           top is to check the parent node (a nearest sub-tree contains the left and right
           sub-trees.)
           Don't need to maintain a hash-table to track whether the node is visited!
        */
        while (nullptr != curr || !stack_tree.empty())
        {
            /* Walk left down to the (sub)-tree. */
            while (nullptr != curr)
            {
                stack_tree.push(std::move(curr));
                curr = curr->left;
            }

            /* The parent of the leaf-node/tree. */
            curr = stack_tree.top();

            if (nullptr == curr->right || prev == curr->right)
            {
                /* The right sub-tree is completely popped!
                   We need pop and then top again.
                */
                stack_tree.pop();
                result.push_back(std::move(curr->val));
                prev = curr;
                curr = nullptr;
            }
            else
            {
                /* walk the right sub-tree. */
                curr = curr->right;
            }
        }

        return result;
    }

    vector<int> postorderTraversal(TreeNode* root)
    {
        vector<int> result;
        stack<TreeNode* > stack_trees;

        TreeNode* curr = root;
        TreeNode* prev = nullptr;
        while (nullptr != curr || !stack_trees.empty())
        {
            /* Traverse the left subtree (go to the leftmost node)*/
            while (nullptr != curr)
            {
                stack_trees.push(std::move(curr));
                curr = curr->left;
            }

            /* see the most recent node's right subtree. */
            curr = stack_trees.top();

            if (nullptr == curr->right || prev == curr->right)
            {
                /* right subtree is not existent or already traversed! */
                result.push_back(std::move(curr->val));
                stack_trees.pop();

                prev = curr;
                /* set the curr to nullptr to continuously top! */
                curr = nullptr;
            }
            else
            {
                /* right subtree is not traversed. */
                curr = curr->right;
            }
        }


        return result;
    }

    /*
       https://leetcode.com/problems/binary-tree-preorder-traversal/
    */
    void preorderTraversalHelper(TreeNode* root, vector<int>& result)
    {
        if (nullptr == root) return;

        result.push_back(std::move(root->val));
        preorderTraversalHelper(root->left, result);
        preorderTraversalHelper(root->right, result);
    }

    vector<int> preorderTraversal_recur(TreeNode* root) {
        vector<int> result;
        preorderTraversalHelper(root, result);
        return result;
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> stack_trees;
        TreeNode* curr = root;

        while (nullptr != curr || !stack_trees.empty())
        {
            while (nullptr != curr)
            {
                result.push_back(std::move(curr->val));
                stack_trees.push(curr);
                curr = curr->left;
            }

            curr = stack_trees.top();
            stack_trees.pop();
            curr = curr->right;
        }

        return result;
    }

    /* Morris Traversal
       Time: O(N) with N being the total of nodes.
       Each node is travsed at most two times. The first time is to connect to its successor while
       the second time is to really traverse it (store it in the result!).
       Hence, the overall time complexity is O(N).
       Space: O(1)
    */
    vector<int> preorder_traversal_morris(TreeNode* root)
    {
        vector<int> result;

        TreeNode * curr = root;

        while (nullptr != curr)
        {
            result.push_back(std::move(curr->val));
            if (nullptr != curr->left)
            {
                /* Find the node which is the predecessor of the prev->right by going right down to
                   the leaf if possible!

                */
                TreeNode * prev = curr;
                curr = curr->left;
                while (nullptr != curr->left || nullptr != curr->right)
                {
                    if (nullptr != curr->right)
                    {
                        /* Go right if possible. */
                        curr = curr->right;
                    }
                    else
                    {
                        /* Right is imposiible and just try going left. */
                        curr = curr->left;
                    }
                }

                TreeNode * prev_right = prev->right;
                prev->right = prev->left;
                prev->left = nullptr;
                curr->right = prev_right;
                curr = prev->right;
            }
            else
            {
                curr= curr->right;
            }

        }
        return result;
    }

    /* This method needs a new data-structure threaded tree!
       It is kind of like flattening/unrolling/unwrapping the binary tree.
       Ref: https://en.wikipedia.org/wiki/Threaded_binary_tree
       Make all right child pointers that would normally be null point to the in-order successor
       (if not null), and all left child that would normally be null point to the in-order
       predecessor of the node (if exists).
       This assumes the traversal order is the same as in-order traversal of the tree.
    */
    vector<int> inorder_traversal_morris(TreeNode* root)
    {
        vector<int> result;
        TreeNode* curr = root;
        TreeNode* prev = nullptr;
        while (nullptr != curr)
        {
            if (nullptr == curr->left)
            {
                /* No left subtree! */
                result.push_back(std::move(curr->val));
                curr = curr->right;
            }
            else
            {
                /* Find the right-most node of the left subtree. */
                TreeNode * left_subtree = curr->left;
                prev = curr;
                curr = curr->left;
                prev->left = nullptr; /* Null out the left pointer of parent node!*/
                while (nullptr != curr->right)
                {
                    curr = curr->right;
                }

                curr->right = prev;
                curr = left_subtree;
            }
        }

        return result;
    }

    vector<int> post_order_traversal_morris(TreeNode* root)
    {
        vector<int> result;
        TreeNode * curr = root;
        /* Here, we store them in rervese order in pre_order_traversal. (N->R->L)
           We recursively thread the last node of R to the first node of L and
           update the curr to its right child tree.
        */
        while (nullptr != curr)
        {
            result.push_back(std::move(curr->val));
            TreeNode* prev = curr;
            if (nullptr != curr->right)
            {
                curr = curr->right;
                /* Go left if possible until hitting the leaf. */
                while (nullptr != curr->left || nullptr != curr->right)
                {
                    if (nullptr != curr->left)
                    {
                        curr = curr->left;
                    }
                    else if(nullptr != curr->right)
                    {
                        curr = curr->right;
                    }
                }

                /* Heat the last node of right subtree. */
                curr->right = prev->left;
                prev->left = nullptr;
                curr = prev->right;
            }
            else
            {
                curr = curr->left;
            }
        }

        /* Dont't forget to reverse the order!
           Reverse the array by double pointers rather than alloacte another array of the same size.
        */
        int l = 0;
        int r = result.size() - 1;
        while (l < r)
        {
            swap(result[l], result[r]);
            // update the l and r
            ++l;
            --r;
        }

        return result;
    }

    /*
       https://leetcode.com/problems/binary-tree-level-order-traversal/solution/
       The definition of depth, level, and height count the number of edges!
       https://stackoverflow.com/questions/59151282/what-is-level-of-root-node-in-a-tree
    */
    void level_order_recur_helper(TreeNode* root, int level, vector<vector<int>>& result)
    {
        /* base case: hit the dummy null node of leaf!
           return to the calling function and do the backward process!
        */
        if (nullptr == root) return;

        /* We start from level 0 and increase it by one after one recursive call.
           level past the end of result by one : level = result.size()
           Don't use level > result.size() - 1.
        */
        if (level == result.size()) result.push_back(std::move(vector<int>()));

        result[level].push_back(std::move(root->val));
        level_order_recur_helper(root->left, level + 1, result);
        level_order_recur_helper(root->right, level + 1, result);
    }

    vector<vector<int>> level_order_recur(TreeNode* root)
    {
        /* Space complexity is the depth of call stacks!
           worst case: O(N) a linked list of N nodes!
           best case: O(logN).
           We don't include the result vector!
        */
        vector<vector<int>> result;
        level_order_recur_helper(root, 0, result);
        return result;
    }

    /* pop followed by its child nodes! */
    vector<vector<int>> level_order(TreeNode* root)
    {
        vector<vector<int>> result;
        queue<TreeNode*> queue_trees;
        int level = 0;
        int curr_cnt = 0;
        int next_cnt = 0;

        if (nullptr != root)
        {
            queue_trees.push(root);
            ++curr_cnt;
        }

        while (!queue_trees.empty())
        {
            TreeNode * top = queue_trees.front();
            queue_trees.pop();
            --curr_cnt;

            /* Traverse level by level and from top to bottom.
               level start at zero!
               Once level goes past the end of result, we need push a vector.
            */
            if (level == result.size())
            {
                result.push_back(std::move(vector<int>()));
            }

            result[level].push_back(std::move(top->val));

            if (nullptr != top->left)
            {
                queue_trees.push(top->left);
                ++next_cnt;
            }

            if (nullptr != top->right)
            {
                queue_trees.push(top->right);
                ++next_cnt;
            }

            if (0 == curr_cnt)
            {
                ++level;
                curr_cnt = next_cnt;
                next_cnt = 0;
            }
        }

        return result;
    }

    vector<vector<int>> level_order_morris(TreeNode* root)
    {
        vector<vector<int>> result;

        return result;
    }

};

int main()
{
    int a = 0;

    return 0;
}
