#include <string>
#include <queue>
#include <stack>
#include <sstream>
#include <iostream>

using namespace std;

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec_itera {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        /* Traverse by BFS or DFS */
        string data;

        TreeNode* curr = root;
        queue<TreeNode*> tree_queue;

        if (curr != nullptr)
        {
            tree_queue.push(std::move(curr));
        }

        while (!tree_queue.empty())
        {
            curr = tree_queue.front();
            tree_queue.pop();

            if (nullptr != curr)
            {
                /* Append curr->val to data */
                data = data + std::to_string(curr->val) + ",";
                /* Different from normal BFS, we also push nullptr to ensure we can reconstruct. */
                tree_queue.push(curr->left);
                tree_queue.push(curr->right);
            }
            else
            {
                data += "#,";
            }
        }

        return data;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;

        vector<string> node_val; // nullptr is "#"
        std::stringstream data_stream;
        data_stream.str(data);
        std::string curr_val_str;

        while (getline(data_stream, curr_val_str, ','))
        {
            node_val.push_back(std::move(curr_val_str));
        }

        int curr_idx = 0;
        TreeNode* root = new TreeNode(std::stoi(node_val[curr_idx]));
        queue<TreeNode*> tree_q;
        tree_q.push(root);
        TreeNode* curr;

        while (!tree_q.empty())
        {
            curr = tree_q.front();
            tree_q.pop();

            string left = node_val[++curr_idx];
            string right = node_val[++curr_idx];

            if (left != "#")
            {
                curr->left = new TreeNode(std::stoi(left));
                tree_q.push(curr->left);
            }
            else
            {
                curr->left = nullptr;
            }

            if(right != "#")
            {
                curr->right = new TreeNode(std::stoi(right));
                tree_q.push(curr->right);
            }
            else
            {
                curr->right = nullptr;
            }
        }

        return root;
    }
};


class Codec {
public:
    void preorder_dfs(TreeNode* root, string& data)
    {
        if (nullptr == root)
        {
            data =  data + "#" + ",";
        }
        else
        {
            data = data + std::to_string(root->val) + ",";

            preorder_dfs(root->left, data);
            preorder_dfs(root->right, data);
        }

        return;
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root)
    {
        string data;
        preorder_dfs(root, data);

        return data;

    }

    TreeNode* preorder_dfs_des(queue<string>& data)
    {
        string curr_val_str = data.front();
        data.pop();

        if ("#" == curr_val_str)
        {
            return nullptr;
        }

        TreeNode* root = new TreeNode(std::stoi(curr_val_str));
        if (!data.empty())
        {
            root->left = preorder_dfs_des(data);
        }
        if (!data.empty())
        {
            root->right = preorder_dfs_des(data);
        }

        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
    {
        queue<string> node_val; // nullptr is "#"
        string curr;
        for (unsigned int i = 0; i < data.size(); ++i)
        {
            /*
               Extended ASCII code use 8-bit numeric representation and ranges from 0 to 255;
               For 0-9, their ASCII (char or uint8) code order matches original order, i.e.
               '0' < '1' < ... < '9'. The difference of any two consecutive digit char is 1.
               For lowercase letters,
               'a' < 'b' < 'c' < ... < 'z'. The difference of any two consecutive lowercases is 1.
               For uppercase letters,
               'A' < 'B' < 'C' < ... < 'Z'. The difference of any two consecutive lowercases is 1.
            */
            if ((data[i] >= '0' && data[i] <= '9') || data[i] == '#')
            {
                curr.push_back(data[i]);
            }
            else
            {
                /* comma */
                node_val.push(std::move(curr));
                curr = "";
            }
        }
        data = "";

        TreeNode* root = nullptr;
        if (!node_val.empty())
        {
            root = preorder_dfs_des(node_val);
        }

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
