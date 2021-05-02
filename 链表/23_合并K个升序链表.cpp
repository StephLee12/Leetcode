# include <vector>
# include <algorithm>
# include <iostream>
# include <queue>

using namespace std;

/*
����һ���������飬ÿ�������Ѿ����������С�

���㽫��������ϲ���һ�����������У����غϲ��������
*/

struct ListNode
{
	int val;
	ListNode* next;
};

class Solution {
public:
	// Method 1 �鲢
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		if (lists.size() == 0) return nullptr;
		return recursive(lists, 0, lists.size()-1);
	}

	ListNode* recursive(vector<ListNode*>& lists, int low, int high) {
		if (low < high) {
			int mid = (low + high) / 2;
			ListNode* left = recursive(lists, low, mid);
			ListNode* right = recursive(lists, mid + 1, high);
			return mergeTwoLists(left, right);
		}
		return lists[low];
	}

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

	// Method 2 ���ȶ���
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		ListNode* dummy = new ListNode{ 0 };
		// �Զ������ȶ��бȽ����� ����lambda���ʽ
		auto comp = [&](ListNode* const a, ListNode* const b) {return a->val > b->val; };
		// ����һ��С����
		priority_queue<ListNode*, vector<ListNode*>, decltype(comp)> q(comp);
		for (auto&& lst : lists) {
			if (lst) q.push(lst);
		}

		ListNode* p = dummy;
		while (!q.empty()) {
			// ÿ�ε����Ѷ�Ԫ�� p��nextָ��ָ���Ԫ��
			p->next = q.top();
			q.pop();
			p = p->next; // ����p
			if (p->next) q.push(p->next); // ��p->next���
		}
		return dummy->next;

	}
};