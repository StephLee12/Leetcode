# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。

进阶：你能尝试使用一趟扫描实现吗？

*/
struct ListNode
{
	int val;
	ListNode* next;
};

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// Method 1 双指针 一遍扫描
		// 常设置一个dummy结点 是为了删除头结点时好处理
		ListNode* dummy = new ListNode{ 0 };
		dummy->next = head;

		// 快慢指针
		ListNode* l_p = nullptr; // l_p最后位于要删除的结点的前一个结点位置
		ListNode* r_p = dummy; // r_p最后位于链表的最后一个结点
		int cnt = 0;
		while (r_p->next) {
			// 当计数为n-1时 为l_p赋值 这样当r_p移动到最后一个结点时 l_p移动到删除的结点的前一个结点
			if (cnt < n - 1) cnt++;
			else if (cnt == n - 1) { l_p = dummy; cnt++; }
			else { l_p = l_p->next; cnt++; }

			r_p = r_p->next;
		}
		// 删除l_p的后一个结点 直接将l_p的的next指针移动的删除结点的后一个结点
		l_p->next = l_p->next->next;

		return dummy->next; // 返回dummy结点的next结点
	}
};