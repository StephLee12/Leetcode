# include <iostream>
# include <vector>
# include <algorithm>
# include <stack>


using namespace std;

// �жϸö������Ƿ���BST

// Tips: һ��BST�����������Ϊ����

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	// Method 1 �ݹ�
	bool isValidBST(TreeNode* root) {
		// INT_MIN�����
		return bfs(root, LONG_MIN, LONG_MAX);
	}
	bool bfs(TreeNode* root, long long low_bound, long long upper_bound) {
		if (!root) return true;
		if (root->val >= upper_bound || root->val <= low_bound) return false;

		// ���������� ��������ֵ��Ӧ����low_bound~root->val������(������) ������ͬ��
		// �൱�ڰѽ��ָ����ض������� ����������� ��һ������BST
		return bfs(root->left, low_bound, root->val) && bfs(root->right, root->val, upper_bound);

	}

	// Method 2 �������(�ǵݹ�) Ҳ������Morris�������Ϳռ临�Ӷ�
	bool isValidBST(TreeNode* root) {
		// ����BST ��������õ�������һ��������
		stack<TreeNode*> stk;

		long long pre_num = (long long)INT_MIN - 1;

		while (!stk.empty() || root) {
			while (root) {
				stk.push(root);
				root = root->left;
			}
			root = stk.top();
			stk.pop();
			// ֻҪ�ж�������������ֵ�Ƿ����������ϵ��ok
			if (root->val <= pre_num) return false;
			pre_num = root->val;
			root = root->right;
		}
		return true;

	}
};