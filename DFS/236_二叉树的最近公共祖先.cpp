using namespace std;


/*
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：

“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，

满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

*/

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		// Method 1 递归
		return recursive(root, p, q);
	}
	TreeNode* recursive(TreeNode* root, TreeNode* p, TreeNode* q) {
		// 递归停止条件
		if (!root) return nullptr;
		if (root->val == q->val) return q; // 这里直接返回q 如果p在以q为根的树中 那么二者最近祖先即为q 如果不在以q为根的树中 那么返回该结点 以供下面判断
		if (root->val == p->val) return p;

		// root的左子树是否含有p或者q 如果没有返回nullptr 如果有返回p和q中高度较高的
		auto node_left = recursive(root->left, p, q);
		auto node_right = recursive(root->right, p, q);

		if (node_left && !node_right) {
			return node_left;
		}
		else if (!node_left && node_right) {
			return node_right;
		}
		else if (node_left && node_right) {
			return root; // 如果p和q分别在左右子树中 则二者的最近祖先为root
		}
		else return nullptr;
	}
};
