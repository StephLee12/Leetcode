# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素）
返回其最大和
*/

class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		// Method 1 动态规划
		int len = nums.size();
		// 直接在nums上动态规划 以nums[i]为右边界的最大和
		int max_val = nums[0];
		for (int i = 1; i < len; i++) {
			if (nums[i - 1] + nums[i] > nums[i]) {
				// 若nums[i]前的连续最大和加上nums[i]>nums[i]
				// 则要更新nums[i]
				nums[i] += nums[i-1];	
			}
			// 判断当前以nums[i]为右边界的最大和 是否最大
			if (nums[i] > max_val) max_val = nums[i];
		}

		return max_val;
	}
};