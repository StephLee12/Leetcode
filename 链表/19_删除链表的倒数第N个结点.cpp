# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
����һ������ɾ������ĵ����� n ����㣬���ҷ��������ͷ��㡣

���ף����ܳ���ʹ��һ��ɨ��ʵ����

*/
struct ListNode
{
	int val;
	ListNode* next;
};

class Solution {
public:
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		// Method 1 ˫ָ�� һ��ɨ��
		// ������һ��dummy��� ��Ϊ��ɾ��ͷ���ʱ�ô���
		ListNode* dummy = new ListNode{ 0 };
		dummy->next = head;

		// ����ָ��
		ListNode* l_p = nullptr; // l_p���λ��Ҫɾ���Ľ���ǰһ�����λ��
		ListNode* r_p = dummy; // r_p���λ����������һ�����
		int cnt = 0;
		while (r_p->next) {
			// ������Ϊn-1ʱ Ϊl_p��ֵ ������r_p�ƶ������һ�����ʱ l_p�ƶ���ɾ���Ľ���ǰһ�����
			if (cnt < n - 1) cnt++;
			else if (cnt == n - 1) { l_p = dummy; cnt++; }
			else { l_p = l_p->next; cnt++; }

			r_p = r_p->next;
		}
		// ɾ��l_p�ĺ�һ����� ֱ�ӽ�l_p�ĵ�nextָ���ƶ���ɾ�����ĺ�һ�����
		l_p->next = l_p->next->next;

		return dummy->next; // ����dummy����next���
	}
};