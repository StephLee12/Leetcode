# include <algorithm>
# include <iostream>
# include <vector>
# include <queue>
# include <unordered_map>

using namespace std;

/*
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制 。
实现 LRUCache 类：

LRUCache(int capacity) 
以正整数作为容量 capacity 初始化 LRU 缓存

int get(int key) 
如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。

void put(int key, int value) 
如果关键字已经存在，则变更其数据值；如果关键字不存在，则插入该组「关键字-值」。
当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，
从而为新的数据值留出空间。

进阶：你是否可以在 O(1) 时间复杂度内完成这两种操作？

*/

// 双向链表
struct DLinkedNode {
	int key, val;
	DLinkedNode* prev;
	DLinkedNode* next;
	// 初始化
	DLinkedNode():key(0),val(0),prev(nullptr),next(nullptr){}
	DLinkedNode(int _key, int _val):key(_key),val(_val),prev(nullptr),next(nullptr){}
};

// 双向链表+哈希表
class LRUCache {
private:
	unordered_map<int, DLinkedNode*> cache;
	DLinkedNode* head;
	DLinkedNode* tail;
	int size;
	int capacity;

public:
	LRUCache(int _capacity):capacity(_capacity),size(0) {
		// 使用伪头部和伪尾部结点
		head = new DLinkedNode();
		tail = new DLinkedNode();
		head->next = tail;
		tail->prev = head;

	}

	int get(int key) {
		if (!cache.count(key)) return -1; // 如果key不存在
		// 如果key存在 用哈希表定位key对应的结点 
		// 由于该结点正在被访问 将其移到链表的头部
		DLinkedNode* node = cache[key];
		moveToHead(node);
		return node->val;
	}

	void put(int key, int value) {
		if (!cache.count(key)) {
			// 如果key不存在 创建一个新的结点
			DLinkedNode* node = new DLinkedNode(key, value);
			cache[key] = node; // 哈希表记录
			addToHead(node); // 新结点添加到链表头部
			size++; // 链表长度+1
			if (size > capacity) {
				// 如果容量爆了 删除链表尾部结点
				DLinkedNode* removed = removeTail();
				// 删除哈希表对应的项
				cache.erase(removed->key);
				// 删除该结点 防止内存泄露
				delete removed;
				size--;
			}
		}
		else {
			// 如果key存在 先修改val 再将其移动到链表头部
			DLinkedNode* node = cache[key];
			node->val = value;
			moveToHead(node);
		}
	}

	// 这几个过程画个图比较清晰
	// 将结点加入双向链表头部
	void addToHead(DLinkedNode* node) {
		node->prev = head; // node的prev指针指向伪头部
		node->next = head->next; // node的next指针指向本来的头部结点
		head->next->prev = node; // 本来头部结点的prev指针指向node
		head->next = node; // 伪头部的next指针指向node
	}

	// 将结点从双向链表删除
	void removeNode(DLinkedNode* node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	// 将结点移至头部 可以分为删除+加入头部
	void moveToHead(DLinkedNode* node) {
		removeNode(node);
		addToHead(node);
	}

	// 删除尾部结点
	DLinkedNode* removeTail() {
		DLinkedNode* node = tail->prev;
		removeNode(node);
		return node;
	}
};