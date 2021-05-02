# include <iostream>
# include <vector>
# include <algorithm>
# include <string>

using namespace std;

/*
给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。
*/

class Solution {
public:
	int longestValidParentheses(string s) {
		if (s.empty()) return 0;

		int len_s = s.size();
		// 创建dp数组
		vector<int> dp(len_s, 0);
		int max_valid = 0;
		for (int i = 1; i < len_s; i++) {
			// 不用考虑'(' 因为有效括号串一定以')'结尾
			if (s[i] == ')') {
				if (s[i - 1] == '(') {
					// 与前一个字符刚好匹配
					dp[i] = (i - 2 >= 0 ? dp[i - 2] : 0) + 2;
				}
				else if (i - 1 - dp[i - 1] >= 0 && s[i - 1 - dp[i - 1]] == '(') {
					// 若前一个字符也为')' 考虑以s[i-1]结尾的有效长度 dp[i-1]
					// 这里不仅要考虑 dp[i-1] 还要考虑以s[i-1-dp[i-1]-1]结尾的有效长度 因为可能存在这种情况 ()(())
					dp[i] = dp[i - 1] + 2 + (i - 1 - dp[i - 1] - 1 >= 0 ? dp[i - 1 - dp[i - 1] - 1] : 0);
				}
				if (dp[i] > max_valid) max_valid = dp[i];
			}
		}

		return max_valid;

	}
};

int main() {
	Solution obj;
	string s = "())";
	obj.longestValidParentheses(s);
	
	return 0;
}