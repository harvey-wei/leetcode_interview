#include <iostream>
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

class BSTIterator {
private:
	std::stack<TreeNode*> stack_nodes;
	TreeNode* curr;

public:
    BSTIterator(TreeNode* root)
	{
		curr = root;
    }

    int next()
	{
		if (nullptr != curr || !stack_nodes.empty())
		{
			while(nullptr != curr)
			{
				stack_nodes.push(curr);
				curr = curr->left;
			}

			curr = stack_nodes.top();
			stack_nodes.pop();

			int val = curr->val;

			curr = curr->right;

			return val;
		}
		else
		{
			std::cout << "BST is completely traversed!" << std::endl;
			return -1;
		}

    }

    bool hasNext()
	{
		return (nullptr != curr || !stack_nodes.empty());
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
