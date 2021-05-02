# include <vector>
# include <stack>
# include <iostream>
# include <algorithm>

using namespace std;

/*
�������ö������ĸ��ڵ� p �� q ����дһ���������������������Ƿ���ͬ��

����������ڽṹ����ͬ�����ҽڵ������ͬ��ֵ������Ϊ��������ͬ��
*/

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	// Method 1 �ݹ�
	bool isSameTree(TreeNode* p, TreeNode* q) {
		// �����ٽ����
		if (!p && !q) return true; // ��������Ϊ��
		if ((p && !q) || (!p && q)) return false; // ��������ֻ��һ��Ϊ��
		if (p->val != q->val) return false; // ������ֵ�����

		// �ڸ�����ֵ��ȵ������� �ж����������Ƿ���ͬ
		return recursive(p->left, q->left) && recursive(p->right, q->right);
	}

	bool recursive(TreeNode* p,TreeNode* q) {
		if (!p && !q) return true; // ��ǰ��������Ϊ��
		if ((p && !q) || (!p && q)) return false; // ��������ֻ��һ�ÿ�

		if (p->val == q->val) {
			// �����ǰ�����ֵ��� �����ݹ�
			return recursive(p->left, q->left) && recursive(p->right, q->right);
		}
		else return false; // ��ǰ������ֵ����� ֱ�ӷ���false
	}
};