# include <vector>
# include <iostream>
# include <algorithm>
# include <unordered_map>

using namespace std;

/*
给定一个无重复元素的数组 candidates 和一个目标数 target 

找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。

candidates中每个元素都是独一无二的



说明：

所有数字（包括 target）都是正整数。
解集不能包含重复的组合

*/

class Solution {
public:
	// Method 1 暴力DFS 
	/*
	自己的思路是 从数组的第一个元素开始枚举 这样会使递归深度
	这样时间复杂度和空间复杂度都很大
	主要是没剪枝
	*/
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		int len = candidates.size();

		sort(candidates.begin(), candidates.end());

		int r_pos = 0; // 寻找target可能出现的最右位置
		vector<vector<pair<int,int>>> dict(len); // 记录每个元素 及其自乘的值
		for (int i = 0; i < len; i++) {
			r_pos = i;
			if (candidates[i] > target) {
				r_pos = i - 1;
				break;
			}
			int tmp = target / candidates[i];
			for (int j = 0; j <= tmp; j++) {
				dict[i].push_back(pair<int, int>{j, j* candidates[i]});
			}
		}

		vector<vector<int>> res;
		for (auto&& x : dict[0]) {
			vector<int> tmp;
			int sum = 0;
			for (int i = 1; i <= x.first; i++) {
				tmp.push_back(x.second/x.first);
				sum += x.second/x.first;
			}
			dfs(res, dict, tmp, target, sum,1,r_pos);
		}

		return res;
		
	}

	void dfs(vector<vector<int>>& res, vector<vector<pair<int,int>>>& dict, vector<int> vec,int target,int sum,int cnt,int r_pos) {
		if (sum == target) {
			res.push_back(vec);
			return;
		}

		if (sum > target) return;

		if (cnt > r_pos) return;

		for (auto&& x : dict[cnt]) {
			vector<int> tmp(vec.begin(), vec.end());
			int tmp_sum = 0;
			for (int i = 1; i <= x.first; i++) {
				tmp.push_back(x.second / x.first);
				tmp_sum += x.second / x.first;
			}
			dfs(res, dict, tmp, target, sum + tmp_sum, cnt + 1, r_pos);
		}
	}


	// Method 2 题解DFS
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		int len = candidates.size();

		vector<vector<int>> res;

		sort(candidates.begin(), candidates.end());
		vector<int> path;
		dfs(candidates, 0, len, target, path, res);
		return res;
		
	}

	void dfs(vector<int>& candidates, int begin, int len, int target, vector<int>& path, vector<vector<int>>& res) {
		if (target == 0) {
			res.push_back(path);
			return;
		}
		for (int i = begin; i < len; i++) {
			// begin即为递归开始的起点 这样起点不同 会使递归的深度减小 即树的高度会减小 
			// begin之后的递归 不会再遍历candidates[i]之前的元素 这种防止会出现重复 尤其是对这种 223 和322 不能重复的题目
			if (target - candidates[i] < 0) break;
			path.push_back(candidates[i]);
			dfs(candidates, i, len, target - candidates[i], path, res);
			path.pop_back();
		}
	}
};

int main() {
	
	vector<int> test{ 2,3,6,7 };
	Solution obj;
	obj.combinationSum(test, 7);
	return 0;
}
