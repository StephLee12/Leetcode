# include <algorithm>
# include <string>
# include <iostream>
# include <vector>

using namespace std;

// 找到s中最长回文子串并返回

class Solution {
public:
	string longestPalindrome(string s) {
		
		// Method 1 动态规划
		int len = s.length();

		if (len == 1) return s;

		// 创建dp数组 dp[i][j]表示从第i+1个字符到第j+1个字符是否是回文串
		vector<vector<int>> dp(len,vector<int>(len,0));

		for (int i = 0; i < len; i++) dp[i][i] = 1; // 一个字符自身显然是回文串

		int max_len = 1;
		int start_pos = 0;
		// 寻找最长回文串 时间复杂度n^2
		// 循环的设置 要考虑dp的填表顺序 即dp[i][j]=dp[i+1][j-1]的合法性
		for (int j = 0; j < len;j++) {
			for (int i = 0; i <= j;i++) {
				if (s[i] == s[j]) {
					// 若s[i]==s[j] 考虑s[i+1:j-1]是否是回文串 同时要考虑区间边界不能越过 即j-1>=i+1
					if (j - i >= 2) dp[i][j] = dp[i+1][j-1];
					else dp[i][j] = 1;

					// 如果dp[i][j]==1
					// 计算当前子串的长度是否最大
					if (dp[i][j]) {
						int cur_len = j - i + 1;
						if (cur_len > max_len) {
							max_len = cur_len;
							start_pos = i;
						}
					}

				}
			}
		}

		return s.substr(start_pos, max_len);

	}
};