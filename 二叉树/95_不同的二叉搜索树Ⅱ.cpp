# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
给定一个整数 n，生成所有由 1 ... n 为节点所组成的 二叉搜索树
*/

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	vector<TreeNode*> generateTrees(int n) {
		if (n == 0) return vector<TreeNode*>(); // 边界情况

		// 递归 这种很多可能的情况 对于树 可以列举出其左子树、右子树所有可能 进行拼接
		return recursive(1,n);
	}

	vector<TreeNode*> recursive(int start, int end) {
		if (start > end) return {nullptr};

		vector<TreeNode*> trees;
		// 遍历所有可能的根结点
		for (int root = start; root <= end; root++) {
			// 获得所有可能的左子树
			vector<TreeNode*> left_trees = recursive(start, root - 1);
			// 获得所有可能的右子树
			vector<TreeNode*> right_trees = recursive(root + 1, end);

			// 进行组合 笛卡尔积
			for (auto&& l_tree : left_trees) {
				for (auto&& r_tree : right_trees) {
					TreeNode* cur_root = new TreeNode{ root };
					cur_root->left = l_tree;
					cur_root->right = r_tree;
					trees.push_back(cur_root);
				}
			}
		}
		
		return trees;
	}
};	