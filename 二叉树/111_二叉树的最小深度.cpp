# include <vector>
# include <algorithm>
# include <iostream>
# include <queue>
# include <stack>

using namespace std;

//����һ�����������ҳ�����С��ȡ�
//
//��С����ǴӸ��ڵ㵽���Ҷ�ӽڵ�����·���ϵĽڵ�������
//
//˵����Ҷ�ӽڵ���ָû���ӽڵ�Ľڵ�


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	int minDepth(TreeNode* root) {
		// Method 1 BFS �������������xx BFS�ȽϺ���
		if (!root) return 0;

		queue<TreeNode*> q;
		q.push(root);

		int min_depth = 1;
		while (!q.empty()) {
			// BFS����
			int now_cnt = q.size();
			for (int i = 1; i <= now_cnt; i++) {
				root = q.front();
				q.pop();

				// �������Ҷ�ӽ�� ֱ�ӽ������� BFS�ܱ�֤��ʱ��Ҷ�ӽ�㵽������·������̵�
				if (root->left && root->right) {
					q.push(root->left);
					q.push(root->right);
				}
				else if (root->left == nullptr && root->right != nullptr) q.push(root->right);
				else if (root->left != nullptr && root->right == nullptr) q.push(root->left);
				else goto End;

			}
			min_depth += 1;
		}
		End:
		return min_depth;
	}
};