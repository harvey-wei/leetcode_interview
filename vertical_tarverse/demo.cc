#include <vector>
#include <stack>
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
private:
    class Triplet
    {
        public:
            TreeNode* node;
            int row;
            int col;
            Triplet(TreeNode* _node = nullptr, int _row = 0, int _col = 0)
                : node(_node), row(_row), col(_col)
            {}
    };

public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        /* Traverse the binary tree by post-order. */
        /* stack<TreeNode*> node_statck; */
        stack<Triplet> node_statck;
        std::vector<Triplet> triplets;
        Triplet curr_triplet(root, 0, 0);
        Triplet prev_triplet;

        /* L -> R -> N */
        while (curr_triplet.node != nullptr || !node_statck.empty())
        {
            while (curr_triplet.node != nullptr)
            {
                node_statck.push(std::move(curr_triplet));
                curr_triplet = Triplet(curr_triplet.node->left, curr_triplet.row + 1,
                        curr_triplet.col - 1);
            }

            curr_triplet = node_statck.top();

            if (nullptr == curr_triplet.node->right
                    || curr_triplet.node->right == prev_triplet.node)
            {
                /* Right sub-tree is completely traversed. */
                node_statck.pop();
                triplets.push_back(std::move(curr_triplet));
                prev_triplet = curr_triplet;
                curr_triplet = Triplet(); // Make node_statck pop again.
            }
            else
            {
                curr_triplet = Triplet(curr_triplet.node->right, curr_triplet.row + 1,
                        curr_triplet.col + 1);
            }
        }

        /* in-place sort */
        std::sort(triplets.begin(), triplets.end(), [](const Triplet& lhs, const Triplet& rhs)
                {
                    if (lhs.col < rhs.col)
                    {
                        return true;
                    }
                    else if (lhs.col == rhs.col)
                    {
                        if (lhs.row < rhs.row)
                        {
                            return true;
                        }
                        else if (lhs.row == rhs.row)
                        {
                            return lhs.node->val <= rhs.node->val;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }

                });

        int min_col = triplets[0].col;
        int max_col = triplets[triplets.size() - 1].col;

        vector<vector<int>> res(max_col - min_col + 1, vector<int>());
        for (uint32_t i = 0; i < triplets.size(); ++i)
        {
            res[triplets[i].col - min_col].push_back(std::move(triplets[i].node->val));
        }

        return res;
    }
};

int main()
{
    return 0;
}
