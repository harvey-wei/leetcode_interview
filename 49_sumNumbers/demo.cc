#include <stack>
/**
 * Definition for a binary tree node.
 */


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
	void dfs_preorder(TreeNode* root, int path_sum, int& total_sum)
	{
		// update path_sum
		path_sum = 10 * path_sum + root->val;

		// base case
		if (nullptr == root->left && nullptr == root->right)
		{
			total_sum += path_sum;
		}
		else
		{
			if (nullptr != root->left) dfs_preorder(root->left, path_sum, total_sum);
			if (nullptr != root->right) dfs_preorder(root->right, path_sum, total_sum);
		}
	}

    int sumNumbers(TreeNode* root)
    {
		int total_sum = 0;
		if (nullptr == root) return total_sum;

		dfs_preorder(root, 0, total_sum);
		return total_sum;
    }
};
