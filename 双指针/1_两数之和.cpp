# include <iostream>
# include <vector>
# include <algorithm>
# include <numeric>

using namespace std;

/*
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案

*/

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		// Method 1 双指针
		int len = nums.size();
		// 对nums数组的下标按照其对应的值升序排列
		vector<int> idxs(len);
		iota(idxs.begin(), idxs.end(), 0); // itoa生成连续的序列 需要numeric头文件
		sort(idxs.begin(), idxs.end(), [&](int i, int j) {return nums[i] < nums[j]; }); // lambda表达式


		int l_p = 0; int r_p = len - 1; // 双指针
		vector<int> res;
		while (l_p<r_p) {
			// 左右指针在nums数组中的实际下标
			int l_idx = idxs[r_p]; int r_idx = idxs[l_p];
			// 实际下标对应的值
			int l_num = nums[l_idx]; int r_num = nums[r_idx];
			// 判断是否等于target
			if (l_num + r_num < target) l_p++;
			else if (l_num + r_num > target) r_p--;
			else {
				res.push_back(l_idx); res.push_back(r_idx);
				break;
			}
		}
		return res;
	}
};