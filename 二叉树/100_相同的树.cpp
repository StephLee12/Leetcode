# include <vector>
# include <stack>
# include <iostream>
# include <algorithm>

using namespace std;

/*
给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。

如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的
*/

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	// Method 1 递归
	bool isSameTree(TreeNode* p, TreeNode* q) {
		// 处理临界情况
		if (!p && !q) return true; // 两棵树均为空
		if ((p && !q) || (!p && q)) return false; // 两棵树中只有一棵为空
		if (p->val != q->val) return false; // 根结点的值不相等

		// 在根结点的值相等的条件下 判断左右子树是否相同
		return recursive(p->left, q->left) && recursive(p->right, q->right);
	}

	bool recursive(TreeNode* p,TreeNode* q) {
		if (!p && !q) return true; // 当前两棵树均为空
		if ((p && !q) || (!p && q)) return false; // 两棵树中只有一棵空

		if (p->val == q->val) {
			// 如果当前根结点值相等 继续递归
			return recursive(p->left, q->left) && recursive(p->right, q->right);
		}
		else return false; // 当前根结点的值不相等 直接返回false
	}
};