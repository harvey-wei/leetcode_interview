#include <climits>
#include <limits>
#include <algorithm>


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

	long int dfs_post_order(TreeNode* root, long int& max_sum)
	{
		if (nullptr == root)
		{
			// base case
			return 0;
		}
		else
		{
			// subproblem 1: max gain from one of subtrees
			long int left_max_sum = std::max(dfs_post_order(root->left, max_sum), 0l);
			long int right_max_sum = std::max(dfs_post_order(root->right, max_sum), 0l);

			long int local_max_sum = std::max(left_max_sum, right_max_sum);

			// subproblem 2: max_sum of path starting at root or with root in between

			max_sum = std::max(max_sum, (long int)(root->val) + left_max_sum + right_max_sum);

			return local_max_sum + root->val;
		}
	}

    int maxPathSum(TreeNode* root) {
		long int max_sum = std::numeric_limits<long int>::min();

		dfs_post_order(root, max_sum);

        return max_sum;
    }
};
