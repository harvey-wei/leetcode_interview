#include <vector>
#include <iostream>
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
        vector<int> prostTraversal(TreeNode* root)
		{
			std::vector<int> res;

			std::stack<TreeNode*> stack_nodes;
			TreeNode* curr = root;
			TreeNode* prev = nullptr;

			/* Left - right - root */
			while (nullptr != curr || !stack_nodes.empty())
			{
				if (nullptr != curr)
				{
					/* Go left */
					stack_nodes.push(curr);
					curr = curr->left;
				}
				else
				{
					/* Left is completely travesed. Check if parent's right is already  travesed*/
					curr = stack_nodes.top();

					if (nullptr == curr->right || prev == curr->right)
					{
						/* right subtree is travesed. */
						res.push_back(curr->val);
						stack_nodes.pop();

						prev = curr;
						curr = nullptr; // Make next iteration check curr->parent

					}
					else
					{
						/* Go to right*/
						curr = curr->right;
					}
				}

			}

			return res;
		}
};
