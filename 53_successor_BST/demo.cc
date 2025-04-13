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

		TreeNode* curr = root;
		TreeNode* result = nullptr; // Smallerst one larger than p->val

		/* result shoulbe in the left most of right subtree of p->val */
		/* If curr->val <= p->val, go right.*/
		/* If curr > p, go left to find Smallerst one, update result = curr*/

		while (nullptr != curr)
		{
			if (curr->val <= p->val)
			{
				curr = curr->right;
			}
			else
			{
				result = curr;
				curr = curr->left;
			}
		}

		return result;

    }
};
