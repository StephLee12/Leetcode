# include <string>
# include <iostream>
# include <vector>
# include <algorithm>
# include <unordered_set>

using namespace std;


/*
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。

如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。

*/

class Solution {
public:
	string minWindow(string s, string t) {
		// Method 1 滑动窗口
		vector<int>dict(128, 0); // 用vec充当哈希表 记录每个字符出现的次数
		for (char c : t) dict[c]++; // 将串t中的元素计入哈希表

		int cnt = t.size();
		// l_p记录窗口左侧 r_p记录窗口右侧 start_pos记录最短串的左端 min_len记录最短串的长度
		int l_p = 0, r_p = 0, start_pos = 0, min_len = INT_MAX;
		while (r_p < s.size()) {
			char c = s[r_p];
			if (dict[c] > 0) cnt--; // 如果c是t中的字符 cnt--
			dict[c]--; // 将当前元素加入窗口

			if (cnt == 0) { // 如果当前窗口中已经包含t
				while (l_p < r_p && dict[s[l_p]] < 0) {
					// 移动l_p 缩减窗口（移除不是t中的字符）
					dict[s[l_p]]++;
					l_p++;
				}
				// 记录当前窗口的长度 与最小长度比较
				if (r_p - l_p + 1 < min_len) {
					min_len = r_p - l_p + 1;
					start_pos = l_p;
				}
				// 改变当前窗口的左端 进入下一个循环 继续向右扩充窗口
				dict[s[l_p]]++;
				l_p++;
				cnt++;
			}
			r_p++;
		}

		return min_len == INT_MAX ? "" : s.substr(start_pos, min_len);
	}
};