# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
����һ���������� nums ���ҵ�һ���������͵����������飨���������ٰ���һ��Ԫ�أ�
����������
*/

class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		// Method 1 ��̬�滮
		int len = nums.size();
		// ֱ����nums�϶�̬�滮 ��nums[i]Ϊ�ұ߽������
		int max_val = nums[0];
		for (int i = 1; i < len; i++) {
			if (nums[i - 1] + nums[i] > nums[i]) {
				// ��nums[i]ǰ���������ͼ���nums[i]>nums[i]
				// ��Ҫ����nums[i]
				nums[i] += nums[i-1];	
			}
			// �жϵ�ǰ��nums[i]Ϊ�ұ߽������ �Ƿ����
			if (nums[i] > max_val) max_val = nums[i];
		}

		return max_val;
	}
};