#include <iostream>
#include <stack>


struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution
{
	private:
		std::stack<TreeNode*> next_stack; // next means larger
		std::stack<TreeNode*> prev_stack; // prev means smaller
		TreeNode* curr_next;
		TreeNode* curr_prev;

	public:

		TreeNode* next()
		{
			TreeNode* next_node = nullptr;
			if (nullptr != curr_next || !next_stack.empty())
			{
				while (nullptr != curr_next)
				{
					next_stack.push(curr_next);
					curr_next = curr_next->left;
				}

				curr_next = next_stack.top();
				next_stack.pop();
				next_node = curr_next;

				// update curr_next
				curr_next = curr_next->right;
			}

			return next_node;
		}

		TreeNode* prev()
		{
			TreeNode* prev_node = nullptr;
			if (nullptr != curr_prev || !prev_stack.empty())
			{
				while (nullptr != curr_prev)
				{
					prev_stack.push(curr_prev);
					curr_prev = curr_prev->right;
				}

				curr_prev = prev_stack.top();
				prev_stack.pop();
				prev_node = curr_prev;

				// update curr_prev
				curr_prev = curr_prev->left;
			}

			return prev_node;
		}

		/**
		 * prev() and next() has O(h = longN) in space complexity, respectively.
		 * But they have O(N) in time complexity.
		 */
		bool findTarget(TreeNode* root, int k)
		{
			curr_next = root;
			curr_prev = root;
			TreeNode* next_ptr = next();
			TreeNode* prev_ptr = prev();
			long int curr_sum = 0;

			while (next_ptr != prev_ptr)
			{
				curr_sum = static_cast<long int>(next_ptr->val + prev_ptr->val);
				if (curr_sum == k)
				{
					return true;
				}
				else if (curr_sum < k)
				{
					next_ptr = next();
				}
				else
				{
					prev_ptr = prev();
				}
			}

			return false;
		}
};
