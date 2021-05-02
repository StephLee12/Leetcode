# include<vector>

using namespace std;

/*
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。

*/

class Solution {
public:
	/*
	本题关键在于确定搜索起点——矩阵的四个角
	左上角和右下角都不行——左上角的右侧和下侧都比左上角元素大 右下角同理 左侧和上侧都小
	而右上角和左下角可以作为搜索起点
	若以左下角为搜索起点
	若目标元素小于左下角 由于左下角是当前行中的最小元素 目标元素不可能在当前行 则继续在不包含该行的子矩阵中搜索
	若目标元素大于左下角 由于左下角是当前列中的最大元素 目标元素不可能在当前列 则继续在不包含该列的子矩阵中搜索
	*/
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int rowNum = matrix.size();
		if (rowNum == 0) return false;
		int colNum = matrix[0].size();

		int col = 0;
		int row = rowNum - 1;
		while (col < colNum && row >= 0) {
			if (matrix[row][col] == target) return true;
			else if (matrix[row][col] < target) col++;
			else row--;
		}
		return false;
	}
};