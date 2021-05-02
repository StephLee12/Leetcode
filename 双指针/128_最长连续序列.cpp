# include <vector>
# include <iostream>
# include <algorithm>
# include <unordered_set>

using namespace std;

/*
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

进阶：你可以设计并实现时间复杂度为 O(n) 的解决方案吗？

*/

class Solution {
public:
	// Method 1 先排序 双重循环 暴力遍历 复杂度O(nlogn+n)
	int longestConsecutive(vector<int>& nums) {
		int len = nums.size();
		if (len == 0) return 0;

		sort(nums.begin(), nums.end()); // 先将数组排序

		int max_len = 1;
		int p = 0;
		int l_p = 0;
		int r_p = 0;

		// 优化一下二层循环
		while (p < len - 1) {
			// 排序后 是升序序列 向p的右边搜索 直到不是连续序列 更新p的位置
			l_p = nums[p];
			r_p = nums[p];
			for (int j = p + 1; j < len; j++) {
				p++;
				if (nums[j] == r_p + 1) r_p++;
				else if (nums[j] > r_p + 1) break;
			}
			max_len = max(max_len, r_p - l_p + 1);
		}

		/*
		for (int i = 0; i < len - 1; i++) {
			if (nums[i] == INT_MIN) continue; // nums[i]已经被遍历过
			// 若nums[i]没有被遍历过 中心扩散它的左右边界
			int l_p = nums[i]; int r_p = nums[i]; 
			for (int j = i + 1; j < len; j++) {
				if (nums[j] == l_p - 1) {
					nums[j] = INT_MIN;
					l_p--;
				}
				else if (nums[j] == r_p + 1) {
					nums[j] = INT_MIN;
					r_p++;
				}
			}
			max_len = max(max_len, (r_p - l_p + 1));
		}
		*/
		return max_len;
	}

	// Method 2 时间复杂度O(n) 个人觉得不是O(n)
	int longestConsecutive(vector<int>& nums) {
		// 用set首先erase掉重复数据
		unordered_set<int> num_set;
		for (auto&& num : nums) num_set.insert(num);

		int max_len = 0;
		for (auto&& num : num_set) {
			// 对于一个连续序列 x x+1 x+2... 保证一定从x开始搜索
			// 所以如果num-1不在set中 说明一定是序列最左端
			if (num_set.find(num - 1) == num_set.end()) {
				int cur_num = num;
				int cur_len = 1;

				// 在set中搜索连续序列
				while (num_set.find(cur_num) != num_set.end()) {
					cur_num += 1;
					cur_len += 1;
				}

				max_len = max(max_len, cur_len);
			}
		}

		return max_len;
	}
};