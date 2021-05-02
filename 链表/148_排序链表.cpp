# include <vector>
# include <algorithm>
# include <iostream>

using namespace std;

/*
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

进阶：

你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
 
*/

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
	// Method 1 暴力 遍历+排序+修改遍历
	ListNode* sortList(ListNode* head) {
		if (!head) return nullptr;

		vector<int> vals;
		ListNode* p = head;
		while (p) {
			vals.push_back(p->val);
			p = p->next;
		}

		sort(vals.begin(), vals.end());
		p = head;
		for (auto&& val : vals) {
			p->val = val;
			p = p->next;
		}

		return head;
	}
	 
	// Method 2 归并排序 若要常数的空间复杂度 则不能递归 采用自底向上的迭代
	/*
	将步长不断扩大 切割链表 进行归并
	*/
	ListNode* sortList(ListNode* head) {
		ListNode* dummyHead = new ListNode(0);
		dummyHead->next = head;

		auto p = head;
		int lstLen = 0;
		// 得到链表的长度
		while (p) {
			lstLen++;
			p = p->next;
		}

		for (int len = 1; len < lstLen; len *= 2) {
			// 初始化当前结点 和链表尾部结点
			auto curNode = dummyHead->next;
			auto tail = dummyHead;

			while (curNode) {
				auto left = curNode; 
				// len是切割的长度
				auto right = cut(left,len); // 这条语句将left切割下来
				curNode = cut(right, len); // 这条语句将right切割下来

				// 注意curNode和right之间是断开连接的
				// 将链表的尾部的next先指向归并后的链表头部
				tail->next = merge(left, right); // 归并left和right
				// 移动tail 将其移动到归并后的链表尾部
				while (tail->next) tail = tail->next;
			}
		}

		return dummyHead->next;
	}

	// 断链 切掉链表head的前len个结点 并返回后半部分的链表头
	ListNode* cut(ListNode* head, int len) {
		auto p = head;

		// --len是先执行len自减 再使用len的值
		while (--len && p) p = p->next;

		if (!p) return nullptr; // 如果p为空 则返回空指针

		auto next = p->next;
		p->next = nullptr; // 切除后半部分和前半部分的连接
		return next; // 返回后半部分的结点头
	}

	ListNode* merge(ListNode* l1, ListNode* l2) {
		ListNode* dummmyHead = new ListNode(0);
		auto p = dummmyHead;

		while (l1 && l2) {
			if (l1->val <= l2->val) {
				p->next = l1;
				p = l1;
				l1 = l1->next;
			}
			else {
				p->next = l2;
				p = l2;
				l2 = l2->next;
			}
		}
		if (l1) p->next = l1;
		if (l2) p->next = l2;

		return dummmyHead->next;
	}

	// Method 3 归并排序 递归 空间复杂度不为常数
	// 使用快慢指针寻找链表的中点 当快指针到头时 慢指针到达中点
	ListNode* sortList(ListNode* head) {
		if (!head) return nullptr;
		return mergeSort(head);
	}

	ListNode* mergeSort(ListNode* head) {
		if (!head->next) return head; // 如果链表为空 或链表长度为1 不需要排序

		auto fast = head;
		auto slow = head;
		auto pre_slow = head; // slow结点的前驱结点 以便断开以slow为链表头的链表 和之前的链表的连接
		while (fast && fast->next) {
			pre_slow = slow;
			slow = slow->next;
			fast = fast->next->next;
		}

		pre_slow->next = nullptr;
		ListNode* left = mergeSort(head);
		ListNode* right = mergeSort(slow);
		return merge(left, right);
	}

	ListNode* merge(ListNode* l1, ListNode* l2) {
		ListNode* dummmyHead = new ListNode(0);
		auto p = dummmyHead;

		while (l1 && l2) {
			if (l1->val <= l2->val) {
				p->next = l1;
				p = l1;
				l1 = l1->next;
			}
			else {
				p->next = l2;
				p = l2;
				l2 = l2->next;
			}
		}
		if (l1) p->next = l1;
		if (l2) p->next = l2;

		return dummmyHead->next;
	}
};