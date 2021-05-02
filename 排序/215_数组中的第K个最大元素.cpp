# include <vector>
# include <algorithm>
# include <time.h>

using namespace std;

/*
在未排序的数组中找到第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素
*/

class Solution {
public:
	// Method 1 暴力解法 调用库函数
	int findKthLargest(vector<int>& nums, int k) {
		int len = nums.size();
		sort(nums.begin(), nums.end(), greater<int>());
		return nums[k - 1];
	}

	// Method 2 快排
	int findKthLargest(vector<int>& nums, int k) {
		int len = nums.size();
		k = len - k; // 转换为下标
		return quickSort(nums, 0, len - 1, k);
	}

	int quickSort(vector<int>& nums, int left, int right, const int targetIndex) {
		if (left < right) {
			int mid = partition(nums, left, right);
			if (mid == targetIndex) return nums[mid];
			else if (mid < targetIndex) {
				return quickSort(nums, mid + 1, right, targetIndex);
			}
			else {
				return quickSort(nums, left, mid, targetIndex);
			}
		}
		return nums[left];
	}

	int partition(vector<int>& nums, int left, int right) {
		int pivot = nums[left];
		while (left < right) {
			while (left < right && nums[right] >= pivot) {
				right--;
			}
			nums[left] = nums[right];
			while (left < right && nums[left] <= pivot) {
				left++;
			}
			nums[right] = nums[left];
		}
		nums[left] = pivot;
		return left;
	}

	// Method 3 快排(随机化加速)
	int findKthLargest(vector<int>& nums, int k) {
		
		srand(time(NULL)); // 初始化随机种子
		int len = nums.size();
		k = len - k; // 转换为下标
		return quickSort(nums, 0, len - 1, k);
	}

	int quickSort(vector<int>& nums, int left, int right, const int targetIndex) {
		if (left < right) {
			int mid = partition(nums, left, right);
			if (mid == targetIndex) return nums[mid];
			else if (mid < targetIndex) {
				return quickSort(nums, mid + 1, right, targetIndex);
			}
			else {
				return quickSort(nums, left, mid, targetIndex);
			}
		}
		return nums[left];
	}

	int partition(vector<int>& nums, int left, int right) {
		// 随机选取下标
		int randIndex = rand() % (right - left + 1) + left;
		// 将选取的下标对应的值作为pivot
		swap(nums[left], nums[randIndex]);

		int pivot = nums[left];
		while (left < right) {
			while (left < right && nums[right] >= pivot) {
				right--;
			}
			nums[left] = nums[right];
			while (left < right && nums[left] <= pivot) {
				left++;
			}
			nums[right] = nums[left];
		}
		nums[left] = pivot;
		return left;
	}
};