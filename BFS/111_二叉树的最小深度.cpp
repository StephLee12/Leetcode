# include <vector>
# include <algorithm>
# include <iostream>
# include <queue>
# include <stack>

using namespace std;

//给定一个二叉树，找出其最小深度。
//
//最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
//
//说明：叶子节点是指没有子节点的节点


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	int minDepth(TreeNode* root) {
		// Method 1 BFS 对于这种求最短xx BFS比较好用
		if (!root) return 0;

		queue<TreeNode*> q;
		q.push(root);

		int min_depth = 1;
		while (!q.empty()) {
			// BFS遍历
			int now_cnt = q.size();
			for (int i = 1; i <= now_cnt; i++) {
				root = q.front();
				q.pop();

				// 如果遇到叶子结点 直接结束遍历 BFS能保证此时的叶子结点到根结点的路径是最短的
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