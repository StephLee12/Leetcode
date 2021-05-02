# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头

*/

struct ListNode
{
	int val;
	ListNode* next;
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		
		// Method 1 链表双指针
		ListNode* res = new ListNode{};
		ListNode* p = res; //链表指针
		bool flag = false; // 判断是否进位
		int sum = 0;
		while (l1 && l2) {
			// 如果前一位进位 则flag=true 两数和还需加1
			sum = (flag? l1->val + l2->val + 1:l1->val+l2->val);
			if (sum >= 10) {
				// 如果当前位需要进位
				flag = true;
				sum %= 10;
			}
			else flag = false;

			// 更新当前结点
			p->val = sum;

			// 指针移动
			l1 = l1->next;
			l2 = l2->next;

			if (l1 || l2) {
				// 这个if 是为了防止出现指针移动后 l1,l2均为空 但却新增了一个结点
				p->next = new ListNode{};
				p = p->next;
			}
		}

		// 若l1空 l2非空
		while (l2) {
			sum = (flag ? l2->val + 1 : l2->val);
			if (sum >= 10) {
				flag = true;
				sum %= 10;
			}
			else flag = false;
			p->val = sum;
			l2 = l2->next;
			if (l2) {
				p->next = new ListNode{};
				p = p->next;
			}
		}
		// 若l2空 l1非空
		while (l1) {
			sum = (flag ? l1->val + 1 : l1->val);
			if (sum >= 10) {
				flag = true;
				sum %= 10;
			}
			else flag = false;
			p->val = sum;
			l1 = l1 ->next;
			if (l1) {
				p->next = new ListNode{};
				p = p->next;
			}
		}
		// 都为空之后 还要进位 则还需多增一个结点
		if (flag) p->next = new ListNode{ 1 };
		return res;
	}
};