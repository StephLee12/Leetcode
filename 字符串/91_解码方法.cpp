# include <iostream>
# include <vector>
# include <string>
# include <cstring>
# include <algorithm>

using namespace std;

/*
A message containing letters from A-Z can be encoded into numbers using the following mapping:

To decode an encoded message, all the digits must be grouped then mapped back into letters using the reverse of the mapping above (there may be multiple ways). For example, "11106" can be mapped into:

"AAJF" with the grouping (1 1 10 6)
"KJF" with the grouping (11 10 6)
Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' since "6" is different from "06".

Given a string s containing only digits, return the number of ways to decode it.

The answer is guaranteed to fit in a 32-bit integer.

*/

class Solution {
public:
	int numDecodings(string s) {
		// Method 1 一维动态规划
		int len = s.size();

		if (s[0] == '0') return 0;
		vector<int> dp(len);
		// 逆序进行动态规划
		dp[len - 1] = (s[len - 1] == '0' ? 0 : 1);

		for (int i = len - 2; i >= 0; i--) {
			// 判断当前位置的字符和其前一个(对于逆序来说)的关系
			char now = s[i]; char next = s[i + 1];
			if (now == '0') continue; // 如果当前位置的digit为0 则无法解码
			else {
				// 当前digit不为0
				if (dp[i + 1] != 0) {
					// 如果其前一个digit不为0 则一种解码方式为 当前digit单独解码 
					dp[i] += dp[i + 1];
				}
				// 另一种解码方式是now和next组合解码 要判断string{now,next}的合法性
				if (i + 2 <= len - 1) {
					if (dp[i + 2] != 0) dp[i] += (stoi(string{ now,next }) <= 26 ? dp[i+2] : 0);
				}
				else dp[i] += (stoi(string{ now,next }) <= 26 ? 1 : 0);
			}
		}
		return dp[0];
	}
};


int main() {
	string test = "27";
	Solution obj;
	obj.numDecodings(test);
	return 0;
}