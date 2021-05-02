# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
ʵ�ֻ�ȡ ��һ������ �ĺ������㷨��Ҫ���������������������г��ֵ�������һ����������С�

�����������һ����������У��������������г���С�����У����������У���

���� ԭ�� �޸ģ�ֻ����ʹ�ö��ⳣ���ռ�

*/

class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int len = nums.size();
		if (len == 1) return; // �߽����

		bool flag = false;
		int r_p = len - 1;
		while (r_p - 1 >= 0) {
			// ������ǰԪ�ر�ǰһ��Ԫ�ش��λ�� ǰһ��Ԫ�ص�λ�ü�Ϊ�滻��
			if (nums[r_p - 1] >= nums[r_p]) r_p--;
			else {
				flag = true;
				int left_pos = r_p - 1;
				int min_pos = r_p;
				// �����Ҵ���left_pos����С��Ԫ�� ��Ԫ�ض�Ӧλ�ü�Ϊ�滻��
				r_p++;
				while (r_p < len) {
					if (nums[r_p] > nums[left_pos]) {
						if (nums[r_p] < nums[min_pos]) {
							min_pos = r_p;
						}
					}
					r_p++;
				}
				// ��������Ԫ��
				swap(nums[left_pos], nums[min_pos]);
				// ����֮�� ��ǰһ��������֮������н�����������
				sort(nums.begin() + left_pos + 1, nums.end());
				break;
			}
		}
		// ����������Ѿ��������ֵ��� �������������
		if (!flag) reverse(nums.begin(), nums.end());
	}
};