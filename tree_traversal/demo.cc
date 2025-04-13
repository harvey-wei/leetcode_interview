#include <vector>
#include <stack>
#include <queue>


using namespace std;
/**
 * Definition for a binary tree node.
 */

 struct TreeNode
{
     int val;
     TreeNode *left;
     TreeNode *right;

	 // Constructor Overloading
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


/**
 * For DFS, time complexity: O(N) (push and pop is both O(1). N pushes and pops).
 *   		space complexity: O(h)=O(logN) if binary tree is balanced.
 * For BFS, Time complexity: O(N)
 *           Space complexity: O(N) = O((N+1)/2) if binary tree is balanced.
 * If tree is not balanced just a linkedin list.
 * DFS has space complexity O(N) while BFS has space complexity as O(1)!
 * BFS is slightly inferior to DFS in terms of space complexity if binary tree is balanced.
 * Image leaf of tree has both left and right child as nullptr. -> recursive structrue.
 * For tree-related problem, the key is to determine what kind of traversal method works!
 */
class Solution
{
public:

    vector<vector<int>> levelOrder(TreeNode* root)
	{
		vector<vector<int>> res;

		if (nullptr == root) return res;

		TreeNode* curr = nullptr;
		queue<TreeNode*> node_queue;

		node_queue.push(root);
		/* res.resize(1); // Now res = [[]] (1 empty inner vector) */
		res.push_back({});
		int curr_level_cnt = 1;  // number of current level nodes in the queue.
		int next_level_cnt = 0;  // number of the next level nodes in the queue.

		/* Max of (curr_level_cnt + next_level_cnt) = space complexity. */
		/* Max sum is number of nodes in the last level if */

		while (!node_queue.empty())
		{
			 curr = node_queue.front(); // access oldest element but not remove
			 node_queue.pop();

			 res[res.size() - 1].push_back(curr->val);

			 --curr_level_cnt;

			 if (nullptr != curr->left)
			 {
				 node_queue.push(curr->left);
				 ++next_level_cnt;
			 }

			 if (nullptr != curr->right)
			 {
				 node_queue.push(curr->right);
				 ++next_level_cnt;
			 }

			 if (0 == curr_level_cnt)
			 {
				 // Current level is done.
				 curr_level_cnt = next_level_cnt;
				 next_level_cnt = 0;

				 // Create a new vector<int> for new level
				 if (0 != curr_level_cnt)
				 {
					res.push_back({});
				 }
			 }
		}

		return res;

    }

	/**
	 * base case root == nullptr, backtrack
	 */
	void dfs_postorder(TreeNode* root, vector<int>& res)
	{
		if (nullptr != root)
		{
			dfs_postorder(root->left, res);
			dfs_postorder(root->right, res);

			res.push_back(root->val);
		}
	}

    vector<int> postorderTraversal(TreeNode* root)
	{
		vector<int> res;

		dfs_postorder(root, res);

		return res;
    }

	void dfs_preorder(TreeNode* root, vector<int>& res)
	{
		if (nullptr != root)
		{
			res.push_back(root->val);
			dfs_preorder(root->left, res);
			dfs_preorder(root->right, res);
		}
	}

    vector<int> preorderTraversal(TreeNode* root)
	{
		vector<int> res;
		dfs_preorder(root, res);
		return res;
    }

	void dfs_inorder(TreeNode* root, vector<int>& res)
	{
		if (nullptr != root)
		{
			dfs_inorder(root->left, res);
			res.push_back(root->val);
			dfs_inorder(root->right, res);
		}
	}

	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> res;
		dfs_inorder(root, res);

		return res;
    }

};


class TreeTraversal
{
    public:
        /* The general pattern should match the first iteration of the tree traversal! */
        /* Hence, you can generilize from the first iteration. */
		/* Root -> left (Root-.left -> Right) -> Right (Root-> left-> right) */
		/* After visisting root, we need to push right and then left. */
		/* stack is last in first out. So, left is last in will first out.*/
		/**
		 * Time Complexity: O(n)
		 * Space Complexity: O(h) with h as the height of tree h = logn if binary tree is balanced.
		 */
        vector<int> preorderTraversal(TreeNode* root)
        {
			vector<int> res;
			if (nullptr == root)  return res;

			stack<TreeNode*> node_stack;
			node_stack.push(root);
			TreeNode* curr = nullptr;

			while (!node_stack.empty())
			{
				curr = node_stack.top(); // access but not remove
				node_stack.pop(); // remove

				res.push_back(curr->val);

				// Check if right is null
				if (nullptr != curr->right)
				{
					node_stack.push(curr->right);
				}

				// So, left will be poped out ealier than right
				// Stack is LIFO
				if (nullptr != curr->left)
				{
					node_stack.push(curr->left);
				}
			}

			return res;
        }


		/* The leaf of tree is a tree with both left and right node is null!*/
		/* Work on an instance of this problem using a pencil and a piece of paper. */
        vector<int> inorderTraversal_v1(TreeNode* root)
        {
			vector<int> res;

			/* Edge case: root == nullptr. */
			if (nullptr == root) return res;

			/* L -> root -> R */
			TreeNode* curr = root;
			stack<TreeNode*> stack_nodes;

			while (nullptr != curr || !stack_nodes.empty())
			{
				/* Go left until reach NULL left */
				while (nullptr != curr)
				{
					stack_nodes.push(curr);
					curr = curr->left;
				}

				// pop up parent node, empty?
				curr = stack_nodes.top();
				stack_nodes.pop();
				res.push_back(curr->val);

				// Traverse the right subtree
				// right == nullptr means subtree rooted at curr is completely traversed.
				curr = curr->right;
			}

			return res;
        }

		/* The leaf of tree is a tree with both left and right node is null!*/
		/* Work on an instance of this problem using a pencil and a piece of paper. */
        vector<int> inorderTraversal(TreeNode* root)
        {
			vector<int> res;

			/* Edge case: root == nullptr. */
			if (nullptr == root) return res;

			/* L -> root -> R */
			TreeNode* curr = root;
			stack<TreeNode*> stack_nodes;

			/* Inner loop conditioin is one of outer conditioins. */
			while (nullptr != curr || !stack_nodes.empty())
			{
				/* Go left until reach NULL left */
				if (nullptr != curr)
				{
					stack_nodes.push(curr);
					curr = curr->left;
				}
				else
				{
					// left subtree is exhuasted.
					// pop up parent node, empty?
					curr = stack_nodes.top();
					stack_nodes.pop();
					res.push_back(curr->val);

					// Traverse the right subtree
					// right == nullptr means subtree rooted at curr is completely traversed.
					curr = curr->right;
				}
			}

			return res;
        }


        vector<int> postorderTraversal(TreeNode* root)
        {
			vector<int> res;

			if (nullptr == root) return res;

			TreeNode* curr = root;
			TreeNode* prev_vsisted = nullptr; // no previous visited.
			stack<TreeNode*> stack_nodes;

			// L->R->root
			while (nullptr != curr || !stack_nodes.empty())
			{
				// Go left until reaching null left node
				if  (nullptr != curr)
				{
					stack_nodes.push(curr);
					curr = curr->left;
				}
				else
				{
					// curr turns into null left
					curr = stack_nodes.top();

					if (curr->right == nullptr || curr->right == prev_vsisted)
					{
						// Right subtree is already completely traversed
						res.push_back(curr->val);
						stack_nodes.pop();

						prev_vsisted = curr;

						// triger nex top by setting curr to nullptr
						curr = nullptr;
					}
					else
					{
						curr = curr->right;
					}
				}

			}

            return res;
        }
};


























/* https://www.shubo.io/iterative-binary-tree-traversal/ */
/* https://www.enjoyalgorithms.com/blog/iterative-binary-tree-traversals-using-stack */
class SolutionInIter {
public:
    vector<int> inorderTraversal(TreeNode* root)
    {
        if (nullptr == root) return {};

        vector<int> res;
        /* Order of push to result: L -> Curr_Root -> R. */
        /* We need a pointer to memorize the Curr_Root. */
        // Note the difference between going order and pop order.

        stack<TreeNode*> stack_nodes;
        TreeNode* curr = root;
        while (nullptr != curr || !stack_nodes.empty())
        {
            /* We need further check the case */
            if (nullptr != curr)
            {
                /* Push to stack before go left first */
                stack_nodes.push(curr) ;
                curr = curr->left;
            }
            else
            {
                /* Left or Right is traversed */
                TreeNode* parent = stack_nodes.top();
                stack_nodes.pop();
                res.push_back(parent->val);

                /* Go to right */
                curr = parent->right;
            }
        }

        return res;
    }
};


class SolutionPreRecur {
public:
    void preorderTraversalRecur(TreeNode* root, vector<int>& res)
    {
        if (nullptr == root) return;

        res.push_back(root->val);
        preorderTraversalRecur(root->left, res);
        preorderTraversalRecur(root->right, res);

        /* No extra operations after the final recusion. */
        /* Hence, this recusion call is tail-recursive. */

        return;
    }

    vector<int> preorderTraversal(TreeNode* root)
    {
        vector<int> res;
        preorderTraversalRecur(root, res);

        return res;
    }
};


class SolutionPreorderIter {
public:
    vector<int> preorderTraversal(TreeNode* root)
    {
        if (nullptr == root)
        {
            return {};
        }

        vector<int> res;

        stack<TreeNode*> stack_node;
        stack_node.push(root);
        TreeNode* top;

        while (!stack_node.empty())
        {
            /***** repeated *****/
            top = stack_node.top();
            stack_node.pop();

            res.push_back(top->val);
            /***** repeated *****/

            /* stack is FILO, we need pop from stack top-bottom, left-right order to result*/
            /* We need push right first to stack. */
            /* Then right is popped lastly. */
            // We must push right first ->right is visted last
            if (nullptr != top->right)
            {
                stack_node.push(top->right);
            }

            // Left will be poped ealier than right.
            if (nullptr != top->left)
            {
                stack_node.push(top->left);
            }
        }

        return res;
    }
};
