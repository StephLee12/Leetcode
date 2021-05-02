# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
����һ������ n������������ 1 ... n Ϊ�ڵ�����ɵ� ����������
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
		if (n == 0) return vector<TreeNode*>(); // �߽����

		// �ݹ� ���ֺܶ���ܵ���� ������ �����оٳ��������������������п��� ����ƴ��
		return recursive(1,n);
	}

	vector<TreeNode*> recursive(int start, int end) {
		if (start > end) return {nullptr};

		vector<TreeNode*> trees;
		// �������п��ܵĸ����
		for (int root = start; root <= end; root++) {
			// ������п��ܵ�������
			vector<TreeNode*> left_trees = recursive(start, root - 1);
			// ������п��ܵ�������
			vector<TreeNode*> right_trees = recursive(root + 1, end);

			// ������� �ѿ�����
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