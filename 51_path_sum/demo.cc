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


class Solution {
public:
    Solution()
    {
        path_cnt = 0;
    }
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
    void dfs(TreeNode* root, unordered_map<long int, int>& acc_sum2cnt,  long int acc_sum,
            const int& target_sum)
    {
        if (nullptr == root) return;

        // choose the root
        acc_sum += root->val;
        long int s = acc_sum - target_sum;

        if (acc_sum2cnt.end() != acc_sum2cnt.find(s))
        {
            path_cnt += acc_sum2cnt[s];
        }

        // update acc_sum2cnt, choose - explore - un-cho0se
        if (acc_sum2cnt.end() == acc_sum2cnt.find(acc_sum))
        {
            acc_sum2cnt[acc_sum] = 1;
        }
        else
        {
            ++acc_sum2cnt[acc_sum];
        }

        // pass acc_sum by value explore
        // note that both acc_sum and acc_sum2cnt are state.
        // They need to follow choose explore unchoose
        dfs(root->left, acc_sum2cnt, acc_sum, target_sum);
        dfs(root->right, acc_sum2cnt, acc_sum, target_sum);

        // unchoose to back-track to the calling root.
        --acc_sum2cnt[acc_sum];
    }

    int pathSum(TreeNode* root, int targetSum)
    {
        unordered_map<long int, int> acc_sum2cnt;
        // a dummy root with a value of 0.
        acc_sum2cnt[0] = 1; // Don't forget the path from root;

        dfs(root, acc_sum2cnt, 0, targetSum);

        return path_cnt;

    }

private:
    int path_cnt;
};
