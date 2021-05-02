# include <iostream>
# include <algorithm>
# include <vector>
# include <stack>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */


// 中序遍历二叉树 左中右
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};


class Solution {
public:
	// Method 1 递归
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		if (!root) return res;
		recursive(root, res);
		return res;
	}

	void recursive(TreeNode* root, vector<int>& res) {
		if (!root) return;
		recursive(root->left, res);
		res.push_back(root->val);
		recursive(root->right, res);
	}

	// Method 2 非递归(迭代)
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		if (!root) return res; // 二叉树为空

		stack<TreeNode*> st;
		// 注意这里的循环结束条件
		// 当root==nullptr(root=root->right导致)但栈不为空时 要继续循环
		// 当root!=nullptr但栈为空时 要继续循环
		while (root || !st.empty()) {
			// 遍历左结点
			while (root) {
				st.push(root);
				root = root->left;
			}
			// 获取栈顶结点
			root = st.top();
			st.pop();
			res.push_back(root->val);
			// 下面这条语句 即为回溯
			// 当root->right为null时 root是作为叶结点被遍历(父结点的左结点)
			// 当root->right不为空时 root是作为根结点被遍历
			root = root->right;
		}
		
	}

	// Method 3 Morris中序遍历
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> res;
		if (!root) return res; // 二叉树为空

		// 空间复杂度降为常数
		// 核心思想:用当前左子树的 遍历的最后一个右结点pred 记录当前根结点
		// 从而达到不使用栈且回溯的效果 链表的思想
		TreeNode* pred = nullptr;
		while (root) {
			if (root->left) {
				// 寻找pred
				pred = root->left;
				// 循环的第二个条件 是因为pred可能在一开始就与root绑定
				// 所以在回溯的时候如果不设置这个条件 会导致死循环
				while (pred->right && pred->right != root) {
					pred = pred->right;
				}
				if (!pred->right) {
					// pred如果没和root绑定 一定是个叶子结点
					pred->right = root; // 指向root
					root = root->left; // 继续遍历root的左子树
				}
				else {
					// 说明pred的右结点为root
					// 说明root的左子树已经遍历完
					res.push_back(root->val);
					// 重置pred 是为了恢复树的结构 因为这条link加上之后不再是树了
					pred->right = nullptr; 
					root = root->right; // 更新root 遍历右子树
				}
			}	
			else {
				// 若root没有左结点
				res.push_back(root->val);
				// 这里不用考虑 存在没遍历完但是root==nullptr的情况
				// 因为pred的右结点为root
				root = root->right;
			}
		}
			
		return res;
	}
};