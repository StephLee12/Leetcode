# include <iostream>
# include <algorithm>
# include <vector>

using namespace std;

/*
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的 中位数 。

进阶：你能设计一个时间复杂度为 O(log (m+n)) 的算法解决此问题吗？
*/

class Solution {
public:
	// Method 1 双指针 复杂度O(m+n)
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		
		int len_1 = nums1.size(); int len_2 = nums2.size();
		// 中位数的位置 即第x个数字 若len_1+len_2为奇数 则left_pos与right_pos相等
		int left_pos = (len_1 + len_2 + 1) / 2; int right_pos = (len_1 + len_2) / 2 + 1;

		double res = 0;
		int p_1 = 0; int p_2 = 0; // 双指针
		int cnt = 1; // 记录当前遍历的数字的位置
		while (p_1 < len_1 && p_2 < len_2) {
			// nums1和nums2都没遍历完

			// 如果到了中位数左侧的数字
			if (cnt == left_pos) res += (double)(nums1[p_1] <= nums2[p_2] ? nums1[p_1] : nums2[p_2]);

			// 如果到了中位数右侧的数字 直接return
			if (cnt == right_pos) {
				res += (double)(nums1[p_1] <= nums2[p_2] ? nums1[p_1] : nums2[p_2]);
				return res / double(2);
			}
			// 比较大小 更新指针
			if (nums1[p_1] <= nums2[p_2]) {
				p_1++; cnt++;
			}
			else {
				p_2++; cnt++;
			}
		}

		if (p_1 < len_1) {
			// 如果nums2遍历完
			if (cnt > left_pos) res += (double)(nums1[p_1 + right_pos - cnt]); // 当前位置已经超过中位数左侧
			else {
				// 当前位置未超过中位数左侧
				res += (double)(nums1[p_1 + left_pos - cnt]);
				res += (double)(nums1[p_1 + right_pos - cnt]);
			}
		}
		if (p_2 < len_2) {
			// 如果nums1遍历完
			if (cnt > left_pos) res += (double)(nums2[p_2 + right_pos - cnt]);
			else {
				res += (double)(nums2[p_2 + left_pos - cnt]);
				res += (double)(nums2[p_2 + right_pos - cnt]);
			}
		}
		return res/double(2);
	}

	// Method 2 二分法 进阶方法 时间复杂度O(log(m+n))
	/*
	找中位数 相当于是找第k小的数 则在nums1和nums2中分别截取前k/2个数
	*/
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int len_1 = nums1.size(); int len_2 = nums2.size();
		int left_pos = (len_1 + len_2 + 1) / 2; int right_pos = (len_1 + len_2) / 2 + 1;
		// 对于中位数左侧和右侧分别计算一次后求平均
		return (double)(0.5 * (get_k_min(nums1, nums2, left_pos, 0, len_1 - 1, 0, len_2 - 1) + get_k_min(nums1, nums2, right_pos, 0, len_1 - 1, 0, len_2 - 1)));
	}

	int get_k_min(vector<int>& nums1, vector<int>& nums2, int k,int start_1, int end_1, int start_2, int end_2) {
		// 若nums1长度大于nums2 则两者交换 始终保持nums1的长度<=nums2
		if (end_1 - start_1 + 1> end_2 - start_2 + 1) return get_k_min(nums2, nums1, k,start_2, end_2, start_1, end_1);
		// 如果nums1已经遍历完
		if (end_1 - start_1 + 1 == 0) return nums2[start_2 + k - 1];

		// 如果要找第1个最小数 直接判断当前nums1和nums2中哪个更小
		if (k == 1) return min(nums1[start_1], nums2[start_2]);

		// 分别找到k/2的位置 这里-1是因为下标从0开始
		int p_1 = start_1 + min(k / 2, end_1 - start_1 + 1) - 1;
		int p_2 = start_2 + min(k / 2, end_2 - start_2 + 1) - 1;

		// 如果nums1比nums2大 则对nums2进行更新 反之 对nums1进行更新
		if (nums1[p_1] > nums2[p_2]) return get_k_min(nums1, nums2, k - (p_2 - start_2 + 1), start_1, end_1, p_2 + 1, end_2);
		else return get_k_min(nums1, nums2, k - (p_1 - start_1 + 1), p_1 + 1, end_1, start_2, end_2);
	}
};

int main() {
	vector<int> test_1{2};
	vector<int> test_2{};
	Solution obj;
	obj.findMedianSortedArrays(test_1, test_2);
	return 0;
}