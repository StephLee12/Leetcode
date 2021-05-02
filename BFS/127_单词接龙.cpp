# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include <unordered_set>
# include <queue>

using namespace std;

/*
字典 wordList 中从单词 beginWord 和 endWord 的 转换序列 是一个按下述规格形成的序列：

序列中第一个单词是 beginWord 。
序列中最后一个单词是 endWord 。
每次转换只能改变一个字母。
转换过程中的中间单词必须是字典 wordList 中的单词。
给你两个单词 beginWord 和 endWord 和一个字典 wordList ，找到从 beginWord 到 endWord 的 最短转换序列中的单词数目 。
如果不存在这样的转换序列，返回 0

*/

class Solution {

public:
	// Method 1 单向BFS
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		// method 1 直接暴力bfs 注意这里用到了set这种数据结构 
		// 建图 将该问题转换为无向图中求两点间最短路径的问题 可以转换的两个单词形成连边

		// 转换为集合
		unordered_set<string> word_set(wordList.begin(), wordList.end());
		if (word_set.empty() || word_set.find(endWord) == word_set.end()) return 0; // find()函数如果没找到 返回set末尾的迭代器

		queue<string> q;
		q.push(beginWord);
		word_set.erase(beginWord); // 入队之后就要在set中删除 以免重复遍历

		int path_cnt = 1; // 遍历的路径长

		while (!q.empty()) {
			int now_cnt = q.size(); // 当前层的结点数
			for (int i = 1; i <= now_cnt; i++) {
				string s = q.front();
				q.pop();

				vector<string> tmp; // 存储遍历到下一层的结点

				// 遍历version 1 遍历set 将可以转换的加入tmp 这里遍历set时间开销有点大
				// 这种遍历形式 可以记一下 对于这种数据结构的遍历 如vector set等
				// 这里遍历 相当于是找所有与s相连的单词 找到之后要在word_set中删除 避免同一单词多次入队
				// 因此这里用一个vector tmp保存 下面在word_set中删除
				//for (const string& word : word_set) {
				//	if (can_transit(s, word)) {
				//		// 判断两个串能否交换
				//		if (word == endWord) return path_cnt + 1;
				//		tmp.push_back(word);
				//		q.push(word);
				//	}
				//}

				// 遍历version 2 将当前单词变为其它25个单词 然后在set中查找 因为set是用红黑树实现的 效率高
				// version 2的速度要快很多
				for (int i = 0; i < s.size(); i++) {
					char ori_word = s[i]; // 字符串s在位置i的字母
					for (int j = 0; j < 26; j++) {
						// 更换ori_word为其它25个字母
						if (char('a' + j) == ori_word) continue;
						s[i] = (char)('a' + j);// 更换该字母后的字符串
						if (s == endWord) return path_cnt + 1;
						if (word_set.find(s) != word_set.end()) {
							// 如果更换后的字符串能在word_set中找到
							q.push(s);
							tmp.push_back(s);
						}
					}
					s[i] = ori_word; // 遍历完其它25个单词后恢复原来的单词
				}
				// 要删除tmp中的结点 防止二次遍历
				for (auto&& s : tmp) word_set.erase(s);
			}

			path_cnt++; // 进入下一层遍历
		}

		return 0;
	}
	
	// 检验两个字符串能否从转换
	bool can_transit(const string& a, const string& b) {
		int non_match = 0;
		for (int i = 0; i < a.size(); i++) {
			if (a[i] != b[i]) non_match++;
			if (non_match > 1) return false;
		}
		return non_match == 1;
	}


	// Method 2 双向BFS
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		
		unordered_set<string> word_set(wordList.begin(), wordList.end());
		if (word_set.empty() || word_set.find(endWord) == word_set.end()) return 0; // find()函数如果没找到 返回set末尾的迭代器
		
		// 设置双向BFS搜索
		// 这里哈希表存储已经遍历过的string 双向不太好直接在word_set中erase 因为要判断双向相遇
		unordered_set<string> visited_begin;
		visited_begin.insert(beginWord);
		unordered_set<string> visited_end;
		visited_end.insert(endWord);

		queue<string> begin_q;
		begin_q.push(beginWord);
		queue<string> end_q;
		end_q.push(endWord);

		int level_cnt = 1;
		while (!begin_q.empty() && !end_q.empty()) {
			// 永远让begin_q中的元素最少 如果begin_q中的多 就交换 即交替搜索
			if (begin_q.size() > end_q.size()) {
				visited_begin.swap(visited_end);
				begin_q.swap(end_q);
			}

			// 下面的操作和单向BFS相同
			int now_cnt = begin_q.size();
			for (int i = 1; i <= now_cnt; i++) {
				string s = begin_q.front();
				begin_q.pop();

				for (int i = 0; i < s.size(); i++) {
					char ori_word = s[i];
					for (int j = 0; j < 26; j++) {
						s[i] = (char)('a' + j);
						if (visited_begin.find(s) != visited_begin.end()) continue;
						if (visited_end.find(s) != visited_end.end()) return level_cnt + 1;
						if (word_set.find(s) != word_set.end()) {
							visited_begin.insert(s);
							begin_q.push(s);
						}
					}
					s[i] = ori_word;
				}

			}
			level_cnt++;
		}
		return 0;
	}

};