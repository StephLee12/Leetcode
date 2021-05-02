# include <iostream>
# include <vector>
# include <string>
# include <algorithm>

using namespace std;

/*
给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。

字符串的一个 子序列 是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。

（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）

题目数据保证答案符合 32 位带符号整数范围。

*/


class Solution {
public:
	int numDistinct(string s, string t) {
		int len_s = s.size(); int len_t = t.size();
		if (len_s < len_t) return 0;
		if (len_s == 0 && len_t == 0) return 1;

		// dp[i][j]表示t的前j个字符 在s的前i个字符中出现的次数
		vector<vector<unsigned int>> dp(len_s + 1, vector<unsigned int>(len_t + 1));
		// 初始化
		dp[0][0] = 1;
		for (int i = 1; i <= len_s; i++) dp[i][0] = 1;
		for (int i = 1; i <= len_t; i++) dp[0][i] = 0;

		// dp[i][j] 表示                                          
		for (int i = 1; i <= len_s; i++) {
			for (int j = 1; j <= len_t; j++) {
				// 若当前位置s的字符与t的不相等 则继承s前一个字符的dp值
				if (s[i - 1] != t[j - 1]) dp[i][j] = dp[i - 1][j];
				// 如果当前位置相等 既要计算 不算当前的字符有多少次数dp[i-1][j] 也要计算考虑当前字符 统计其前缀出现次数dp[i-1][j-1]
				else dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
			}
		}
		// 用unsigned int 防止中途计算爆掉
		return (int)(dp[len_s][len_t]);
	}
};