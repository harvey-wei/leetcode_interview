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
	void dfs_inorder(TreeNode* root, long int& cum_sum)
	{
		if (nullptr != root)
		{
			dfs_inorder(root->right, cum_sum);
			int val = root->val;
			root->val += cum_sum;
			cum_sum += val;
			dfs_inorder(root->left, cum_sum);
		}
	}

    TreeNode* convertBST(TreeNode* root)
	{
		long int cum_sum = 0;
		dfs_inorder(root, cum_sum);
		return root;
    }
};


class SolutionIter {
public:
    TreeNode* convertBST(TreeNode* root)
	{
		TreeNode* curr = root;
		std::stack<TreeNode*> stack_nodes;
		long int cum_sum = 0l;

		// This is a reverse order traversal i.e. decreasing order.
		while (nullptr != curr || !stack_nodes.empty())
		{
			// Go right until
			while (nullptr != curr)
			{
				stack_nodes.push(curr);
				curr = curr->right;
			}


			curr = stack_nodes.top();
			stack_nodes.pop();
			int curr_val = curr->val;
			curr->val += cum_sum;
			cum_sum += curr_val;

			curr = curr->left;
		}

		return root;
    }
};
