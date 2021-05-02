# include <vector>
# include <algorithm>
# include <iostream>

using namespace std;

/*
·�� ������Ϊһ������������ڵ�������ظ��ڵ�-�ӽڵ����ӣ��ﵽ����ڵ�����С�

ͬһ���ڵ���һ��·�������� �������һ�� ����·�� ���ٰ���һ�� �ڵ㣬�Ҳ�һ���������ڵ㡣

·���� ��·���и��ڵ�ֵ���ܺ͡�

����һ���������ĸ��ڵ� root �������� ���·���� ��

*/

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	int max_path = INT_MIN; // ����ȫ�ֱ��� ��¼���·����

	int maxPathSum(TreeNode* root) {
		// Method 1 dfs�ݹ�
		dfs(root);
		return max_path;
	}
	int dfs(TreeNode* root) {
		if (root == nullptr) return 0;

		// ���������·���Ĺ��� ������׳���С��0 ����ѡ���������·��
		// ��l_gain=0
		int l_gain = max(dfs(root->left), 0);
		// ������ͬ��
		int r_gain = max(dfs(root->right), 0);
		// ���·���� ȡ���ڵ�ǰ����ֵ�����������Ĺ���ֵ
		int new_path = root->val + l_gain + r_gain;
		max_path = max(max_path, new_path);

		// ��������ֵ���Ըý��Ϊ�������·��
		return root->val + max(l_gain, r_gain);
	}
};