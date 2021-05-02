# include <iostream>

using namespace std;

/*
��תһ��������
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
	// Method 1 ���� ����ͷ�� ʱ�临�Ӷ����� �ռ临�Ӷȳ���
	ListNode* reverseList(ListNode* head) {
		
		if (!head) return nullptr; // ����Ϊ��
		if (!head->next) return head; // ������Ϊ1

		auto prev_p = head;
		auto p = head->next;
		while (p) {
			// �г�p������ ����pͷ��
			prev_p->next = p->next;
			p->next = head;
			head = p; // ��������ͷ��
			p = prev_p->next; // ����p ��һ��ѭ������ͷ��
		}

		return head;
	}

	// Method 2 �ݹ�
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
