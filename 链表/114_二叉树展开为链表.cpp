# include <iostream>
# include <vector>
# include <algorithm>
# include <stack>

using namespace std;

/*
����������ĸ���� root �����㽫��չ��Ϊһ��������

չ����ĵ�����Ӧ��ͬ��ʹ�� TreeNode ������ right ��ָ��ָ����������һ����㣬������ָ��ʼ��Ϊ null ��

չ����ĵ�����Ӧ��������� ������� ˳����ͬ��

*/

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	// Method 1 ���� �ȵõ�������� ��ֱ���޸�ָ��(ԭ���޸�) �������������еĶ��⿪��
	void flatten(TreeNode* root) {
		if (!root) return;

		vector<TreeNode*> preorder;
		dfs(root, preorder); // �����������

		TreeNode* p = root; // ����ָ��
		p->left = nullptr; // �����������ӽ���ͷ�
		for (int i = 1; i < preorder.size(); i++) {
			// ѭ��������1��ʼ
			// ÿ��ѭ���ͷŽ������ӽ�� Ȼ������Ϊ��һ���������ӽ��
			auto node = preorder[i]; 
			node->left = nullptr;
			p->right = node;
			p = node;
		}
	}

	// dfs�������
	void dfs(TreeNode* root,vector<TreeNode*>& preorder) {
		if (root) {
			preorder.push_back(root);
			dfs(root->left, preorder);
			dfs(root->right, preorder);
		}
	}


	// Method 2 û�ж���Ŀռ俪�� ����Morris�㷨
	// ÿ���ͷŵ�ǰ������������ ���������ӵ��������� ���������ӵ������������ҽ����
	void flatten(TreeNode* root) {
		TreeNode* p = root;
		while (p) {
			if (p->left) {
				auto next = p->left;
				// �ҵ����������ܵ�������ҽ��
				auto pred = p->left;
				while (pred->right) pred = pred->right;

				// �൱�ڶϿ�p�������� Ȼ��p���������ӵ���������
				// ԭ��p�������� �ӵ��������������ҽ��
				pred->right = p->right; // ��pred���ָ��p��������
				p->left = nullptr;
				p->right = next;
			}
			p = p->right;
		}
	}
};