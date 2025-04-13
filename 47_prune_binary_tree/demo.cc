#include <iostream>
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

// https://leetcode.com/problems/binary-tree-level-order-traversal/editorial/
class SolutionV1 {
public:
	// pass by copying pointer
	bool dfs_postorder(TreeNode* root)
	{
		bool is_left_zero = false;
		bool is_right_zero = false;

		if (nullptr != root->left)
		{
			is_left_zero = dfs_postorder(root->left);

			if (is_left_zero)
			{
				delete root->left;
				root->left = nullptr;
			}
		}
		else
		{
			is_left_zero = true;
		}

		if (nullptr != root->right)
		{
			is_right_zero = dfs_postorder(root->right);
			if (is_right_zero)
			{
				delete root->right;
				root->right = nullptr;
			}
		}
		else
		{
			is_right_zero = true;
		}

		// recursion
		return root->val == 0 && is_left_zero && is_right_zero;
	}

    TreeNode* pruneTree(TreeNode* root)
    {
        /**
         * One tree can be delete if and only if its root == 0 and its left and right subtree are
         * deleted.
         * Hence, we need to check left and right, and then current node. -> post order
         * bottom to up , left to right
         * nullptr can be viewes as deleted.
         * This recusive funtion return the root which might be set null.
         */
		if (nullptr == root) return nullptr;
		if (dfs_postorder(root))
		{
			delete  root; // call destrutor of the object pointed by root, release heap memory used by that object
			root = nullptr;
		}


        return root;
    }
};


class Solution {
public:
	// pass by copying pointer
	TreeNode* dfs_postorder(TreeNode* root)
	{
		if (nullptr == root)
		{
			return nullptr;
		}
		else
		{
			root->left = dfs_postorder(root->left);
			root->right = dfs_postorder(root->right);

			if (0 == root->val && nullptr == root->left && nullptr == root->right)
			{
				delete root;
				root = nullptr;

				return nullptr;
			}
			else
			{
				return root;
			}
		}
	}

    TreeNode* pruneTree(TreeNode* root)
    {
        /**
         * One tree can be delete if and only if its root == 0 and its left and right subtree are
         * deleted.
         * Hence, we need to check left and right, and then current node. -> post order
         * bottom to up , left to right
         * nullptr can be viewes as deleted.
         * This recusive funtion return the root which might be set null.
         */

		root = dfs_postorder(root);

        return root;
    }
};

