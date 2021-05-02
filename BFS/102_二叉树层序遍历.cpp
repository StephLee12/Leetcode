# include <vector>
# include <algorithm>
# include <iostream>
# include <queue>

using namespace std;

// ���ز�������õ��Ľ��ֵ


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {

		vector<vector<int>> res; // ���ؽ��
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
		return res;
	}
};

int main() {
	TreeNode* root = new TreeNode{ 3,new TreeNode{9},new TreeNode{20,new TreeNode{15},new TreeNode{7}} };
	Solution obj;
	vector<vector<int>> res;
	res = obj.levelOrder(root);
	return 0;
}