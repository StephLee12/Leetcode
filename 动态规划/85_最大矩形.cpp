# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
����һ�������� 0 �� 1 ����СΪ rows x cols �Ķ�ά�����ƾ����ҳ�ֻ���� 1 �������Σ������������
*/

class Solution {
public:
	int maximalRectangle(vector<vector<char>>& matrix) {
		int row_num = matrix.size();
		if (row_num == 0) return 0;
		int col_num = matrix[row_num - 1].size();

		// left_max�洢��ǰ����������ߵ����ֵ up_max�洢��ǰ����������ߵ����ֵ
		vector<vector<int>> left_max(row_num, vector<int>(col_num));
		vector<vector<int>> up_max(row_num, vector<int>(col_num));
		
		// ��ʼ�������Ͻ�Ԫ��
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

		// ��ʼ����һ�к͵�һ��
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

		// �������� Ѱ��max_area�����ֵ
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
						// �Ҷ�������[row,col]����Χ�ɵľ����е����ֵ 
						int left_min = left_max[row][col];
						for (int height = 1; height <= up_max[row][col]; height++) {
							// ����ÿһ�������ĸ߶� height ������������ֵ ��Ϊ�������
							left_min = min(left_min, left_max[row - height + 1][col]);
							int tmp = height * left_min;
							// ��õ�ǰ������������е����ֵ
							max_area = max(max_area, tmp);
						}
					}
				}
			}
		}

		return max_area;
	}
};