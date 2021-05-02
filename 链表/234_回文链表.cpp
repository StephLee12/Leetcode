# include <vector>
# include <iostream>

using namespace std;

/*
���ж�һ�������Ƿ�Ϊ��������
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

		// ��������ĳ���
		int len = 0;
		auto p = head;
		while (p) {
			len++;
			p = p->next;
		}

		// ����ָ������λ��
		int splitPos = len / 2;
		int cnt = 0;
		auto splitNode = head;
		while (++cnt < splitPos) {
			splitNode = splitNode->next;
		}

		// ��ȡ�������
		auto nextHead = (len % 2 == 0) ? splitNode->next : splitNode->next->next;
		if (len % 2 == 1) splitNode = splitNode->next;
		splitNode->next = nullptr; // �г�����

		// ��ת�������
		p = nextHead->next;
		auto oriHead = nextHead;
		while (p) {
			oriHead->next = p->next; // ��ԭ����ͷ��nextָ��p��next �г�p��ǰ������
			p->next = nextHead; // ��p��nextָ��ͷ��
			nextHead = p; // ����ͷ��
			p = oriHead->next; // ����p
		}

		// �жϻ���
		p = head;
		auto nextP = nextHead;
		while (nextP) {
			if (p->val != nextP->val) return false;
			p = p->next;
			nextP = nextP->next;
		}
		return true;
		// splitNode->next = nextHead; // �ָ�����
	}
};

 