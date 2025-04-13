/**
 * Definition for a binary tree node.
 */

#include <stack>

struct TreeNode
{
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p)
	{
		if (nullptr == root) return nullptr;

		TreeNode* curr = root; // we hope the curr is the smallest one who is larger then p->val
		TreeNode* result= nullptr;

		// Find right subtree containing smallest one larger than p->val
		while (nullptr != curr)
		{
			if (curr->val > p->val)
			{
				// curr is in the righ subtree, i.e. all nodes in tree rooted at curr > p-val
				result = curr; // possible answer
				curr = curr->left; // Find posible smaller one > p->val
			}
			else
			{
				// if curr->val <=  p->val, go right until find one or nullptr
				curr = curr->right;
			}

		}


		return result;

    }
};
