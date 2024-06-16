#include <string>
#include <queue>
#include <stack>
#include <sstream>
#include <iostream>
#include <cctype>

using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


/*
   Extended ASCII code use 8-bit numeric representation and ranges from 0 to 255;
   For 0-9, their ASCII (char or uint8) code order matches original order, i.e.
   '0' < '1' < ... < '9'. The difference of any two consecutive digit char is 1.
   For lowercase letters,
   'a' < 'b' < 'c' < ... < 'z'. The difference of any two consecutive lowercases is 1.
   For uppercase letters,
   'A' < 'B' < 'C' < ... < 'Z'. The difference of any two consecutive lowercases is 1.
*/

class Codec {
public:
    void preorder_dfs(TreeNode* root, string& data)
    {
        /* data should be initialized as a emtpy string "". */
        if (nullptr == root)
        {
            // base case null node.
            data = data +  "#" + ",";
            return;
        }
        else
        {
            data += std::to_string(root->val);
            data += ",";

            // nullptr is handled by the next call.
            preorder_dfs(root->left, data);
            preorder_dfs(root->right, data);

            return;
        }
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root)
    {
        string data = "";
        preorder_dfs(root, data);

        return data;
    }

    /**
     * How to construct the tree?
     * With the help of the null node (coded as "#"), we can image we have a binary tree.
     * We just do recusive dfs as dfs-serialization. Each call create a node (it might be null)
     */

    TreeNode* dfs_des(queue<string>& data_q)
    {
        /* You have to ensure data_q is not empty before pass it to dfs_des */
        string curr_str = data_q.front();
        data_q.pop();
        if ("#" == curr_str)
        {
            return nullptr;
        }

        TreeNode* root = new TreeNode(stoi(curr_str));

        if (!data_q.empty())
        {
            root->left = dfs_des(data_q);
        }

        if (!data_q.empty())
        {
            root->right = dfs_des(data_q);
        }


        return root;
    }

    // Decodes your encoded data (string type) to tree.
    TreeNode* deserialize(string data)
    {
        /* step 1: extract node value from data and push to queue. */
        /* queue has first-in-first-out. Hence, it maintains the visiting order of serialization*/
        queue<string> data_q;
        string curr = ""; // vector char

        for (int i = 0; i < data.size(); ++i)
        {
            /* There might be negatives */
            /* if ('-' == data[i] || isdigit(data[i]) || '#' == data[i]) */
            if (',' != data[i])
            {
                curr.push_back(data[i]);
            }
            else
            {
                /* data[i0] == ',' marks the end of one node value. */
                data_q.push(curr);
                curr = "";
            }
        }

        // Note that the tree might be empty!
        TreeNode* root = nullptr;
        if (!data_q.empty())
        {
            root = dfs_des(data_q);
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
