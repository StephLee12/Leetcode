# include <iostream>
# include <vector>
# include <stack>
# include <algorithm>

using namespace std;


// Method 1 用一个栈保存入栈元素 同时维护一个升序链表
/*
这个做法 栈完全就是个摆设
*/

struct Node {
	long long val;
	Node* next;
	Node() :val(0), next(nullptr) {}
	Node(long long x) :val(x), next(nullptr) {}
	Node(long long x, Node* node) :val(x), next(node) {}
};

class MinStack {
private:
	stack<int> stk;
	Node* head = new Node((long long)INT_MIN - 1);
public:
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int val) {
		stk.push(val);
		// 将结点插入链表
		Node* node = new Node((long long)(val));
		addToList(node);
	}

	void addToList(Node* node) {
		auto p = head;
		auto prev_p = head;
		while (p) {
			if (p->val <= node->val) {
				prev_p = p;
				p = p->next;
			}
			else break;
		}
		// 进行插入
		node->next = p;
		prev_p->next = node;
	}

	void pop() {
		int val = this->top();
		stk.pop();
		delNode((long long)(val));
	}

	void delNode(long long val) {
		auto p = head;
		auto prev_p = head;
		while (true) {
			if (p->val == val) break;
			prev_p = p;
			p = p->next;
		}
		prev_p->next = p->next;
		p->next = nullptr;
	}

	int top() {
		return stk.top();
	}

	int getMin() {
		return (int)(head->next->val);
	}
};

// Method 2 直接采用一个链表 不断头插(相当于栈) 同时维护一个最小元素
class MinStack {
private:
	struct Node {
		int val; // 当前结点的值
		int min; // 以该结点为栈顶的最小元素的值
		Node* next;
		Node(int x,int y):val(x),min(y),next(nullptr){}
		Node(int x, int y,Node* next):val(x),min(y),next(next){}
	};

	Node* head;
public:
	/** initialize your data structure here. */
	MinStack() {
		head = nullptr;
	}

	void push(int val) {
		if (head == nullptr) head = new Node(val, val);
		else {
			// 维护最小元素
			Node* node = new Node(val, min(val, head->min));
			// 链表头插
			node->next = head;
			head = node;
		}
	}

	void pop() {
		head = head->next;
	}

	int top() {
		return head->val;
	}

	int getMin() {
		return head->min;
	}
};