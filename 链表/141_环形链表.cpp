# include <iostream>
# include <vector>
# include <algorithm>
# include <unordered_set>

using namespace std;

/*
����һ�������ж��������Ƿ��л���

�����������ĳ���ڵ㣬����ͨ���������� next ָ���ٴε���������д��ڻ��� 

Ϊ�˱�ʾ���������еĻ�������ʹ������ pos ����ʾ����β���ӵ������е�λ�ã������� 0 ��ʼ����

��� pos �� -1�����ڸ�������û�л���ע�⣺pos ����Ϊ�������д��ݣ�������Ϊ�˱�ʶ�����ʵ�������

��������д��ڻ����򷵻� true �� ���򣬷��� false ��

���ף�

������ O(1)�������������ڴ�����������

*/


struct ListNode {
	int val;
	ListNode* next;
};

class Solution {
public:
	// Method 1 ��set�洢node�ĵ�ַ
	bool hasCycle(ListNode* head) {
		if (!head) return false;

		unordered_set<ListNode*> nodes;
		while (head) {
			if (nodes.find(head) != nodes.end()) return true;
			nodes.insert(head);
			head = head->next;
		}
		return false;
	}

	// Method 2 �޶���ռ� �����޸���ԭ������
	bool hasCycle(ListNode* head) {
		if (!head) return false;

		while (head) {
			if (head->val == INT_MIN) return true;
			head->val = INT_MIN;
			head = head->next;
		}
		return false;
	}

	// Method 3 ����ָ��
	// ��ָ��ÿ���ƶ�һ�� ��ָ��ÿ���ƶ�����
	// �����ָ����׷����ָ�� ˵���л�
	bool hasCycle(ListNode* head) {
		if (!head) return false;
		if (!head->next) return false;

		ListNode* slow = head;
		ListNode* fast = head->next;
		while (slow != fast) {
			if (fast == nullptr || fast->next == nullptr) {
				// ��ָ���Ѿ�������ͷ
				return false;
			}

			slow = slow->next;
			fast = fast->next->next;
		}
		return true;
	}
};