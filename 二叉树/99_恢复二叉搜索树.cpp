# include <iostream>
# include <vector>
# include <algorithm>
# include <stack>


/*
��������������ĸ��ڵ� root �������е������ڵ㱻����ؽ��������ڲ��ı���ṹ������£��ָ��������

���ף�ʹ�� O(n) �ռ临�ӶȵĽⷨ������ʵ�֡��������һ��ֻʹ�ó����ռ�Ľ��������

*/

// �����ռ�϶�Ҫ�õ�Morris����

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	// Method 1 �ǵݹ��������
	void recoverTree(TreeNode* root) {
		// �����ٱ�����ͬʱ��¼������Ϣ ����Ҫ����������б���
		stack<TreeNode*> stk;
		// ��������������� x y
		TreeNode* x = nullptr;
		TreeNode* y = nullptr;
		// root��ǰ�����
		TreeNode* prev_root = nullptr;

		while (!stk.empty() || root) {
			while (root) {
				// ��������
				stk.push(root);
				root = root->left;
			}

			// ���ջ�����
			root = stk.top();
			stk.pop();

			// ���if�����ж��ǹؼ�
			// ץס������������ص� �������һ��������
			// ����ֻҪ�Ƚ�ǰ�����ֵ ���ܷ��ֽ����Ľ��
			if (prev_root && prev_root->val > root->val) {
				y = root;
				// ���xΪ�� ��prev_root����x 
				// x�൱�������������б��������Ϊ��ǰ�Ľ��
				// ���xy���� �����break�������ᴥ�� ��Ϊ֮������Ľ�㻹����������
				// �� 1 2 3 4 5 ������ 1 3 2 4 5
				// ���xy������ ��if�жϻ��ٴ���һ�� ˵���ҵ��������Ϊ����Ľ�� ֱ��break
				// �� 1 2 3 4 5 ������ 1 5 3 4 2
				if (!x) x = prev_root;
				else break;
			}
			// ����ǰroot��㸳ֵ��last�����root
			prev_root = root;
			root = root->right;
		}

		swap(x->val, y->val);
	}

	// Method 2 Morris������� 
	void recoverTree(TreeNode* root) {
		 
		// ˼���Method 2 ��� ֻ�ǲ���ջ �ռ临�Ӷ�Ϊ����
		TreeNode* prev_root = nullptr;
		TreeNode* x = nullptr;
		TreeNode* y = nullptr;
		TreeNode* pred = nullptr;// Morris�����е�ǰ�����������ҽ��

		while (root) {
			if (root->left) {
				// root����������
				// ����root�������������ҽ��
				// ����������һ�� Ȼ������������
				pred = root->left;
				while (pred->right && pred->right != root) {
					// ѭ����ǰһ��������֤�䲻�ᵽnullptr
					// ��һ��������֤�䲻��������ѭ�� ��Ϊpred���ҽ������Ѿ���Ϊroot
					pred = pred->right;
				}
				if (!pred->right) {
					// ���pred�����ӽ��Ϊ�� �󶨵�ǰroot
					pred->right = root;
					// root���¼���������
					root = root->left;
				}
				else {
					// pred�����ӽ�㲻Ϊ�� ˵����ǰroot���������Ѿ���������
					
					if (prev_root && prev_root->val > root->val) {
						y = root;
						if (!x) x = prev_root;
						// else break; // ����ֱ��break ��Ϊline154Ҳ�������ж�
					}

					pred->right = nullptr; // ����� �ָ����ṹ
					prev_root = root;
					root = root->right;
				}
			}
			else {
				// root������������

				// ˼��ͬMethod 2
				if (prev_root && prev_root->val > root->val) {
					y = root;
					if (!x) x = prev_root;
					// else break;
				}

				prev_root = root;
				root = root->right;
				
			}
		}

		swap(x->val, y->val);
	}
};

int main() {
	TreeNode* root = new TreeNode{ 1,new TreeNode{3,nullptr,new TreeNode{2}},nullptr };
	Solution obj;
	obj.recoverTree(root);
	return 0;
}