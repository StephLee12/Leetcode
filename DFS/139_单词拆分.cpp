# include <vector>
# include <iostream>
# include <algorithm>
# include <unordered_set>

using namespace std;

/*
给定一个非空字符串 s 和一个包含非空单词的列表 wordDict，

判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

说明：

拆分时可以重复使用字典中的单词。
你可以假设字典中没有重复的单词。

*/

class Solution {
public:
	// Method 1 动态规划
	bool wordBreak(string s, vector<string>& wordDict) {
		
		unordered_set<string> w_set(wordDict.begin(), wordDict.end()); // 将字典vector装入set 便于查找

		int len = s.size();
		vector<int> dp(len);
		for (int i = 0; i < len; i++) {
			string tmp_s = s.substr(0, i + 1);
			if (w_set.find(tmp_s) != w_set.end()) {
				// 如果从0到i到字符串在集合中
				dp[i] = 1;
			}
			else {
				// 如果不在集合中
				// 向前搜索 对于从0到j到字符串在集合中的位置
				// 判断从j+1到i的字符串是否在集合内
				int j = i - 1;
				while (j >= 0) {
					if (dp[j] == 1) {
						string tmp = s.substr(j + 1, i - j);
						dp[i] |= (w_set.find(tmp) != w_set.end());
					}
					j--;
				}
			}
		}

		return dp[len - 1];
	}

	// Method 2 dfs递归+记忆化回溯
	bool wordBreak(string s, vector<string>& wordDict) {
		int len = s.size();
		unordered_set<string> w_set(wordDict.begin(), wordDict.end());

		// 存储从i到字符串末尾是否能被字典切分
		vector<int> memo(len, -1); // 初始值为-1
		return dfs(s, w_set, memo, 0);
	}

	bool dfs(const string& s, unordered_set<string>& w_set, vector<int>& memo, int begin) {
		// dfs判断从begin到s.size()是否能被字典切分

		// 边界情况 如果begin超过边界 直接返回true
		if (begin > s.size() - 1) return true;
		// 记忆化回溯 如果该位置已经被遍历过 直接返回它对应的bool值
		if (memo[begin] != -1) return memo[begin];

		for (int end = begin; end < s.size(); end++) {
			string tmp_s = s.substr(begin, end - begin + 1);
			// 将问题拆解为从begin到end是否在集合中 从end到s.size()是否在集合中
			if ((w_set.find(tmp_s) != w_set.end()) && dfs(s, w_set, memo, end + 1)) {
				memo[begin] = 1;
				return true;
			}
		}

		memo[begin] = 0;
		return false;
	}
};