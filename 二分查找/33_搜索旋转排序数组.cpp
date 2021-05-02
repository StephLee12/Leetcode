# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，

使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。

例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 

*/

class Solution {
public:
	int search(vector<int>& nums, int target) {
		// Method 1 二分查找
		int len = nums.size();
		if (len == 0) return -1;
		if (len == 1) return nums[0] == target ? 0 : -1;

		int low = 0; int high = len - 1; 
		int mid = 0;

		while (low <= high) {
			mid = (low + high) / 2;
			if (nums[mid] == target) return mid;
			if (nums[0] <= nums[mid]) { // 注意这里的等号要加 因为mid可能等于0(e.g. 数组中只有两个元素)
				// mid左侧为升序
				if (nums[0] <= target && nums[mid] >= target) high = mid-1; // target在左侧序列内
				else low = mid + 1; // target在右侧序列内
			}
			else {
				// mid右侧为升序
				if (nums[mid] <= target && nums[len - 1] >= target) low = mid + 1; // target在右侧序列内
				else high = mid - 1;
			}
		}

		return -1;
	}
};