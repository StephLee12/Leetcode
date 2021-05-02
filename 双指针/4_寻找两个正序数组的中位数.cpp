# include <iostream>
# include <algorithm>
# include <vector>

using namespace std;

/*
����������С�ֱ�Ϊ m �� n �����򣨴�С�������� nums1 �� nums2�������ҳ���������������������� ��λ�� ��

���ף��������һ��ʱ�临�Ӷ�Ϊ O(log (m+n)) ���㷨�����������
*/

class Solution {
public:
	// Method 1 ˫ָ�� ���Ӷ�O(m+n)
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		
		int len_1 = nums1.size(); int len_2 = nums2.size();
		// ��λ����λ�� ����x������ ��len_1+len_2Ϊ���� ��left_pos��right_pos���
		int left_pos = (len_1 + len_2 + 1) / 2; int right_pos = (len_1 + len_2) / 2 + 1;

		double res = 0;
		int p_1 = 0; int p_2 = 0; // ˫ָ��
		int cnt = 1; // ��¼��ǰ���������ֵ�λ��
		while (p_1 < len_1 && p_2 < len_2) {
			// nums1��nums2��û������

			// ���������λ����������
			if (cnt == left_pos) res += (double)(nums1[p_1] <= nums2[p_2] ? nums1[p_1] : nums2[p_2]);

			// ���������λ���Ҳ������ ֱ��return
			if (cnt == right_pos) {
				res += (double)(nums1[p_1] <= nums2[p_2] ? nums1[p_1] : nums2[p_2]);
				return res / double(2);
			}
			// �Ƚϴ�С ����ָ��
			if (nums1[p_1] <= nums2[p_2]) {
				p_1++; cnt++;
			}
			else {
				p_2++; cnt++;
			}
		}

		if (p_1 < len_1) {
			// ���nums2������
			if (cnt > left_pos) res += (double)(nums1[p_1 + right_pos - cnt]); // ��ǰλ���Ѿ�������λ�����
			else {
				// ��ǰλ��δ������λ�����
				res += (double)(nums1[p_1 + left_pos - cnt]);
				res += (double)(nums1[p_1 + right_pos - cnt]);
			}
		}
		if (p_2 < len_2) {
			// ���nums1������
			if (cnt > left_pos) res += (double)(nums2[p_2 + right_pos - cnt]);
			else {
				res += (double)(nums2[p_2 + left_pos - cnt]);
				res += (double)(nums2[p_2 + right_pos - cnt]);
			}
		}
		return res/double(2);
	}

	// Method 2 ���ַ� ���׷��� ʱ�临�Ӷ�O(log(m+n))
	/*
	����λ�� �൱�����ҵ�kС���� ����nums1��nums2�зֱ��ȡǰk/2����
	*/
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int len_1 = nums1.size(); int len_2 = nums2.size();
		int left_pos = (len_1 + len_2 + 1) / 2; int right_pos = (len_1 + len_2) / 2 + 1;
		// ������λ�������Ҳ�ֱ����һ�κ���ƽ��
		return (double)(0.5 * (get_k_min(nums1, nums2, left_pos, 0, len_1 - 1, 0, len_2 - 1) + get_k_min(nums1, nums2, right_pos, 0, len_1 - 1, 0, len_2 - 1)));
	}

	int get_k_min(vector<int>& nums1, vector<int>& nums2, int k,int start_1, int end_1, int start_2, int end_2) {
		// ��nums1���ȴ���nums2 �����߽��� ʼ�ձ���nums1�ĳ���<=nums2
		if (end_1 - start_1 + 1> end_2 - start_2 + 1) return get_k_min(nums2, nums1, k,start_2, end_2, start_1, end_1);
		// ���nums1�Ѿ�������
		if (end_1 - start_1 + 1 == 0) return nums2[start_2 + k - 1];

		// ���Ҫ�ҵ�1����С�� ֱ���жϵ�ǰnums1��nums2���ĸ���С
		if (k == 1) return min(nums1[start_1], nums2[start_2]);

		// �ֱ��ҵ�k/2��λ�� ����-1����Ϊ�±��0��ʼ
		int p_1 = start_1 + min(k / 2, end_1 - start_1 + 1) - 1;
		int p_2 = start_2 + min(k / 2, end_2 - start_2 + 1) - 1;

		// ���nums1��nums2�� ���nums2���и��� ��֮ ��nums1���и���
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