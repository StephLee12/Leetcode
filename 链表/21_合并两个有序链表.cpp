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

		// ֱ�Ӵ�l1�ϲ��� ��l2��l1С ���߽��� ʼ�ձ�֤l1��ͷԪ�ر�l2С
		if (l1->val > l2->val) return mergeTwoLists(l2, l1); 

		ListNode* p_1 = l1; ListNode* p_2 = l2; // ���������ָ��
		while (p_1->next && p_2) { // ѭ������������ һ��Ҫ��ѭ���� ������ʹ���Ƿ�Խ��
			int now_val = p_1->val;
			int next_val = p_1->next->val; // ����Ҫ�õ�p_1->next ����p_1->next����Ϊ��
			// ֻ�е�p_2->val ��[now_val,next_val]������ �ſ��Բ���
			if (p_2->val >= now_val && p_2->val <= next_val) {
				ListNode* tmp = p_2->next; // �ȱ���p_2->next ���p_2Ҫ����
				// ����p_2
				p_2->next = p_1->next;
				p_1->next = p_2;

				// ����p_1 p_2
				p_1 = p_1->next;
				p_2 = tmp; // tmp����Ϊ��
			}
			else p_1 = p_1->next; // ���������� ����1ָ��Ҫ�ƶ�
		}
		
		if (p_2) p_1->next = p_2; // ������1���������һ����� ֱ�ӽ����һ������nextָ��p_2
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