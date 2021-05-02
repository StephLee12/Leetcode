# include <vector>
# include <algorithm>
# include <time.h>

using namespace std;

/*
��δ������������ҵ��� k ������Ԫ�ء�

��ע�⣬����Ҫ�ҵ������������ĵ� k ������Ԫ�أ������ǵ� k ����ͬ��Ԫ��
*/

class Solution {
public:
	// Method 1 �����ⷨ ���ÿ⺯��
	int findKthLargest(vector<int>& nums, int k) {
		int len = nums.size();
		sort(nums.begin(), nums.end(), greater<int>());
		return nums[k - 1];
	}

	// Method 2 ����
	int findKthLargest(vector<int>& nums, int k) {
		int len = nums.size();
		k = len - k; // ת��Ϊ�±�
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

	// Method 3 ����(���������)
	int findKthLargest(vector<int>& nums, int k) {
		
		srand(time(NULL)); // ��ʼ���������
		int len = nums.size();
		k = len - k; // ת��Ϊ�±�
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
		// ���ѡȡ�±�
		int randIndex = rand() % (right - left + 1) + left;
		// ��ѡȡ���±��Ӧ��ֵ��Ϊpivot
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