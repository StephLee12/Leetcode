# include <algorithm>
# include <vector>
# include <iostream>

using namespace std;


/*
����һ�������Ǹ������� m x n ���� grid �����ҳ�һ�������Ͻǵ����½ǵ�·����ʹ��·���ϵ������ܺ�Ϊ��С��

˵����ÿ��ֻ�����»��������ƶ�һ����
*/

class Solution {
public:
	int minPathSum(vector<vector<int>>& grid) {
		// Method 1 ��̬�滮 ������ ��medium��
		int row_num = grid.size(); int col_num = grid[row_num - 1].size();

		vector<vector<int>> dp(row_num, vector<int>(col_num));
		dp[0][0] = grid[0][0];

		// ����ÿ��ֻ�����»������ƶ�һ�� ���Կ��Գ�ʼ����һ�к͵�һ��
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