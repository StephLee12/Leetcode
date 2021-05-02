# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;


/*
给定一个二叉树，找出其最大深度。

二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
*/

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	int maxDepth(TreeNode* root) {
		// Method 1 递归 dfs
		if (!root) return 0;

		return max(recursive(root->left,1), recursive(root->right,1));
	}

	int recursive(TreeNode* root, int depth) {
		if (!root) return depth;
		return max(recursive(root->left, depth + 1), recursive(root->right, depth + 1));
	}
};