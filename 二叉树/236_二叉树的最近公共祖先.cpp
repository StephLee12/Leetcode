using namespace std;


/*
����һ��������, �ҵ�����������ָ���ڵ������������ȡ�

�ٶȰٿ�������������ȵĶ���Ϊ��

�������и��� T �������ڵ� p��q������������ȱ�ʾΪһ���ڵ� x��

���� x �� p��q �������� x ����Ⱦ����ܴ�һ���ڵ�Ҳ���������Լ������ȣ�����

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
		// Method 1 �ݹ�
		return recursive(root, p, q);
	}
	TreeNode* recursive(TreeNode* root, TreeNode* p, TreeNode* q) {
		// �ݹ�ֹͣ����
		if (!root) return nullptr;
		if (root->val == q->val) return q; // ����ֱ�ӷ���q ���p����qΪ�������� ��ô����������ȼ�Ϊq ���������qΪ�������� ��ô���ظý�� �Թ������ж�
		if (root->val == p->val) return p;

		// root���������Ƿ���p����q ���û�з���nullptr ����з���p��q�и߶Ƚϸߵ�
		auto node_left = recursive(root->left, p, q);
		auto node_right = recursive(root->right, p, q);

		if (node_left && !node_right) {
			return node_left;
		}
		else if (!node_left && node_right) {
			return node_right;
		}
		else if (node_left && node_right) {
			return root; // ���p��q�ֱ������������� ����ߵ��������Ϊroot
		}
		else return nullptr;
	}
};
