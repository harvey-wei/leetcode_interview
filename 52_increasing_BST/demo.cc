/**
 * Definition for a binary tree node.
 */
#include <stack>

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

    TreeNode* increasingBST(TreeNode* root)
	{
		TreeNode* prev = nullptr;
		TreeNode* new_root = nullptr;
		TreeNode* curr = root;

		std::stack<TreeNode*> nodes_stack;

		while (nullptr != curr || !nodes_stack.empty())
		{
			// Go left until curr == null
			while (nullptr != curr)
			{
				nodes_stack.push(curr);
				curr = curr->left;
			}

			curr = nodes_stack.top();
			nodes_stack.pop();

			if (nullptr == prev)
			{
				prev = curr;
				new_root = curr;
			}
			else
			{
				prev->right = curr;
				prev = curr;
			}

			curr->left = nullptr;
			curr = curr->right;
		}

		return new_root;
    }
};



class Solution_
{
public:
	void dfs_inorder(TreeNode* root, TreeNode*& prev, TreeNode*& new_root)
	{

		if (nullptr != root)
		{
			dfs_inorder(root->left, prev, new_root);

			if (nullptr != prev)
			{
				prev->right = root;
                prev = root;
			}
			else
			{
				prev = root;
				new_root = root;
                prev = root;
			}

			dfs_inorder(root->right, prev, new_root);

			root->left = nullptr;

		}
	}

    TreeNode* increasingBST(TreeNode* root)
	{
		TreeNode* prev = nullptr;
		TreeNode* new_root = nullptr;
		dfs_inorder(root, prev, new_root);

        return new_root;
    }
};
