# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积
*/

class Solution {
public:
	int maximalRectangle(vector<vector<char>>& matrix) {
		int row_num = matrix.size();
		if (row_num == 0) return 0;
		int col_num = matrix[row_num - 1].size();

		// left_max存储当前结点能向左走的最大值 up_max存储当前结点能向上走的最大值
		vector<vector<int>> left_max(row_num, vector<int>(col_num));
		vector<vector<int>> up_max(row_num, vector<int>(col_num));
		
		// 初始化最左上角元素
		int max_area = 0;
		if (matrix[0][0] == '0') {
			left_max[0][0] = 0;
			up_max[0][0] = 0;
		}
		else {
			left_max[0][0] = 1;
			up_max[0][0] = 1;
			max_area = 1;
		}

		// 初始化第一列和第一行
		for (int col = 1; col < col_num; col++) {
			if (matrix[0][col] == '0') left_max[0][col] = 0;
			else { // matrix[0][col] == '1'
				up_max[0][col] = 1;
				left_max[0][col] = left_max[0][col - 1] + 1;
				max_area = max(max_area, left_max[0][col]);
			}
		}
		for (int row = 1; row < row_num; row++) {
			if (matrix[row][0] == '0') up_max[row][0] = 0;
			else { // matrix[row][0] == '1'
				left_max[row][0] = 1;
				up_max[row][0] = up_max[row - 1][0] + 1;
				max_area = max(max_area, up_max[row][0]);
			}
		}

		// 遍历矩阵 寻找max_area的最大值
		for (int row = 1; row < row_num; row++) {
			for (int col = 1; col < col_num; col++) {
				if (matrix[row][col] == '0') {
					left_max[row][col] = 0;
					up_max[row][col] = 0;
				}
				else { // matrix[row][col] == '1'
					char up = matrix[row - 1][col]; char left = matrix[row][col - 1];
					if (up == '0' && left == '0') {
						left_max[row][col] = 1;
						up_max[row][col] = 1;
						max_area = max(max_area, 1);
					}
					else if (up == '0' && left == '1') {
						left_max[row][col] = left_max[row][col - 1] + 1;
						up_max[row][col] = 1;
						max_area = max(left_max[row][col], max_area);
					}
					else if (up == '1' && left == '0') {
						left_max[row][col] = 1;
						up_max[row][col] = up_max[row - 1][col] + 1;
						max_area = max(up_max[row][col], max_area);
					}
					else { // up=='1' && left == '1'
						left_max[row][col] = left_max[row][col - 1] + 1;
						up_max[row][col] = up_max[row - 1][col] + 1;
						// 找对于坐标[row,col]可以围成的矩形中的最大值 
						int left_min = left_max[row][col];
						for (int height = 1; height <= up_max[row][col]; height++) {
							// 对于每一个连续的高度 height 找能向左的最大值 作为矩形面积
							left_min = min(left_min, left_max[row - height + 1][col]);
							int tmp = height * left_min;
							// 获得当前面积和最大面积中的最大值
							max_area = max(max_area, tmp);
						}
					}
				}
			}
		}

		return max_area;
	}
};