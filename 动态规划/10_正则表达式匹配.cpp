# include <iostream>
# include <vector>
# include <string>
# include <algorithm>

using namespace std;


/*
给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素

所谓匹配，是要涵盖 整个 字符串 s的，而不是部分字符串。
*/

class Solution {
public:
	bool isMatch(string s, string p) {
		// Method 1 动态规划
		// s是主串 p是模式串
		if (p.empty() && s.empty()) return true; // 两个串均为空
		if (p.empty() && !s.empty()) return false; // 主串非空 模式串空
		// 注意 若s为空不能直接返回 因为p中存在*可以抵消字母
		int len_s = s.length();
		int len_p = p.length();

		// 创建dp数组 注意多增加了一行一列 并初始化为false
		// dp[i][j]含义是s的前i个字符与p的前j个字符是否匹配
		vector<vector<bool>> dp(len_s+1, vector<bool>(len_p+1, false));
		// 初始化dp数组第一行 s为空时p的匹配情况
		dp[0][0] = true;
		for (int j = 1; j < len_p+1; j++) {
			if (j % 2 == 0 && p[j - 1] == '*') {
				dp[0][j] = dp[0][j - 2];
			}
		}

		// 注意循环条件的设置
		for (int i = 1; i < len_s + 1; i++) {
			for (int j = 1; j < len_p+1; j++) {
				// 可以直接匹配
				if (s[i-1] == p[j-1] || p[j-1] == '.') {
					dp[i][j] = dp[i - 1][j - 1];
				}
				else if (p[j-1] == '*') {
					if (p[j - 1-1] == s[i-1] || p[j - 1-1] == '.') {
						// 下式的右值 第一项'*'代表一个或多个字符 第二项'*'不代表任何字符
						dp[i][j] = dp[i - 1][j] || dp[i][j - 2];
					}
					else {
						// '*'和'*'前面的字符不代表任何字符
						dp[i][j] = dp[i][j - 2];
					}
				}
				else {
					dp[i][j] = false;
				}
			}
		}

		return dp[len_s][len_p];

	}
};