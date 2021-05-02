# include <vector>
# include <algorithm>
# include <iostream>

using namespace std;

/*
路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。

同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

路径和 是路径中各节点值的总和。

给你一个二叉树的根节点 root ，返回其 最大路径和 。

*/

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	int max_path = INT_MIN; // 设置全局变量 记录最大路径和

	int maxPathSum(TreeNode* root) {
		// Method 1 dfs递归
		dfs(root);
		return max_path;
	}
	int dfs(TreeNode* root) {
		if (root == nullptr) return 0;

		// 左子树对最长路径的贡献 如果贡献长度小于0 则不能选择该子树的路径
		// 即l_gain=0
		int l_gain = max(dfs(root->left), 0);
		// 右子树同理
		int r_gain = max(dfs(root->right), 0);
		// 最大路径和 取决于当前结点的值和左右子树的贡献值
		int new_path = root->val + l_gain + r_gain;
		max_path = max(max_path, new_path);

		// 函数返回值是以该结点为起点的最大路径
		return root->val + max(l_gain, r_gain);
	}
};