# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。

*/

class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		
		// Method 1 动态规划
		int row_num = obstacleGrid.size(); int col_num = obstacleGrid[row_num - 1].size();

		// 什么奇葩数据
		if (obstacleGrid[0][0] == 1) return 0;

		// dp[i][j]的含义 从start到row=i,col=j的路径的数量
		vector<vector<int>> dp(row_num, vector<int>(col_num));
		dp[0][0] = 1;

		// 初始化第一行和第一列
		for (int col = 1; col < col_num; col++) {
			if (obstacleGrid[0][col] == 1) dp[0][col] = 0; // 若0,col有障碍
			else dp[0][col] = dp[0][col - 1]; // 若0,col故障
		}

		for (int row = 1; row < row_num; row++) {
			if (obstacleGrid[row][0] == 1) dp[row][0] = 0; // 若row,0有障碍
			else dp[row][0] = dp[row - 1][0];
		}


		for (int row = 1; row < row_num; row++) {
			for (int col = 1; col < col_num; col++) {
				if (obstacleGrid[row][col] == 1) dp[row][col] = 0;
				else {
					int up = obstacleGrid[row - 1][col];
					int left = obstacleGrid[row][col - 1];
					if (up == 1 && left == 1) dp[row][col] = 0;
					else if (up == 1 && left == 0) dp[row][col] = dp[row][col - 1];
					else if (up == 0 && left == 1) dp[row][col] = dp[row - 1][col];
					else dp[row][col] = dp[row - 1][col] + dp[row][col - 1];
				}
			}
		}

		return dp[row_num - 1][col_num - 1];
	}
};