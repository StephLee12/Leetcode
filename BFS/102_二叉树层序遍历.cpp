# include <vector>
# include <algorithm>
# include <iostream>
# include <queue>

using namespace std;

// 返回层序遍历得到的结点值


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {

		vector<vector<int>> res; // 返回结果
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