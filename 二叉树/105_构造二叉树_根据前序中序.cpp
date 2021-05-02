# include <iostream>
# include <vector>
# include <algorithm>
# include <stack>
# include <unordered_map>

using namespace std;


struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

/*
根据前序遍历和中序遍历构造二叉树

可以假设树中没有重复元素
*/

// 前序 根左右 中序 左根右

class Solution {
public:
	unordered_map<int, int> index;

	// Method 1 递归 递归一定是从大问题拆解成小问题 不能从小的地方想
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		
		int node_num = inorder.size();
		for (int i = 0; i < node_num; i++) index[inorder[i]] = i; // 中序遍历的val为键 位置为值

		return recursive(preorder, inorder, 0, node_num - 1, 0, node_num - 1);
	}

	TreeNode* recursive(vector<int>& preorder, vector<int>& inorder, int pre_left, int pre_right, int in_left, int in_right) {
		if (pre_left > pre_right) return nullptr; //递归结束

		int pre_root_pos = pre_left; // 前序遍历中第一个结点就是根结点 preorder_root_pos是根结点在前序序列的位置
		int pre_root_val = preorder[pre_root_pos]; // 根结点对应的值
		int in_root_pos = index[pre_root_val]; // 找到根结点在中序遍历中的位置

		// 中序遍历根结点左侧都是左子树 右侧都是右子树 根据此递归建树

		// 创建根结点 是用new创建
		TreeNode* root = new TreeNode{ pre_root_val };
		int l_tree_size = in_root_pos - in_left; // 左子树的结点数
		// 开始递归构造左子树
		root->left = recursive(preorder, inorder, pre_left + 1, pre_left + l_tree_size, in_left, in_root_pos - 1);
		// 开始递归构造右子树
		root->right = recursive(preorder, inorder, pre_left + l_tree_size + 1, pre_right, in_root_pos + 1, in_right);

		return root;
	}

	// Method 2 迭代
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		
		if (!preorder.size()) return nullptr;
		TreeNode* root = new TreeNode{ preorder[0] }; // 创建根结点
		stack<TreeNode*> stk;
		stk.push(root);
		int inorder_idx = 0; // 中序遍历的指针 记录当前走的最远的左结点的位置
		
		for (int i = 1; i < preorder.size(); i++) {
			int preorder_val = preorder[i];
			TreeNode* node = stk.top();

			if (node->val != inorder[inorder_idx]) {
				node->left = new TreeNode{ preorder_val };
				stk.push(node->left);
			}
			else {
				// 回溯
				while (!stk.empty() && stk.top()->val == inorder[inorder_idx]) {
					node = stk.top();
					stk.pop();
					inorder_idx++;
				}
				node->right = new TreeNode{ preorder_val };
				stk.push(node->right);
			}
		}

		return root;
	}
};