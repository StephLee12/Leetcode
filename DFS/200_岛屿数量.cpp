# include <vector>
# include <algorithm>

using namespace std;

/*
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围

*/

class Solution {
public:
	vector<vector<int>> move{
		vector<int>{-1,0}, // 向上
		vector<int>{1,0}, // 向下
		vector<int>{0,-1}, // 向左
		vector<int>{0,1} // 向右
	};
	int rowNum;
	int colNum;

	int numIslands(vector<vector<char>>& grid) {
		// Method 1 dfs递归
		this->rowNum = grid.size();
		if (rowNum == 0) return 0;
		this->colNum = grid[0].size();


		vector<vector<int>> visited(rowNum, vector<int>(colNum));
		int res = 0;
		for (int i = 0; i < rowNum; i++) {
			for (int j = 0; j < colNum; j++) {
				if (grid[i][j] == '1') {
					// 从没有被遍历过的'1'开始dfs
					if (visited[i][j]) continue;
					dfs(grid, visited, i, j);
					res++;
				}
			}
		}

		return res;
	}

	void dfs(vector<vector<char>>& grid, vector<vector<int>>& visited, int x, int y) {
		/*
		只需要找到岛屿的边界即可
		*/
		visited[x][y] = 1; // 将该结点标记为已遍历
		for (auto&& act : move) {
			// 从xy移动到newXnewY
			int newX = x + act[0];
			int newY = y + act[1];

			if (newX<0 || newX>rowNum - 1) continue; // 超出行边界 停止dfs
			if (newY<0 || newY>colNum - 1) continue; // 超出列边界 停止dfs

			if (grid[newX][newY] == '1') {
				// 如果新坐标对应的网格值为'1' 继续dfs
				if (visited[newX][newY]) continue;
				dfs(grid, visited, newX, newY);
			}
			else continue; // 如果新坐标对应网格值为'0' 停止dfs
		}
	}
};
