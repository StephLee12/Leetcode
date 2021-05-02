# include <iostream>
# include <algorithm>

using namespace std;

// ����һ�����������ж����Ƿ��Ǹ߶�ƽ��Ķ�������
// AVL��ָÿ���������������**�߶�**֮��ľ���ֵ������1
// ע��߶Ⱥ���Ȳ�Ҫ����
// ĳ���ĸ߶�(Height)��ָ �ӵ�ǰ��㵽�����Ҷ����·������
// Height = max(�Ӹý�������������������Ҷ���·����,��������������·����)
// ĳ�������(depth)��ָ �Ӹ���㵽��ǰ����·������
// ��������Ϊ0 Ҷ���߶�Ϊ0

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
};

class Solution {
public:
	
	// Method 1 �Ե����ϵݹ�
	bool isBalanced(TreeNode* root) {
		// �Ե����� ֻҪ���ֲ���AVL������ ������������AVL ������ǰ�ж�
		return recursive(root) != -1;
	}

	int recursive(TreeNode* root) {
		
		// -1�൱��һ��flag �ж��Ƿ���AVL
		// �Ǻ������
		// ��Ϊ�ս�� ·����Ϊ0
		if (!root) return 0;
		// ע�� �Դ�Ҷ���(��Ҷ���ĸ��ڵ�)Ϊ������ һ��ƽ��
		// ������rootΪ�������������߶�
		// ����root������������������Ҷ����·����
		int l_height = recursive(root->left);
		// ��ĳ��������AVL ��ֱ�ӽ����ݹ�
		if (l_height == -1) return -1;
		// ������rootΪ���������������
		int r_height = recursive(root->right);
		// ��ĳ��������AVL ��ֱ�ӽ����ݹ�
		if (r_height == -1) return -1;

		// ����ÿ��rootΪ���������ĸ߶�+1 ��Ϊ�ݹ���� rootҪ��Ϊ�丸��� ����·������+1
		// ע�������max���� �߶ȼ�Ϊ�Ƚ�����������Ҷ�����·��
		return abs(l_height - r_height) <= 1 ? max(l_height, r_height) + 1 : -1;

	}

	// Method 2 �Զ�����
	// ��Ȼ�ݹ鶼�Ǵ�Ҷ������� ���Ǹ÷�������ÿ����� Ҫ��ȡ�߶�
	// ��˻�Ҫ�����¼���(��˳�Ϊ�Զ�����) ������ظ����� 
	int height(TreeNode* root) {
		if (!root) return 0;
		return max(height(root->left), height(root->right));
	}

	bool isBalanced_v2(TreeNode* root) {
		if (!root) return true;
		// Ҫ���жϵ�ǰ����Ƿ�ƽ�� ����һ������ ����ظ�����
		// ��ʹ�Ѻ������������ŵ�ǰ�� Ҳ����
		// ��Ϊ���������ֱ�ƽ�� ���ܱ�֤��rootΪ������ƽ��
		// ���� root���������ܸ� ���������ܰ�
		return (abs(height(root->left) - height(root->right)) <= 1 && isBalanced_v2(root->left) && isBalanced_v2(root->right));
	}
};