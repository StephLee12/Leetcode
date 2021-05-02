# include <vector>
# include <algorithm>

using namespace std;

class Solution {
public:
	// Method 1 ��̬�滮 ��85��˼·һ�� ��¼ÿ��λ��������������ƶ������ֵ
	int maximalSquare(vector<vector<char>>& matrix) {
		int rowNum = matrix.size();
		if (rowNum == 0) return 0;
		int colNum = matrix[0].size();

		vector<vector<int>> leftMax(rowNum, vector<int>(colNum));
		vector<vector<int>> upMax(rowNum, vector<int>(colNum));

		int maxArea = 0;
		// ��ʼ����һ�е�һ��
		if (matrix[0][0] == '1') {
			leftMax[0][0] = 1;
			upMax[0][0] = 1;
			maxArea = 1;
		}
		for (int row = 1; row < rowNum; row++) {
			if (matrix[row][0] == '1') {
				leftMax[row][0] = 1;
				upMax[row][0] = upMax[row - 1][0] + 1;
				maxArea = 1;
			}
		}
		for (int col = 1; col < colNum; col++) {
			if (matrix[0][col] == '1') {
				leftMax[0][col] = leftMax[0][col - 1] + 1;
				upMax[0][col] = 1;
				maxArea = 1;
			}
		}

		for (int row = 1; row < rowNum; row++) {
			for (int col = 1; col < colNum; col++) {
				if (matrix[row][col] == '0') continue; // �����ǰλ����0

				upMax[row][col] = upMax[row - 1][col] + 1;
				leftMax[row][col] = leftMax[row][col - 1] + 1;

				if (upMax[row][col] == 1 || leftMax[row][col] == 1) {
					// ��ǰλ�õ��Ϸ������󷽳���0
					maxArea = max(maxArea, 1);
				}
				else {
					int minLen = INT_MAX;
					for (int h = 1; h <= upMax[row][col]; h++) {
						minLen = min(minLen, leftMax[row - h + 1][col]);
						if (minLen >= h) {
							maxArea = max(maxArea, h * h);
						}
					}
				}


			}
		}
		return maxArea;
	}

	// Method 2 ��̬�滮�Ż� ���������β�����ô�鷳 ֻ��Ҫ��¼�߳�����
	int maximalSquare(vector<vector<char>>& matrix) {
		int rowNum = matrix.size();
		if (rowNum == 0) return 0;
		int colNum = matrix[0].size();

		vector<vector<int>> dp(rowNum, vector<int>(colNum));
		int maxLen = 0;
		// ��ʼ����һ�е�һ��
		if (matrix[0][0] == '1') {
			dp[0][0] = 1;
			maxLen = 1;
		}
		for (int row = 1; row < rowNum; row++) {
			if (matrix[row][0] == '1') {
				dp[row][0] = 1;
				maxLen = 1;
			}
		}
		for (int col = 1; col < colNum; col++) {
			if (matrix[0][col] == '1') {
				dp[0][col] = 1;
				maxLen = 1;
			}
		}

		for (int row = 1; row < rowNum; row++) {
			for (int col = 1; col < colNum; col++) {
				if (matrix[row][col] == '1') {
					dp[row][col] = 1 + min(dp[row - 1][col - 1], min(dp[row - 1][col], dp[row][col - 1]));
					maxLen = max(maxLen, dp[row][col]);
				}
			}
		}
		return maxLen * maxLen;
	}
};
