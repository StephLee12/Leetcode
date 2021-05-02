# include <iostream>
# include <algorithm>

using namespace std;

// 给定一个二叉树，判断它是否是高度平衡的二叉树。
// AVL是指每个结点左右子树的**高度**之差的绝对值不大于1
// 注意高度和深度不要混淆
// 某结点的高度(Height)是指 从当前结点到最深的叶结点的路径长度
// Height = max(从该结点出发到其左子树最深叶结点路径长,到其右子树最深路径长)
// 某结点的深度(depth)是指 从根结点到当前结点的路径长度
// 根结点深度为0 叶结点高度为0

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
};

class Solution {
public:
	
	// Method 1 自底向上递归
	bool isBalanced(TreeNode* root) {
		// 自底向上 只要出现不是AVL的子树 整个树即不是AVL 可以提前判断
		return recursive(root) != -1;
	}

	int recursive(TreeNode* root) {
		
		// -1相当于一个flag 判断是否是AVL
		// 是后序遍历
		// 若为空结点 路径长为0
		if (!root) return 0;
		// 注意 以次叶结点(即叶结点的父节点)为根的树 一定平衡
		// 返回以root为根结点的左子树高度
		// 即从root出发到其左子树最深叶结点的路径长
		int l_height = recursive(root->left);
		// 若某棵树不是AVL 则直接结束递归
		if (l_height == -1) return -1;
		// 返回以root为根结点的右子树深度
		int r_height = recursive(root->right);
		// 若某棵树不是AVL 则直接结束递归
		if (r_height == -1) return -1;

		// 返回每个root为根结点的树的高度+1 因为递归调用 root要变为其父结点 所以路径长度+1
		// 注意这里的max函数 高度即为比较左右子树的叶结点的最长路径
		return abs(l_height - r_height) <= 1 ? max(l_height, r_height) + 1 : -1;

	}

	// Method 2 自顶向下
	// 虽然递归都是从叶结点向上 但是该方法对于每个结点 要获取高度
	// 因此还要再向下计算(因此称为自顶向下) 造成了重复计算 
	int height(TreeNode* root) {
		if (!root) return 0;
		return max(height(root->left), height(root->right));
	}

	bool isBalanced_v2(TreeNode* root) {
		if (!root) return true;
		// 要先判断当前结点是否平衡 即第一个条件 造成重复计算
		// 即使把后面两个条件放到前面 也不行
		// 因为左右子树分别平衡 不能保证以root为根的树平衡
		// 比如 root的左子树很高 而右子树很矮
		return (abs(height(root->left) - height(root->right)) <= 1 && isBalanced_v2(root->left) && isBalanced_v2(root->right));
	}
};