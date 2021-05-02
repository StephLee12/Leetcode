# include <iostream>

using namespace std;

/*
反转一个单链表。
*/

struct ListNode
{
	int val;
	ListNode* next;
	ListNode():val(0),next(nullptr){}
	ListNode(int x):val(x),next{nullptr} {}
	ListNode(int x, ListNode* next):val(x),next(next){}
};

class Solution {
public:
	// Method 1 迭代 不断头插 时间复杂度线性 空间复杂度常数
	ListNode* reverseList(ListNode* head) {
		
		if (!head) return nullptr; // 链表为空
		if (!head->next) return head; // 链表长度为1

		auto prev_p = head;
		auto p = head->next;
		while (p) {
			// 切除p的连接 并将p头插
			prev_p->next = p->next;
			p->next = head;
			head = p; // 更新链表头部
			p = prev_p->next; // 更新p 下一轮循环继续头插
		}

		return head;
	}

	// Method 2 递归
	ListNode* reverseList(ListNode* head) {
		return recursive(nullptr, head);
	}

	ListNode* recursive(ListNode* prev_p, ListNode* p) {
		if (!p) return prev_p;
		auto next = p->next;
		p->next = prev_p;
		return recursive(p, next);
	}
};
