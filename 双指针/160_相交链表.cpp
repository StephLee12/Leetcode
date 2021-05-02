# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
编写一个程序，找到两个单链表相交的起始节点

如果两个链表没有交点，返回 null.

在返回结果后，两个链表仍须保持原有的结构。

可假定整个链表结构中没有循环。

程序尽量满足 O(n) 时间复杂度，且仅用 O(1) 内存

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
		// Method 1 双指针 满足时间O(n) 空间O(1)
		if (!headA || !headB) return nullptr;

		// 获得链表A和B的长度
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

		// 将链表A和B的长度修到一致
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
			if (pA == pB) return pA; // 如果指针相同 说明两个链表相遇
			pA = pA->next;
			pB = pB->next;
		}

		return nullptr;
	}
};