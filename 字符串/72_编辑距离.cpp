# include <iostream>
# include <string>
# include <vector>
# include <algorithm>

using namespace std;

/*
给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符

*/

class Solution {
public:
	int minDistance(string word1, string word2) {
		int len_1 = word1.size();
		int len_2 = word2.size();

		if (len_1 == 0) return len_2;
		if (len_2 == 0) return len_1;

		int row_num = len_1 + 1; int col_num = len_2 + 1;
		vector<vector<int>> dp(row_num, vector<int>(col_num));

		// 初始化第0行 第0列
		for (int row = 0; row < row_num; row++) dp[row][0] = row;
		for (int col = 1; col < col_num; col++) dp[0][col] = col;

		for (int row = 1; row < row_num; row++) {
			int pos_1 = row - 1; // 对应word1的下标
			for (int col = 1; col < col_num; col++) {
				int pos_2 = col - 1; // 对应word2的下标
				if (word1[pos_1] == word2[pos_2]) dp[row][col] = dp[row - 1][col - 1];
				// 对应替换操作 删除操作 插入操作
				else dp[row][col] = min({ dp[row - 1][col - 1] + 1, dp[row - 1][col] + 1, dp[row][col - 1] + 1 });
			}
		}

		return dp[len_1][len_2];
	}
};