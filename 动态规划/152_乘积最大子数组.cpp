# include <vector>
# include <iostream>
# include <algorithm>
# include <unordered_map>
# include <unordered_set>

using namespace std;

/*
����һ���������� nums ��

�����ҳ������г˻��������������飨�������������ٰ���һ�����֣���

�����ظ�����������Ӧ�ĳ˻�

*/

class Solution {
public:
	// Method 1 ��̬�滮 
	int maxProduct(vector<int>& nums) {
		
		int len = nums.size();
		
		// ��������ֱ��¼��i��β�����˻�����С�˻�
		// ��Ϊ���ܴ��ڸ������������
		vector<int> maxVals(nums.begin(),nums.end());
		vector<int> minVals(nums.begin(), nums.end());

		int maxVal = nums[0];
		for (int i = 1; i < nums.size(); i++) {
			// ��ǰmaxVals[i]������nums[i](maxVals[i]*nums[i]Ϊ��),nums[i]*minVals[i-1](��������)
			maxVals[i] = max({ nums[i],nums[i] * minVals[i - 1],maxVals[i - 1] * nums[i] });
			minVals[i] = min({ nums[i],nums[i] * minVals[i - 1],maxVals[i - 1] * nums[i] });
			maxVal = max(maxVal, maxVals[i]);
		}

		return maxVal;
	}

	// Method 2 ������˼· ûд����
	/*
	�����鿴���Ǳ�0��ֵ������� ���ֵ��Ϊÿ����������ֵ��max
	����ÿ�������� ���������ż���� ��ֱ������
	����������� ����߿�ʼ������һ�����ֵ ���ұ߿�ʼ������һ�����ֵ �Ƚϼ���
	*/
	int maxProduct(vector<int>& nums) {
		int len = nums.size();
		int sum = 1;
		int maxVal = nums[0];

		for (int i = 0; i < len; i++) {
			sum *= nums[i];
			maxVal = max(maxVal, sum);
			if (nums[i] == 0) sum = 1; // ���nums[i]Ϊ0 Ҫ��������
		}

		sum = 1;
		for (int i = len - 1; i >= 0; i++) {
			sum *= nums[i];
			maxVal = max(maxVal, sum);
			if (nums[i] == 0) sum = 1;
		}

		return maxVal;
	}
};