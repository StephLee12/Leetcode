# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

// 判断二叉树是否镜像对称


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	bool isSymmetric(TreeNode* root) {
		if (!root) return false; // 如果为空树

		return recursive(root->left, root->right);
	}

	bool recursive(TreeNode* left, TreeNode* right) {
		if (!left && !right) return true; // 均为空 返回true
		if ((!left && right) || (left && !right)) return false; // 一个空 一个不空 返回false

		if (left->val == right->val) {
			// 镜像判断
			return recursive(left->left, right->right) && recursive(left->right, right->left);
		}
		else return false;
	}
};