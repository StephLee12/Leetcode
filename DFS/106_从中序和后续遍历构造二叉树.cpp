# include <vector>
# include <iostream>
# include <algorithm>
# include <unordered_map>

using namespace std;

/*
根据一棵树的中序遍历与后序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。
*/

// 中序 左根右 后序 左右根

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};


class Solution {
public:
	unordered_map<int, int> in_idx;

	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		// Method 1 递归
		int node_num = inorder.size();
		for (int i = 0; i < node_num; i++) {
			in_idx[inorder[i]] = i;
		}
		// 后序遍历的最后一个结点 即为整棵树的根结点 和105题思路类似 
		return recursive(inorder, postorder, 0, node_num - 1, 0, node_num - 1);
	}

	TreeNode* recursive(vector<int>& inorder, vector<int>& postorder, int in_left, int in_right, int post_left, int post_right) {
		if (in_left > in_right) return nullptr;
		// 从根结点递归建树
		int post_root_pos = post_right;
		int post_root_val = postorder[post_root_pos];
		TreeNode* root = new TreeNode{post_root_val};
		int in_pos = in_idx[post_root_val]; // 根结点在中序遍历中的位置
		int r_tree_size = in_right - in_pos;

		root->left = recursive(inorder, postorder, in_left, in_pos - 1, post_left, post_right - r_tree_size - 1);;
		root->right = recursive(inorder, postorder, in_pos + 1, in_right, post_right - r_tree_size, post_right - 1);

		return root;
	}
};