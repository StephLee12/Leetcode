# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
��дһ�������ҵ������������ཻ����ʼ�ڵ�

�����������û�н��㣬���� null.

�ڷ��ؽ���������������뱣��ԭ�еĽṹ��

�ɼٶ���������ṹ��û��ѭ����

���������� O(n) ʱ�临�Ӷȣ��ҽ��� O(1) �ڴ�

*/

struct ListNode
{
	int val;
	ListNode* next;
	ListNode(int x):val(x),next(nullptr){}
};

class Solution {
public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		// Method 1 ˫ָ�� ����ʱ��O(n) �ռ�O(1)
		if (!headA || !headB) return nullptr;

		// �������A��B�ĳ���
		int lenA = 0;
		int lenB = 0;
		auto pA = headA;
		auto pB = headB;
		while (pA) {
			lenA++;
			pA = pA->next;
		}
		while (pB) {
			lenB++;
			pB = pB->next;
		}

		// ������A��B�ĳ����޵�һ��
		pA = headA;
		pB = headB;
		if (lenA < lenB) {
			while (lenB != lenA) {
				pB = pB->next;
				lenB--;
			}
		}
		else if (lenA > lenB) {
			while (lenA != lenB) {
				pA = pA->next;
				lenA--;
			}
		}

		while (pA) {
			if (pA == pB) return pA; // ���ָ����ͬ ˵��������������
			pA = pA->next;
			pB = pB->next;
		}

		return nullptr;
	}
};