# include <vector>
# include <algorithm>
# include <iostream>

using namespace std;

/*
给你一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，

其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

*/

class Solution {
public:
	// Method 1 改变了输入数组
	vector<int> productExceptSelf(vector<int>& nums) {
		int len = nums.size();

		vector<int> res(nums.begin(), nums.end());

		nums[0] = 1; // 用nums保存前缀乘积
		for (int i = 1; i < len; i++) {
			nums[i] = res[i - 1] * nums[i - 1];
		}

		int prod = 1; // 记录后缀乘积
		int store = 0;
		for (int i = len - 1; i >= 0; i--) {
			store = res[i];
			res[i] = prod * nums[i];
			prod = prod * store;
		}

		return res;
	}

	// Method 2 左右累乘
	vector<int> productExceptSelf(vector<int>& nums) {
		int len = nums.size();
		int leftProd = 1;
		int rightProd = 1;
		vector<int> res(len, 1);

		for (int i = 0; i < len; i++) {
			res[i] *= leftProd;
			leftProd *= nums[i];

			res[len - 1 - i] *= rightProd;
			rightProd *= nums[len - 1 - i];
		}
		return res;
	}
};