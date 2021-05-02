# include <iostream>
# include <vector>
# include <stack>
# include <algorithm>

using namespace std;


// Method 1 ��һ��ջ������ջԪ�� ͬʱά��һ����������
/*
������� ջ��ȫ���Ǹ�����
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
		// ������������
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
		// ���в���
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

// Method 2 ֱ�Ӳ���һ������ ����ͷ��(�൱��ջ) ͬʱά��һ����СԪ��
class MinStack {
private:
	struct Node {
		int val; // ��ǰ����ֵ
		int min; // �Ըý��Ϊջ������СԪ�ص�ֵ
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
			// ά����СԪ��
			Node* node = new Node(val, min(val, head->min));
			// ����ͷ��
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