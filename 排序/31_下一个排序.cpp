# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须 原地 修改，只允许使用额外常数空间

*/

class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int len = nums.size();
		if (len == 1) return; // 边界情况

		bool flag = false;
		int r_p = len - 1;
		while (r_p - 1 >= 0) {
			// 搜索当前元素比前一个元素大的位置 前一个元素的位置即为替换点
			if (nums[r_p - 1] >= nums[r_p]) r_p--;
			else {
				flag = true;
				int left_pos = r_p - 1;
				int min_pos = r_p;
				// 向右找大于left_pos中最小的元素 该元素对应位置即为替换点
				r_p++;
				while (r_p < len) {
					if (nums[r_p] > nums[left_pos]) {
						if (nums[r_p] < nums[min_pos]) {
							min_pos = r_p;
						}
					}
					r_p++;
				}
				// 交换两个元素
				swap(nums[left_pos], nums[min_pos]);
				// 交换之后 对前一个交换点之后点序列进行升序排序
				sort(nums.begin() + left_pos + 1, nums.end());
				break;
			}
		}
		// 如果该排列已经是最大的字典序 将序列逆序输出
		if (!flag) reverse(nums.begin(), nums.end());
	}
};