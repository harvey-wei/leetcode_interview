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
	void dfs_predorder(TreeNode* root, std::string& res)
	{
		if (nullptr != root)
		{
			res += std::to_string(root->val) + ",";

			dfs_predorder(root->left, res);
			dfs_predorder(root->right, res);
		}
		else
		{
			res += "#,";
		}
	}

	/* Image you have a virtual complete binary tree with nullptr as child of leaf. */
	/* Be sure to define what each recuisive call do!*/
	/* Each recuisive call create node for input root*/
	/* Note that in reconstruction, we need to use reference to pointer. Otherwise,
	 */
	// Each recursive call do what? Can return what? Caryy what global info?
	void dfs_predorder_reconstruct(TreeNode*& root, std::string& data, int& start, int& end)
	{
		bool is_end = next_int_or_null(data, start, end);
		std::string val = data.substr(start, end - start);
		if ("#" != val)
		{
			root = new TreeNode(std::stoi(val));

			if (!is_end)
			{
				// The serialization ensures at least two in data
				dfs_predorder_reconstruct(root->left, data, start, end);
				dfs_predorder_reconstruct(root->right, data, start, end);
			}
		}
	}

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
		std::string res = "";
		if (nullptr == root) return res;

		dfs_predorder(root, res);

		return res;
    }

	/**
	 * (,)123,456,#,89,#, note (,) is virtual one char to match the pattern
	 * initially, start = -1,  end = -1;
	 * call next_int, start = end + 1 = 0, end -> 3, data[start, end) = 123 is int
	 * call next_int, start = end + 1 = 4, end -> 7, data[4, 7) = 456
	 * if end == data.size() -1, exhaustied
	 * start and end should be a global state variable and pass by reference.
	 * [start, end)
	 */
	bool next_int_or_null(const string& data, int& start, int& end)
	{
		// data[end] is ensured to ',' except initially
		start = end + 1;
		++end;
		while (',' != data[end])
		{
			++end;
		}

		// data[end] == ','
		// whether data is exhaustied
		return end == (data.size() - 1);
	}

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data)
	{
		if (0 == data.size()) return nullptr;

		TreeNode* root = nullptr;
		int start = -1;
		int end = -1;

		dfs_predorder_reconstruct(root, data, start, end);

		return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
