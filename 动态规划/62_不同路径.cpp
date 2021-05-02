# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？
*/

class Solution {
public:
	int uniquePaths(int m, int n) {
		// dp[i][j]的含义 从start到dp[i][j]的不同路径
		vector<vector<int>> dp(m, vector<int>(n, 0));
		// 初始化第1列
		for (int row = 0; row < m; row++) {
			dp[row][0] = 1;
		}
		// 初始化第1行
		for (int col = 1; col < n; col++) {
			dp[0][col] = 1;
		}

		for (int row = 1; row < m; row++) {
			for (int col = 1; col < n; col++) {
				dp[row][col] = dp[row - 1][col] + dp[row][col - 1];
			}
		}

		return dp[m - 1][n - 1];
	}
};