# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;


/*
����һ�����������ҳ��������ȡ�

�����������Ϊ���ڵ㵽��ԶҶ�ӽڵ���·���ϵĽڵ�����
*/

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	int maxDepth(TreeNode* root) {
		// Method 1 �ݹ� dfs
		if (!root) return 0;

		return max(recursive(root->left,1), recursive(root->right,1));
	}

	int recursive(TreeNode* root, int depth) {
		if (!root) return depth;
		return max(recursive(root->left, depth + 1), recursive(root->right, depth + 1));
	}
};