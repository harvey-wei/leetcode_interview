#include <iostream>
#include <unordered_map>
using namespace std;

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
    /*
       SRTBOT: A framework to solve a problem recursively.
       Tree is recursively defined! Hence, the recursive function should have subtree as parameter.
       S: f(x, parent_cum_sum) = # of paths summing up to targetSum for tree x
       R: f(x, parent_cum_sum) = f(x.left) + f(x.right) + induced by node x.
       hash_map: cum_sum to cnt of occurrences.
       Topo: bottom-up: pre-order
       Base case:
       1. f(root, 0) = 0 if root.val = target sum otherwise 0;
       O: sum of f(leaves) directly
       Via Pre-order DFS
    */
    unordered_map<long int, int> cum_sum2cnt;
    int path_cnt = 0;
    void pathSum_helper(TreeNode* root, int& target_sum, long int cum_sum)
    {
        /* base case: null node does not contribute to path_sum */
        if (nullptr == root) return;

        cum_sum += root->val;
        if (target_sum == cum_sum)
        {
            ++path_cnt;
        }

        if (cum_sum2cnt.end() != cum_sum2cnt.find(cum_sum - target_sum))
        {
            path_cnt += cum_sum2cnt[cum_sum - target_sum];
        }

        if (cum_sum2cnt.end() != cum_sum2cnt.find(cum_sum))
        {
            cum_sum2cnt[cum_sum] += 1;
        }
        else
        {
            cum_sum2cnt[cum_sum] = 1;
        }

        pathSum_helper(root->left, target_sum, cum_sum);
        // We need cancel the effect of recursive call to cum_sum2cnt
        // This is why we need unchoose before return (backtrack) to the caller.
        pathSum_helper(root->right, target_sum, cum_sum);

        /* Don't forget to unchoose! */
        --cum_sum2cnt[cum_sum];
    }

    int pathSum(TreeNode* root, int targetSum)
    {
        pathSum_helper(root, targetSum, 0);
        return path_cnt;
    }
};

int main()
{
    return 0;
}
