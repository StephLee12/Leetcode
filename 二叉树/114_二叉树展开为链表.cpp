# include <iostream>
# include <vector>
# include <algorithm>
# include <stack>

using namespace std;

/*
给你二叉树的根结点 root ，请你将它展开为一个单链表：

展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。

展开后的单链表应该与二叉树 先序遍历 顺序相同。

*/

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	// Method 1 暴力 先得到先序遍历 再直接修改指针(原地修改) 但是有先序序列的额外开销
	void flatten(TreeNode* root) {
		if (!root) return;

		vector<TreeNode*> preorder;
		dfs(root, preorder); // 获得先序序列

		TreeNode* p = root; // 树的指针
		p->left = nullptr; // 将根结点的左子结点释放
		for (int i = 1; i < preorder.size(); i++) {
			// 循环变量从1开始
			// 每次循环释放结点的左子结点 然后将它作为上一个结点的右子结点
			auto node = preorder[i]; 
			node->left = nullptr;
			p->right = node;
			p = node;
		}
	}

	// dfs先序遍历
	void dfs(TreeNode* root,vector<TreeNode*>& preorder) {
		if (root) {
			preorder.push_back(root);
			dfs(root->left, preorder);
			dfs(root->right, preorder);
		}
	}


	// Method 2 没有额外的空间开销 神似Morris算法
	// 每次释放当前根结点的左子树 将左子树接到右子树上 而右子树接到左子树的最右结点上
	void flatten(TreeNode* root) {
		TreeNode* p = root;
		while (p) {
			if (p->left) {
				auto next = p->left;
				// 找到左子树中能到达的最右结点
				auto pred = p->left;
				while (pred->right) pred = pred->right;

				// 相当于断开p的右子树 然后将p的左子树接到右子树上
				// 原来p的右子树 接到了左子树的最右结点
				pred->right = p->right; // 将pred结点指向p的右子树
				p->left = nullptr;
				p->right = next;
			}
			p = p->right;
		}
	}
};