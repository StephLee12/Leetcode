# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集
*/

class Solution {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		// Method 1 递归DFS
		int len = nums.size();

		vector<vector<int>> res;
		// 首先将空集加入结果
		res.push_back(vector<int>());

		// 对nums进行排序 为了使得到的集合是升序
		sort(nums.begin(), nums.end());

		vector<int> subset; // 记录dfs时的集合
		for (int i = 0; i < len; i++) {
			// 对nums进行遍历 nums[i]作为集合中最小的元素
			subset.push_back(nums[i]);
			dfs(nums, res, subset, i, len);
			subset.pop_back(); // 注意dfs结束之后要pop 以便下一轮循环的dfs
		}

		return res;
	}

	void dfs(vector<int>& nums, vector<vector<int>>& res, vector<int>& vec, int pos, const int len) {
		// pos表明当前dfs遍历到的位置
		if (pos == len) return;  // 如果pos超过nums右边界 结束dfs
		res.push_back(vec); // 将当前集合加入结果

		for (int i = pos + 1; i < len; i++) {
			vec.push_back(nums[i]);
			dfs(nums, res, vec, i, len);
			vec.pop_back();
		}
	}
};