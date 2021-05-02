# include <vector>
# include <algorithm>
# include <iostream>
# include <queue>
# include <stack>

using namespace std;

// 给定一个二叉树，返回其节点值自底向上的层序遍历。 （
// 即按从叶子节点所在层到根节点所在的层，逐层从左向右遍历）


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> res; // 返回结果.

		if (!root) return res; // 临界情况

		queue<TreeNode*> q; // 层序遍历 队列
		q.push(root); // 整棵树的根结点先入队

		while (!q.empty()) {

			vector<int> tmp; // 存储当前层的结点值
			int now_cnt = q.size();
			// 遍历当前结点的值
			for (int i = 1; i <= now_cnt; i++) {
				root = q.front();
				q.pop();
				tmp.push_back(root->val);

				// 下一层结点入队
				if (root->left) q.push(root->left);
				if (root->right) q.push(root->right);
			}
			res.push_back(tmp);
		}

		// 与102题一样 多一个reverse
		reverse(res.begin(), res.end());
		return res;
	}
};