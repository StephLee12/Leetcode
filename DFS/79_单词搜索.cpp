# include <vector>
# include <string>
# include <iostream>
# include <algorithm>

using namespace std;

/*
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。

如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，

其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

*/

class Solution {
public:
	bool exist(vector<vector<char>>& board, string word) {
		// Method 1 没有经过剪枝的DFS 每个位置都要遍历
		int row_num = board.size();
		if (row_num == 0) return false;
		int col_num = board[0].size();
		int len_w = word.size();

		// 记录遍历过的元素
		vector<vector<int>> visited(row_num, vector<int>(col_num));
		// 每个位置可以向上左下右四个方向移动
		vector<vector<int>> move{
			vector<int>{-1,0}, vector<int>{0,-1},
			vector<int>{1,0}, vector<int>{0,1}
		};

		for (int i = 0; i < row_num; i++) {
			for (int j = 0; j < col_num; j++) {
				if (dfs(i, j, 0, word, len_w, visited,board, row_num, col_num, move)) return true;
			}
		}
		return false;
	}

	bool dfs(int x_pos, int y_pos, int word_pos, const string& word, const int len_w, vector<vector<int>>& visited,const vector<vector<char>>& board, const int row_num, const int col_num,const vector<vector<int>>& move) {
		if (word_pos == len_w - 1) {
			return board[x_pos][y_pos] == word[word_pos];
		}

		if (board[x_pos][y_pos] == word[word_pos]) {
			visited[x_pos][y_pos] = 1;
			
			// 从当前位置向上下左右移动 继续dfs 注意移动不能超过边界
			for (auto&& act : move) {
				int new_x = x_pos + act[0];
				int new_y = y_pos + act[1];
				if ((new_x >= 0 && new_x <= row_num - 1) && (new_y >= 0 && new_y <= col_num - 1) && visited[new_x][new_y]==0) {
					if (dfs(new_x, new_y, word_pos + 1, word, len_w, visited, board, row_num, col_num, move)) {
						return true;
					}
				}
			}

			visited[x_pos][y_pos] = 0; // dfs结束要将状态释放
		}

		return false;
	}
};