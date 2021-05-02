# include <vector>
# include <algorithm>
# include <iostream>
# include <queue>
# include <stack>

using namespace std;

// 给定一个二叉树，返回其节点值的锯齿形层序遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};


class Solution {
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

		// Method 1 双端队列
		vector<vector<int>> res;
		if (!root) return res; // 边界情况

		queue<TreeNode*> q;
		q.push(root);

		int counter_loop = 1;  // 判断从右开始遍历还是从左开始
		while (!q.empty()) {
			vector<int> tmp; // 存储当前层的结点值
			// 由于是锯齿形遍历 若下一层从右开始遍历 则需要将下一层的左侧结点先入栈 
			// 实际上是双端队列
			stack<TreeNode*> stk;  

			int now_cnt = q.size();
			for (int i = 1; i <= now_cnt; i++) {
				root = q.front();
				q.pop();

				tmp.push_back(root->val);
				if (counter_loop % 2 == 0) {
					// 下一层从左开始遍历
					// 右结点先入栈
					if (root->right) stk.push(root->right);
					if (root->left) stk.push(root->left);	
				}
				else {
					// 下一层从右开始遍历
					// 左结点先入栈
					if (root->left) stk.push(root->left);
					if (root->right) stk.push(root->right);
				}
			}
			res.push_back(tmp);

			// 将栈中数据弹出 存入队列
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