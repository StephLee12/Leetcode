# include <vector>
# include <iostream>
# include <algorithm>
# include <unordered_map>

using namespace std;

/*
����һ��������������������������������

ע��:
����Լ�������û���ظ���Ԫ�ء�
*/

// ���� ����� ���� ���Ҹ�

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};


class Solution {
public:
	unordered_map<int, int> in_idx;

	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		// Method 1 �ݹ�
		int node_num = inorder.size();
		for (int i = 0; i < node_num; i++) {
			in_idx[inorder[i]] = i;
		}
		// ������������һ����� ��Ϊ�������ĸ���� ��105��˼·���� 
		return recursive(inorder, postorder, 0, node_num - 1, 0, node_num - 1);
	}

	TreeNode* recursive(vector<int>& inorder, vector<int>& postorder, int in_left, int in_right, int post_left, int post_right) {
		if (in_left > in_right) return nullptr;
		// �Ӹ����ݹ齨��
		int post_root_pos = post_right;
		int post_root_val = postorder[post_root_pos];
		TreeNode* root = new TreeNode{post_root_val};
		int in_pos = in_idx[post_root_val]; // ���������������е�λ��
		int r_tree_size = in_right - in_pos;

		root->left = recursive(inorder, postorder, in_left, in_pos - 1, post_left, post_right - r_tree_size - 1);;
		root->right = recursive(inorder, postorder, in_pos + 1, in_right, post_right - r_tree_size, post_right - 1);

		return root;
	}
};