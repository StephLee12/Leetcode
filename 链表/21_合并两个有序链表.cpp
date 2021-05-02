# include <algorithm>
# include <iostream>
# include <vector>

using namespace std;

struct ListNode
{
	int val;
	ListNode* next;
};

class Solution {
public:
	ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
		if (!l1) return l2;
		if (!l2) return l1;

		// 直接从l1上插入 若l2比l1小 两者交换 始终保证l1的头元素比l2小
		if (l1->val > l2->val) return mergeTwoLists(l2, l1); 

		ListNode* p_1 = l1; ListNode* p_2 = l2; // 两个链表的指针
		while (p_1->next && p_2) { // 循环条件的设置 一般要看循环内 变量的使用是否越界
			int now_val = p_1->val;
			int next_val = p_1->next->val; // 这里要用到p_1->next 所以p_1->next不能为空
			// 只有当p_2->val 在[now_val,next_val]区间内 才可以插入
			if (p_2->val >= now_val && p_2->val <= next_val) {
				ListNode* tmp = p_2->next; // 先保存p_2->next 最后p_2要更新
				// 插入p_2
				p_2->next = p_1->next;
				p_1->next = p_2;

				// 更新p_1 p_2
				p_1 = p_1->next;
				p_2 = tmp; // tmp可以为空
			}
			else p_1 = p_1->next; // 不在区间内 链表1指针要移动
		}
		
		if (p_2) p_1->next = p_2; // 若链表1遍历到最后一个结点 直接将最后一个结点的next指向p_2
		return l1;
	}
};

int main() {
	ListNode* l1 = new ListNode{ 2 };
	ListNode* l2 = new ListNode{ 1 };
	Solution obj;
	obj.mergeTwoLists(l1, l2);
	return 0;
}