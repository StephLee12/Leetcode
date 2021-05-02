# include <iostream>
# include <vector>
# include <algorithm>


using namespace std;

/*
给你一个数组 nums ，它包含 n 个正整数。你需要计算所有非空连续子数组的和，
并将它们按升序排序，得到一个新的包含 n * (n + 1) / 2 个数字的数组。

请你返回在新数组中下标为 left 到 right （下标从 1 开始）的所有数字和（包括左右端点）。
由于答案可能很大，请你将它对 10^9 + 7 取模后返回
*/


class Solution {
public:
	int rangeSum(vector<int>& nums, int n, int left, int right) {
		
		// Method 1 纯暴力解法 没技术含量
		vector<int> new_nums;

		// 得到新数组
		for (int i = 0; i <= n - 1; i++) {
			new_nums.push_back(nums[i]);
			int sum = nums[i];
			for (int j = i + 1; j <= n - 1; j++) {
				sum += nums[j];
				new_nums.push_back(sum);
			}
		}

		//新数组排序
		sort(new_nums.begin(),new_nums.end());
		int res = 0;
		for (int i = left - 1; i <= right - 1; i++) {
			res = (res + new_nums[i]) % 1000000007;
		}

		return res;

		// Method 2 多路归并排序
	}
};