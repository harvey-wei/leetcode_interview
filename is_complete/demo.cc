#include <iostream>
#include <vector>
#include <queue>
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

class Solution
{
	public:
		bool isCompleteTree(TreeNode* root)
		{
			/* Root is ensured not to be nullptr */
			if (nullptr == root->left && nullptr == root->right) return true;

			std::queue<TreeNode*> node_queue;

			TreeNode* curr = nullptr;
			node_queue.push(root);

			bool find_first_null = false;

			while (!node_queue.empty())
			{
				curr = node_queue.front();
				node_queue.pop();

				if (find_first_null && nullptr != curr)
				{
					/* Not complete*/
					return false;
				}

				if (!find_first_null && nullptr == curr)
				{
					find_first_null = true;
				}

				if (nullptr != curr)
				{
					/* We treat nulltpr as node as well*/
					/* Treat nullptr as a  node to represent a binary completely tree as an array*/
					/* Binary Completeness defines the order !*/
					node_queue.push(curr->left);
					node_queue.push(curr->right);
				}
			}

			return true;
		}
};
