# include <iostream>
# include <vector>
# include <algorithm>
# include <string>

using namespace std;

/*
给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。

'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）。
两个字符串完全匹配才算匹配成功。

说明:

s 可能为空，且只包含从 a-z 的小写字母。
p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *
*/


// 该题与第10题 正则表达式匹配相似
class Solution {
public:
	bool isMatch(string s, string p) {
		// Method 1 动态规划
		
		if (s.empty() && p.empty()) return true;
		if (!s.empty() && p.empty()) return false;

		int s_len = s.length();
		int p_len = p.length();
		int row_num = s.length() + 1;
		int col_num = p.length() + 1;

		// 创建dp数组 dp[i][j]的含义是p的前j个字符能否匹配s的前i个字符
		vector<vector<bool>> dp(row_num, vector<bool>(col_num, false));
		// 初始化dp数组的第一行
		dp[0][0] = true;
		for (int col_idx = 1; col_idx < col_num; col_idx++) {
			int p_idx = col_idx - 1;
			if (p[p_idx] == '*') dp[0][col_idx] = dp[0][col_idx - 1];
		}

		for (int row_idx = 1; row_idx < row_num; row_idx++) {
			int s_idx = row_idx - 1;
			for (int col_idx = 1; col_idx < col_num; col_idx++) {
				int p_idx = col_idx - 1;

				// 当前主串和模式串的字符可以直接匹配
				if (s[s_idx] == p[p_idx] || p[p_idx]=='?') {
					dp[row_idx][col_idx] = dp[row_idx - 1][col_idx - 1];
				}
				else if (p[p_idx] == '*') {
					if (p_idx - 1 < 0) {
						// 这里要考虑p_idx-1是否越界 因为"*"可能会出现在p的串首
						// "*"可以匹配任意字符串
						dp[row_idx][col_idx] = true;
					}
					else if (dp[row_idx][col_idx-1]) {
						// 该字符匹配空串
						dp[row_idx][col_idx] = true;
					}
					else {
						// 该字符匹配至少一个字符
						for (int i = row_idx-1; i >= 0; i--) {
							if (dp[i][col_idx - 1]) {
								// 寻找p的前col_idx-1个字符是否能够与s的前i个字符匹配
								// 如果有 则说明"*"可以匹配s的i+1到row_idx个字符
								dp[row_idx][col_idx] = true;
								break;
							}
						}
					}
				}

				
			}
		}
		return dp[row_num - 1][col_num - 1];
	}

	bool isMatch(string s, string p) {
		// 动态规划 优化
		if (s.empty() && p.empty()) return true;
		if (!s.empty() && p.empty()) return false;

		int s_len = s.length();
		int p_len = p.length();
		int row_num = s.length() + 1;
		int col_num = p.length() + 1;

		// 创建dp数组 dp[i][j]的含义是p的前j个字符能否匹配s的前i个字符
		vector<vector<bool>> dp(row_num, vector<bool>(col_num, false));
		// 初始化dp数组的第一行
		dp[0][0] = true;
		for (int col_idx = 1; col_idx < col_num; col_idx++) {
			int p_idx = col_idx - 1;
			if (p[p_idx] == '*') dp[0][col_idx] = true;
			else break;
		}

		for (int row_idx = 1; row_idx < row_num; row_idx++) {
			int s_idx = row_idx - 1;
			for (int col_idx = 1; col_idx < col_num; col_idx++) {
				int p_idx = col_idx - 1;

				if (s[s_idx] == p[p_idx] || p[p_idx] == '?') {
					// 当前主串和模式串的字符可以直接匹配
					dp[row_idx][col_idx] = dp[row_idx - 1][col_idx - 1];
				}
				else if (p[p_idx] == '*') {
					// 右值第一项表示 '*'匹配空字符串 第二项表示"*"匹配若干字符
					dp[row_idx][col_idx] = dp[row_idx][col_idx-1] || dp[row_idx-1][col_idx];
					
				}

			}
		}
		return dp[row_num - 1][col_num - 1];
	}
};

int main() {
	Solution obj;
	string s = "aa";
	string p = "*";
	bool res = obj.isMatch(s, p);
	if (res) {
		return 1;
	}
	else {
		return 0;
	}
}