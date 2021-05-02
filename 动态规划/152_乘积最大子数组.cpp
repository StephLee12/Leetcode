# include <vector>
# include <iostream>
# include <algorithm>
# include <unordered_map>
# include <unordered_set>

using namespace std;

/*
给你一个整数数组 nums ，

请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），

并返回该子数组所对应的乘积

*/

class Solution {
public:
	// Method 1 动态规划 
	int maxProduct(vector<int>& nums) {
		
		int len = nums.size();
		
		// 两个数组分别记录以i结尾的最大乘积和最小乘积
		// 因为可能存在负负得正的情况
		vector<int> maxVals(nums.begin(),nums.end());
		vector<int> minVals(nums.begin(), nums.end());

		int maxVal = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			// 当前maxVals[i]可能是nums[i](maxVals[i]*nums[i]为负),nums[i]*minVals[i-1](负负得正)
			maxVals[i] = max({ nums[i],nums[i] * minVals[i - 1],maxVals[i - 1] * nums[i] });
			minVals[i] = min({ nums[i],nums[i] * minVals[i - 1],maxVals[i - 1] * nums[i] });
			maxVal = max(maxVal, maxVals[i]);
		}

		return maxVal;
	}

	// Method 2 本来的思路 没写出来
	/*
	将数组看成是被0拆分的子数组 最大值即为每个数组的最大值求max
	对于每个子数组 如果负数有偶数个 则直接连乘
	如果有奇数个 从左边开始连乘有一个最大值 从右边开始连乘有一个最大值 比较即可
	*/
	int maxProduct(vector<int>& nums) {
		int len = nums.size();
		int sum = 1;
		int maxVal = nums[0];

		for (int i = 0; i < len; i++) {
			sum *= nums[i];
			maxVal = max(maxVal, sum);
			if (nums[i] == 0) sum = 1; // 如果nums[i]为0 要重新连乘
		}

		sum = 1;
		for (int i = len - 1; i >= 0; i++) {
			sum *= nums[i];
			maxVal = max(maxVal, sum);
			if (nums[i] == 0) sum = 1;
		}

		return maxVal;
	}
};