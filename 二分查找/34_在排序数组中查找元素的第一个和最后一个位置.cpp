# include <algorithm>
# include <iostream>
# include <vector>

using namespace std;

/*
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。

进阶：

你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？

*/

class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target) {
		int len = nums.size();
		// 边界情况
		if (len == 0) return vector<int>{-1, -1};
		if (len == 1) return nums[0] == target ? vector<int>{0, 0} : vector<int>{ -1,-1 };

		int low = 0; int high = len - 1;
		int mid = 0;
		int l_pos = -1; int r_pos = -1;
		// vector<int> res{ -1,-1 };
		while (low <= high) {
			mid = (low + high) / 2;
			if (nums[mid] < target) low = mid + 1;// mid的元素比target小 
			else if (nums[mid] > target) high = mid - 1; // mid的元素比target大
			else { // nums[mid] == target
				l_pos = mid; r_pos = mid;
				break;
			}
		}

		// 在mid两侧进行二分搜索 找到边界
		int high_l = mid - 1; int low_r = mid + 1;
		mid = 0;
		while (low <= high_l) {
			mid = (low + high_l) / 2;
			if (nums[mid] < target) low = mid + 1;// mid的元素比target小
			else if (nums[mid] > target) high_l = mid - 1; // mid的元素比target大
			else { // nums[mid] == target
				l_pos = mid; high_l = mid - 1; // 继续向左搜索
			}
		}
		while (low_r <= high) {
			mid = (low_r + high) / 2;
			if (nums[mid] < target) low_r = mid + 1; // mid的元素比target小
			else if (nums[mid] > target) high = mid - 1; // mid的元素比target大
			else { // nums[mid] == target
				r_pos = mid; low_r = mid + 1; // 继续向右搜索
			}
		}

		vector<int> res;
		res.push_back(l_pos); res.push_back(r_pos);
		return res;
	}
};