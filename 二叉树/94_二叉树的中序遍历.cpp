# include <iostream>
# include <algorithm>
# include <vector>
# include <stack>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */


// ������������� ������
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};


class Solution {
public:
	// Method 1 �ݹ�
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		if (!root) return res;
		recursive(root, res);
		return res;
	}

	void recursive(TreeNode* root, vector<int>& res) {
		if (!root) return;
		recursive(root->left, res);
		res.push_back(root->val);
		recursive(root->right, res);
	}

	// Method 2 �ǵݹ�(����)
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		if (!root) return res; // ������Ϊ��

		stack<TreeNode*> st;
		// ע�������ѭ����������
		// ��root==nullptr(root=root->right����)��ջ��Ϊ��ʱ Ҫ����ѭ��
		// ��root!=nullptr��ջΪ��ʱ Ҫ����ѭ��
		while (root || !st.empty()) {
			// ��������
			while (root) {
				st.push(root);
				root = root->left;
			}
			// ��ȡջ�����
			root = st.top();
			st.pop();
			res.push_back(root->val);
			// ����������� ��Ϊ����
			// ��root->rightΪnullʱ root����ΪҶ��㱻����(����������)
			// ��root->right��Ϊ��ʱ root����Ϊ����㱻����
			root = root->right;
		}
		
	}

	// Method 3 Morris�������
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		if (!root) return res; // ������Ϊ��

		// �ռ临�ӶȽ�Ϊ����
		// ����˼��:�õ�ǰ�������� ���������һ���ҽ��pred ��¼��ǰ�����
		// �Ӷ��ﵽ��ʹ��ջ�һ��ݵ�Ч�� �����˼��
		TreeNode* pred = nullptr;
		while (root) {
			if (root->left) {
				// Ѱ��pred
				pred = root->left;
				// ѭ���ĵڶ������� ����Ϊpred������һ��ʼ����root��
				// �����ڻ��ݵ�ʱ������������������ �ᵼ����ѭ��
				while (pred->right && pred->right != root) {
					pred = pred->right;
				}
				if (!pred->right) {
					// pred���û��root�� һ���Ǹ�Ҷ�ӽ��
					pred->right = root; // ָ��root
					root = root->left; // ��������root��������
				}
				else {
					// ˵��pred���ҽ��Ϊroot
					// ˵��root���������Ѿ�������
					res.push_back(root->val);
					// ����pred ��Ϊ�˻ָ����Ľṹ ��Ϊ����link����֮����������
					pred->right = nullptr; 
					root = root->right; // ����root ����������
				}
			}	
			else {
				// ��rootû������
				res.push_back(root->val);
				// ���ﲻ�ÿ��� ����û�����굫��root==nullptr�����
				// ��Ϊpred���ҽ��Ϊroot
				root = root->right;
			}
		}
			
		return res;
	}
};