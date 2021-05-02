# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

// �ж϶������Ƿ���Գ�


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	bool isSymmetric(TreeNode* root) {
		if (!root) return false; // ���Ϊ����

		return recursive(root->left, root->right);
	}

	bool recursive(TreeNode* left, TreeNode* right) {
		if (!left && !right) return true; // ��Ϊ�� ����true
		if ((!left && right) || (left && !right)) return false; // һ���� һ������ ����false

		if (left->val == right->val) {
			// �����ж�
			return recursive(left->left, right->right) && recursive(left->right, right->left);
		}
		else return false;
	}
};