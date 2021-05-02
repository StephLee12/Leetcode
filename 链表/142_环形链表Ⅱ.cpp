# include <vector>
# include <iostream>
# include <algorithm>
# include <unordered_set>

using namespace std;

/*
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 

如果 pos 是 -1，则在该链表中没有环。注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。

说明：不允许修改给定的链表。

进阶：

你是否可以使用 O(1) 空间解决此题？

*/

struct ListNode
{
	int val;
	ListNode* next;
};

class Solution {
public:
	// Method 1 哈希表
	ListNode* detectCycle(ListNode* head) {
		unordered_set<ListNode*> nodes;
		while (head) {
			if (nodes.count(head)) {
				return head;
			}
			nodes.insert(head);
			head = head->next;
		}
		return nullptr;
	}
	// Method 2 快慢指针
	/*
	设链表头部到环入口有a个结点(不含入口)
	环有b个结点
	fast和slow第一次相遇时
	快指针fast走了f步 慢指针slow走了s步 有
	f=2s
	f=s+nb(相遇必然fast套圈slow)
	解得s=nb
	而入口一定在a+nb的位置
	所以slow指针再走a步即可
	*/
	ListNode* detectCycle(ListNode* head) {
		ListNode* fast = head;
		ListNode* slow = head;

		while (true) {
			if (fast == nullptr || fast->next == nullptr) return nullptr;
			fast = fast->next->next; // 快指针走2步
			slow = slow->next; // 慢指针走1步
			if (fast == slow) break;
		}
		//将fast置为head fast走a步 slow也走a步 相遇即为环的入口
		fast = head;
		while (slow != fast) {
			slow = slow->next;
			fast = fast->next;
		}
		return slow;
	}
};