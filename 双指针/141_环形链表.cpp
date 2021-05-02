# include <iostream>
# include <vector>
# include <algorithm>
# include <unordered_set>

using namespace std;

/*
给定一个链表，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。

如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

如果链表中存在环，则返回 true 。 否则，返回 false 。

进阶：

你能用 O(1)（即，常量）内存解决此问题吗

*/


struct ListNode {
	int val;
	ListNode* next;
};

class Solution {
public:
	// Method 1 用set存储node的地址
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

	// Method 2 无额外空间 但是修改了原来链表
	bool hasCycle(ListNode* head) {
		if (!head) return false;

		while (head) {
			if (head->val == INT_MIN) return true;
			head->val = INT_MIN;
			head = head->next;
		}
		return false;
	}

	// Method 3 快慢指针
	// 慢指针每次移动一步 快指针每次移动两步
	// 如果快指针能追上慢指针 说明有环
	bool hasCycle(ListNode* head) {
		if (!head) return false;
		if (!head->next) return false;

		ListNode* slow = head;
		ListNode* fast = head->next;
		while (slow != fast) {
			if (fast == nullptr || fast->next == nullptr) {
				// 快指针已经到链表尽头
				return false;
			}

			slow = slow->next;
			fast = fast->next->next;
		}
		return true;
	}
};