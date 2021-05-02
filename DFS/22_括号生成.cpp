# include <iostream>
# include <vector>
# include <string>
# include <algorithm>
# include <stack>
# include <unordered_map>

using namespace std;

/*
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合
*/


class Solution {
public:
	vector<string> generateParenthesis(int n) {
		// Method 1 DFS递归
		vector<string> res;
		// dfs(res, "", n,2*n,0);
		dfs(res, "", n, n);
		return res;
	}

	void dfs(vector<string>& res, string s, int l_num, int r_num) {
		// l_num 左括号剩余数目 r_num 右括号剩余数目
		if (l_num == 0 && r_num == 0) {
			// 当且仅当左右括号数目都为0 是一个有效括号
			res.push_back(s);
			return;
		}

		if (l_num == r_num) dfs(res, s+"(", l_num - 1, r_num); // 若左右括号数量相等 下一个只能用左括号
		else if (l_num < r_num) {
			// 如果左括号数量小于右括号 下个括号既可以用左括号 也可以用右括号
			if (l_num > 0) dfs(res, s + "(", l_num - 1, r_num);
			dfs(res, s + ")", l_num, r_num - 1);
		}
		// 左括号数量大于右括号 显然不是一个有效括号
	}

	/*
	void dfs(vector<string>& res, string s, const int pair_num,int rest_len,int match_time) {
		// match_time记录匹配的次数
		if (rest_len == 0) {
			if (match_time == pair_num) res.push_back(s);
			return;
		}

		int len = s.size();

		dfs(res, s + "(", pair_num, rest_len - 1, match_time);
		if ((len - 1 >= 0 && s[len - 1] == '(')) dfs(res, s + ")", pair_num, rest_len - 1, match_time + 1);
		else if (len - 1 >= 0 && s[len - 1] == ')') {
			for (int i = 1; i <= match_time; i++) {
				if (len - 1- match_time * 2 >= 0 && s[len - 1- match_time * 2] == '(') {
					dfs(res, s + ")", pair_num, rest_len - 1, match_time + 1);
					break;
				}
			}
		}
	}
	*/
	
};

int main() {
	Solution obj;
	obj.generateParenthesis(3);
	return 0;
}