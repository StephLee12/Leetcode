# include <algorithm>
# include <vector>
# include <iostream>

using namespace std;


/*
给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。
*/

class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		// Method 1 动态规划 这种题 是medium？
		int row_num = grid.size(); int col_num = grid[row_num - 1].size();

		vector<vector<int>> dp(row_num, vector<int>(col_num));
		dp[0][0] = grid[0][0];

		// 由于每次只能向下或向右移动一步 所以可以初始化第一行和第一列
		for (int row = 1; row < row_num; row++) dp[row][0] = grid[row][0] + dp[row - 1][0];
		for (int col = 1; col < col_num; col++) dp[0][col] = grid[0][col] + dp[0][col - 1];

		for (int row = 1; row < row_num; row++) {
			for (int col = 1; col < col_num; col++) {
				int up = dp[row - 1][col]; int left = dp[row][col - 1];
				if (up <= left) dp[row][col] = grid[row][col] + up;
				else dp[row][col] = grid[row][col] + left;
			}
		}

		return dp[row_num - 1][col_num - 1];
	}
};