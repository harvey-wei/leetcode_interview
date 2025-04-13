#include <unordered_map>


using namespace std;
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


// https://leetcode.com/problems/path-sum-iii/description/?spm=a2c6h.13046898.publish-article.29.40b16ffaIsXWh8
class Solution {
public:
    /**
     *  SRTBOT:
     *  Subproblem: f(x) = the # of target path in tree rooted at x.
     *  Relation:  Locally brute force
     *  f(x) = f(x.left) + f(x.right) + # of target path incuing x
     *  process x first -> pre-order
     *  Topological order: pre-order
     *  Base case: x = nullptr, f(x) = 0
     *  Original Problem: f(root of tree)
     *  Time: O(n)
     *  Image each path from root as a array, path sum is the sum of subarray.
     *  prefix acc_sum -> diff of acc_sum = sum of path sum = target.
     */
    void dfs(TreeNode* root, unordered_map<long int, int>& presum2cnt,  long int presum, int& path_cnt,
			const int& target_sum)
    {
		if (nullptr != root)
		{
			// update presum
			presum += root->val;

			// targetSum = presum - s;
			// overflow use int -> use long long int
			long int s = presum - target_sum;

			if (presum2cnt.end() != presum2cnt.find(s))
			{
				path_cnt += presum2cnt[s];
			}

			// choose presum2cnt
			if (presum2cnt.end() == presum2cnt.find(presum))
			{
				presum2cnt[presum] = 1;
			}
			else
			{
				presum2cnt[presum] += 1;
			}

			// explore left and subtree
			dfs(root->left, presum2cnt, presum, path_cnt, target_sum);
			dfs(root->right, presum2cnt, presum, path_cnt, target_sum);

			// backtrack to the calling glabal status
			--presum2cnt[presum];
		}

    }

    int pathSum(TreeNode* root, int targetSum)
    {
		unordered_map<long int, int> presum2cnt;
		int path_cnt = 0;
		long int presum = 0;

		presum2cnt[0] = 1;
		dfs(root, presum2cnt, presum, path_cnt, targetSum);

        return path_cnt;

    }
};
