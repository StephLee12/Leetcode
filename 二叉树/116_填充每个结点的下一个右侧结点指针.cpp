# include <iostream>
# include <vector>
# include <stack>
# include <queue>
# include <algorithm>

using namespace std;


/*
给定一个 完美二叉树 ，其所有叶子节点都在同一层，每个父节点都有两个子节点。

填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。

进阶：

你只能使用常量级额外空间。

使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。
*/

// 完美二叉树——通俗理解 满树

struct Node {
	int val;
	Node* left;
	Node* right;
	Node* next;
};


class Solution {
public:
	Node* connect(Node* root) {

		if (!root) return root; // 空树

		Node* p = root; // 树的指针0
		Node* level_left = root; // 维护一个每一层最左边的结点
		while (p->left) {
			while (p) {
				// 进行连接 注意连接的顺序
				p->left->next = p->right; // 先对当前p的子结点进行连接
				if (p->next) p->right->next = p->next->left; // 如果p存在兄弟结点 在将p的右子结点与p的兄弟结点的左子结点连接
				p = p->next; // 更新p
				
			}
			// 该层已经连接完 进入下一层 更新每一层最左边的结点
			level_left = level_left->left;
			p = level_left;
		}

		return root;
	}
};

int main() {
	Node* p = new Node{ 1,new Node{2,new Node{3},new Node{4}},new Node{5,new Node{6},new Node{7}} };
	Solution obj;
	obj.connect(p);
	return 0;
}