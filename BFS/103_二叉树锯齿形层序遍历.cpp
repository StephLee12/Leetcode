# include <vector>
# include <algorithm>
# include <iostream>
# include <queue>
# include <stack>

using namespace std;

// ����һ����������������ڵ�ֵ�ľ���β�������������ȴ������ң��ٴ������������һ��������Դ����ƣ������֮�佻����У���


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};


class Solution {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

		// Method 1 ˫�˶���
		vector<vector<int>> res;
		if (!root) return res; // �߽����

		queue<TreeNode*> q;
		q.push(root);

		int counter_loop = 1;  // �жϴ��ҿ�ʼ�������Ǵ���ʼ
		while (!q.empty()) {
			vector<int> tmp; // �洢��ǰ��Ľ��ֵ
			// �����Ǿ���α��� ����һ����ҿ�ʼ���� ����Ҫ����һ������������ջ 
			// ʵ������˫�˶���
			stack<TreeNode*> stk;  

			int now_cnt = q.size();
			for (int i = 1; i <= now_cnt; i++) {
				root = q.front();
				q.pop();

				tmp.push_back(root->val);
				if (counter_loop % 2 == 0) {
					// ��һ�����ʼ����
					// �ҽ������ջ
					if (root->right) stk.push(root->right);
					if (root->left) stk.push(root->left);	
				}
				else {
					// ��һ����ҿ�ʼ����
					// ��������ջ
					if (root->left) stk.push(root->left);
					if (root->right) stk.push(root->right);
				}
			}
			res.push_back(tmp);

			// ��ջ�����ݵ��� �������
			while (!stk.empty()) {
				root = stk.top();
				stk.pop();
				q.push(root);
			}

			counter_loop++;
		}

		return res;
	}
};