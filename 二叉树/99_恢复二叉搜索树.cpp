# include <iostream>
# include <vector>
# include <algorithm>
# include <stack>


/*
给你二叉搜索树的根节点 root ，该树中的两个节点被错误地交换。请在不改变其结构的情况下，恢复这棵树。

进阶：使用 O(n) 空间复杂度的解法很容易实现。你能想出一个只使用常数空间的解决方案吗？

*/

// 常数空间肯定要用到Morris遍历

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
};

class Solution {
public:
	// Method 1 非递归中序遍历
	void recoverTree(TreeNode* root) {
		// 但是再遍历的同时记录交换信息 不需要获得中序序列遍历
		stack<TreeNode*> stk;
		// 待交换的两个结点 x y
		TreeNode* x = nullptr;
		TreeNode* y = nullptr;
		// root的前驱结点
		TreeNode* prev_root = nullptr;

		while (!stk.empty() || root) {
			while (root) {
				// 向左搜索
				stk.push(root);
				root = root->left;
			}

			// 获得栈顶结点
			root = stk.top();
			stk.pop();

			// 这个if条件判断是关键
			// 抓住了中序遍历的特点 中序遍历一定是升序
			// 所以只要比较前后结点的值 就能发现交换的结点
			if (prev_root && prev_root->val > root->val) {
				y = root;
				// 如果x为空 则将prev_root赋给x 
				// x相当于是中序序列中被交换后较为靠前的结点
				// 如果xy相邻 则这个break条件不会触发 因为之后遍历的结点还是升序序列
				// 如 1 2 3 4 5 交换后 1 3 2 4 5
				// 如果xy不相邻 该if判断会再触发一次 说明找到交换后较为靠后的结点 直接break
				// 如 1 2 3 4 5 交换后 1 5 3 4 2
				if (!x) x = prev_root;
				else break;
			}
			// 将当前root结点赋值给last后更新root
			prev_root = root;
			root = root->right;
		}

		swap(x->val, y->val);
	}

	// Method 2 Morris中序遍历 
	void recoverTree(TreeNode* root) {
		 
		// 思想和Method 2 差不多 只是不用栈 空间复杂度为常数
		TreeNode* prev_root = nullptr;
		TreeNode* x = nullptr;
		TreeNode* y = nullptr;
		TreeNode* pred = nullptr;// Morris遍历中当前左子树的最右结点

		while (root) {
			if (root->left) {
				// root存在左子树
				// 搜索root的左子树的最右结点
				// 即先向左走一步 然后疯狂向右搜索
				pred = root->left;
				while (pred->right && pred->right != root) {
					// 循环的前一个条件保证其不会到nullptr
					// 后一个条件保证其不会陷入死循环 因为pred的右结点可能已经绑定为root
					pred = pred->right;
				}
				if (!pred->right) {
					// 如果pred的右子结点为空 绑定当前root
					pred->right = root;
					// root更新继续往左走
					root = root->left;
				}
				else {
					// pred的右子结点不为空 说明当前root的左子树已经遍历完了
					
					if (prev_root && prev_root->val > root->val) {
						y = root;
						if (!x) x = prev_root;
						// else break; // 不能直接break 因为line154也有条件判断
					}

					pred->right = nullptr; // 解除绑定 恢复树结构
					prev_root = root;
					root = root->right;
				}
			}
			else {
				// root不存在左子树

				// 思想同Method 2
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