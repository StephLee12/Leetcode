# include <vector>
# include <algorithm>
# include <iostream>
# include <queue>
# include <stack>

using namespace std;

// ����һ����������������ڵ�ֵ�Ե����ϵĲ�������� ��
// ������Ҷ�ӽڵ����ڲ㵽���ڵ����ڵĲ㣬���������ұ�����


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> res; // ���ؽ��.

		if (!root) return res; // �ٽ����

		queue<TreeNode*> q; // ������� ����
		q.push(root); // �������ĸ���������

		while (!q.empty()) {

			vector<int> tmp; // �洢��ǰ��Ľ��ֵ
			int now_cnt = q.size();
			// ������ǰ����ֵ
			for (int i = 1; i <= now_cnt; i++) {
				root = q.front();
				q.pop();
				tmp.push_back(root->val);

				// ��һ�������
				if (root->left) q.push(root->left);
				if (root->right) q.push(root->right);
			}
			res.push_back(tmp);
		}

		// ��102��һ�� ��һ��reverse
		reverse(res.begin(), res.end());
		return res;
	}
};