# include <iostream>
# include <vector>
# include <algorithm>
# include <stack>
# include <unordered_map>

using namespace std;


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

/*
����ǰ�����������������������

���Լ�������û���ظ�Ԫ��
*/

// ǰ�� ������ ���� �����

class Solution {
public:
	unordered_map<int, int> index;

	// Method 1 �ݹ� �ݹ�һ���ǴӴ��������С���� ���ܴ�С�ĵط���
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		
		int node_num = inorder.size();
		for (int i = 0; i < node_num; i++) index[inorder[i]] = i; // ���������valΪ�� λ��Ϊֵ

		return recursive(preorder, inorder, 0, node_num - 1, 0, node_num - 1);
	}

	TreeNode* recursive(vector<int>& preorder, vector<int>& inorder, int pre_left, int pre_right, int in_left, int in_right) {
		if (pre_left > pre_right) return nullptr; //�ݹ����

		int pre_root_pos = pre_left; // ǰ������е�һ�������Ǹ���� preorder_root_pos�Ǹ������ǰ�����е�λ��
		int pre_root_val = preorder[pre_root_pos]; // ������Ӧ��ֵ
		int in_root_pos = index[pre_root_val]; // �ҵ����������������е�λ��

		// ��������������඼�������� �Ҳ඼�������� ���ݴ˵ݹ齨��

		// ��������� ����new����
		TreeNode* root = new TreeNode{ pre_root_val };
		int l_tree_size = in_root_pos - in_left; // �������Ľ����
		// ��ʼ�ݹ鹹��������
		root->left = recursive(preorder, inorder, pre_left + 1, pre_left + l_tree_size, in_left, in_root_pos - 1);
		// ��ʼ�ݹ鹹��������
		root->right = recursive(preorder, inorder, pre_left + l_tree_size + 1, pre_right, in_root_pos + 1, in_right);

		return root;
	}

	// Method 2 ����
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		
		if (!preorder.size()) return nullptr;
		TreeNode* root = new TreeNode{ preorder[0] }; // ���������
		stack<TreeNode*> stk;
		stk.push(root);
		int inorder_idx = 0; // ���������ָ�� ��¼��ǰ�ߵ���Զ�������λ��
		
		for (int i = 1; i < preorder.size(); i++) {
			int preorder_val = preorder[i];
			TreeNode* node = stk.top();

			if (node->val != inorder[inorder_idx]) {
				node->left = new TreeNode{ preorder_val };
				stk.push(node->left);
			}
			else {
				// ����
				while (!stk.empty() && stk.top()->val == inorder[inorder_idx]) {
					node = stk.top();
					stk.pop();
					inorder_idx++;
				}
				node->right = new TreeNode{ preorder_val };
				stk.push(node->right);
			}
		}

		return root;
	}
};