# include <vector>
# include <iostream>

using namespace std;

/*
请判断一个链表是否为回文链表。
*/


struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
	bool isPalindrome(ListNode* head) {
		if (!head || !head->next) return true;

		// 计算链表的长度
		int len = 0;
		auto p = head;
		while (p) {
			len++;
			p = p->next;
		}

		// 计算分割链表的位置
		int splitPos = len / 2;
		int cnt = 0;
		auto splitNode = head;
		while (++cnt < splitPos) {
			splitNode = splitNode->next;
		}

		// 获取后段链表
		auto nextHead = (len % 2 == 0) ? splitNode->next : splitNode->next->next;
		if (len % 2 == 1) splitNode = splitNode->next;
		splitNode->next = nullptr; // 切除连接

		// 反转后段链表
		p = nextHead->next;
		auto oriHead = nextHead;
		while (p) {
			oriHead->next = p->next; // 将原链表头的next指向p的next 切除p的前端连接
			p->next = nextHead; // 将p的next指向头部
			nextHead = p; // 更新头部
			p = oriHead->next; // 更新p
		}

		// 判断回文
		p = head;
		auto nextP = nextHead;
		while (nextP) {
			if (p->val != nextP->val) return false;
			p = p->next;
			nextP = nextP->next;
		}
		return true;
		// splitNode->next = nextHead; // 恢复连接
	}
};

 