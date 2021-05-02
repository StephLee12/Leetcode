# include <iostream>
# include <vector>
# include <algorithm>
# include <stack>


using namespace std;

// 判断该二叉树是否是BST

// Tips: 一棵BST的中序遍历必为升序

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	// Method 1 递归
	bool isValidBST(TreeNode* root) {
		// INT_MIN会溢出
		return bfs(root, LONG_MIN, LONG_MAX);
	}
	bool bfs(TreeNode* root, long long low_bound, long long upper_bound) {
		if (!root) return true;
		if (root->val >= upper_bound || root->val <= low_bound) return false;

		// 对于左子树 其结点所有值都应该在low_bound~root->val区间内(开区间) 右子树同理
		// 相当于把结点分隔到特定区间内 如果超出区间 则一定不是BST
		return bfs(root->left, low_bound, root->val) && bfs(root->right, root->val, upper_bound);

	}

	// Method 2 中序遍历(非递归) 也可以用Morris遍历降低空间复杂度
	bool isValidBST(TreeNode* root) {
		// 对于BST 中序遍历得到的序列一定是升序
		stack<TreeNode*> stk;

		long long pre_num = (long long)INT_MIN - 1;

		while (!stk.empty() || root) {
			while (root) {
				stk.push(root);
				root = root->left;
			}
			root = stk.top();
			stk.pop();
			// 只要判断相邻两个结点的值是否满足升序关系就ok
			if (root->val <= pre_num) return false;
			pre_num = root->val;
			root = root->right;
		}
		return true;

	}
};