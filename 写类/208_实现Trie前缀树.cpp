# include <string>

using namespace std;

/*
Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。

这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

请你实现 Trie 类：

Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

*/

class Trie {
public:
	bool isEnd;
	Trie* children[26];

	/** Initialize your data structure here. */
	Trie() {
		isEnd = false;
		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
		}
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		Trie* tree = this;
		for (char c : word) {
			if (tree->children[c - 'a'] == nullptr) {
				// 如果字典树中没有c的键 新建
				tree->children[c - 'a'] = new Trie();
			}
			// 移动指针
			tree = tree->children[c - 'a'];
		}
		tree->isEnd = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		Trie* tree = this;
		for (char c : word) {
			if (tree->children[c - 'a'] == nullptr) {
				return false;
			}
			tree = tree->children[c - 'a'];
		}
		return tree->isEnd;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		Trie* tree = this;
		for (char c : prefix) {
			if (tree->children[c - 'a'] == nullptr) {
				return false;
			}
			tree = tree->children[c - 'a'];
		}
		return true;
	}
};