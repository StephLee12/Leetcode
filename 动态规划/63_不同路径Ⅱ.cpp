# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б��Ϊ��Start�� ����

������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ��������½ǣ�����ͼ�б��Ϊ��Finish������

���ڿ������������ϰ����ô�����Ͻǵ����½ǽ����ж�������ͬ��·����

�����е��ϰ���Ϳ�λ�÷ֱ��� 1 �� 0 ����ʾ��

*/

class Solution {
public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
		
		// Method 1 ��̬�滮
		int row_num = obstacleGrid.size(); int col_num = obstacleGrid[row_num - 1].size();

		// ʲô��������
		if (obstacleGrid[0][0] == 1) return 0;

		// dp[i][j]�ĺ��� ��start��row=i,col=j��·��������
		vector<vector<int>> dp(row_num, vector<int>(col_num));
		dp[0][0] = 1;

		// ��ʼ����һ�к͵�һ��
		for (int col = 1; col < col_num; col++) {
			if (obstacleGrid[0][col] == 1) dp[0][col] = 0; // ��0,col���ϰ�
			else dp[0][col] = dp[0][col - 1]; // ��0,col����
		}

		for (int row = 1; row < row_num; row++) {
			if (obstacleGrid[row][0] == 1) dp[row][0] = 0; // ��row,0���ϰ�
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