# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，

使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色

进阶：

你可以不使用代码库中的排序函数来解决这道题吗？
你能想出一个仅使用常数空间的一趟扫描算法吗？

*/

class Solution {
public:
	void sortColors(vector<int>& nums) {
		// Method 1 扫描两遍 计数排序
		int len = nums.size();
		if (len == 0 || len == 1) return;

		vector<int> cnt(3,0); // 用来计数 0 1 2 分别的数目

		for (auto&& num : nums) {
			if (num == 0) cnt[0]++;
			else if (num == 1) cnt[1] ++;
			else cnt[2]++;
		}

		int p = 0;
		for (int i = 0; i < cnt[0]; i++, p++) nums[p] = 0;
		for (int i = 0; i < cnt[1]; i++, p++) nums[p] = 1;
		for (int i = 0; i < cnt[2]; i++, p++) nums[p] = 2;
	}
	void sortColors(vector<int>& nums) {
		// Method 2 扫描一遍 常数空间开销
		// 思路就是将0挪到左边 2挪到右边
		int len = nums.size();
		if (len == 0 || len == 1) return;
		
		// l_p维护0的右边界  r_p维护2的左边界
		int l_p = 0; int r_p = len - 1;
		for (int i = 0; i <= r_p; i++) { // 注意这里循环结束的条件
			if (nums[i] == 0) {
				// 如果当前位置是0 和l_p交换
				nums[i] = nums[l_p];
				nums[l_p] = 0;
				l_p++;
			}

			if (nums[i] == 2) {
				// 如果当前位置是2 和r_p交换
				nums[i] = nums[r_p];
				nums[r_p] = 2;
				r_p--;
				// 如果交换回来的不是1 说明是0或2 i要回退 在下一个循环中还是nums[i]
				if (nums[i] != 1) i--; 
			}
		}
	}
};