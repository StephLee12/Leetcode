# include <iostream>
# include <vector>
# include <algorithm>
# include <string>

using namespace std;

/*
����һ��ֻ���� '(' �� ')' ���ַ������ҳ����Ч����ʽ��ȷ�������������Ӵ��ĳ��ȡ�
*/

class Solution {
public:
	int longestValidParentheses(string s) {
		if (s.empty()) return 0;

		int len_s = s.size();
		// ����dp����
		vector<int> dp(len_s, 0);
		int max_valid = 0;
		for (int i = 1; i < len_s; i++) {
			// ���ÿ���'(' ��Ϊ��Ч���Ŵ�һ����')'��β
			if (s[i] == ')') {
				if (s[i - 1] == '(') {
					// ��ǰһ���ַ��պ�ƥ��
					dp[i] = (i - 2 >= 0 ? dp[i - 2] : 0) + 2;
				}
				else if (i - 1 - dp[i - 1] >= 0 && s[i - 1 - dp[i - 1]] == '(') {
					// ��ǰһ���ַ�ҲΪ')' ������s[i-1]��β����Ч���� dp[i-1]
					// ���ﲻ��Ҫ���� dp[i-1] ��Ҫ������s[i-1-dp[i-1]-1]��β����Ч���� ��Ϊ���ܴ���������� ()(())
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