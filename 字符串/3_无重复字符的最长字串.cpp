# include <iostream>
# include <string>
# include <unordered_set>
# include <algorithm>
# include <unordered_map>

using namespace std;

/*
给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度
*/

class Solution {
public:
	//// Method 1 纯暴力 用set记录 双重循环
	//int lengthOfLongestSubstring(string s) {
	//	
	//	int len = s.size();

	//	if (len == 0) return 0;
	//	
	//	int max_len = 1;
	//	unordered_set<char> records;
	//	for (int i = 0; i < len-1; i++) {
	//		records.insert(s[i]);
	//		for (int j = i + 1; j < len;j++) {
	//			if (records.find(s[j]) == records.end()) records.insert(s[j]);
	//			else break;
	//		}
	//		max_len = max(max_len, (int)(records.size()));
	//		records.clear();
	//	}
	//	return max_len;
	//}

	//// Method 2 用哈希表 存储出现的字符 从而判断重复字符
	//int lengthOfLongestSubstring(string s) {
	//	
	//	int len = s.size();
	//	// 只需要记录出现重复字符的较前位置即可 =>用哈希表
	//	int start_pos = 0;  // 当前字符串的起始下标 
	//	int max_len = 0;
	//	unordered_map<char, int> record; // 记录重复字符出现的位置

	//	for (int i = 0; i < len; i++) {
	//		char c = s[i];
	//		if (record.find(c) != record.end() && record[c] >= start_pos) {
	//			// 当出现重复字符(record.find(c) != record.end())且该字符位于当前字符串中(record[c]>=start_pos)
	//			// 从较前的一个字符位置+1 继续搜索
	//			start_pos = record[c] + 1; 
	//			record[c] = i; // 更新字符c出现的最新位置
	//		}
	//		else {
	//			// 若未出现重复字符 不断搜索 
	//			record[c] = i; // 记录字符c出现的位置
	//			max_len = max(max_len, i - start_pos + 1); // 更新max_len
	//		}
	//	}
	//	return max_len;
	//}

	// Method 3 滑动窗口
	int lengthOfLongestSubstring(string s) {
		
		if (s.size() == 0) return 0;

		int max_len = 1;
		int l_p = 0, r_p = 0;

		vector<int> dict(128, 0); // 记录字符出现的次数

		while (r_p < s.size()) {
			char c = s[r_p];
			if (dict[c] == 0) {
				// 如果当前元素在之前没有重复 将其加入窗口
				dict[c]++;
			}
			else { // dict[c]!=0
				// 遇到了重复元素 缩减窗口
				while (s[l_p] != c) {
					// 移动l_p 直到遇到与c相等的字符
					dict[s[l_p]]--;
					l_p++;
				}
				// 移动当前窗口的左端
				dict[s[l_p]]--;
				l_p++;
				dict[c]++;
			}
			max_len = max(max_len, r_p - l_p + 1);
			r_p++;
		}

		return max_len;
	}

};

int main() {
	string test = "abcabcbb";
	Solution obj;
	obj.lengthOfLongestSubstring(test);
	return 0;
}