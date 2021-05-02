# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
����һ���Ǹ��������� nums �������λ������� ��һ���±� ��

�����е�ÿ��Ԫ�ش������ڸ�λ�ÿ�����Ծ����󳤶ȡ�

�ж����Ƿ��ܹ��������һ���±�
*/


class Solution {
public:
	bool canJump(vector<int>& nums) {
		
		// Method 1 ̰��
		int len = nums.size();
		int max_pos = 0;
		int end = 0;

		// ע������ѭ���Ľ������� ��i<=len-1
		for (int i = 0; i <= len - 1; i++) {
			// ��nums[i]�ɴ� ˵��num[i+1]~nums[i+nums[i]]���ǿɴ��
			// ά���ɴ�����λ��
			if (i <= max_pos) {
				max_pos = max(max_pos, i + nums[i]);
				if (max_pos >= len - 1) return true;
			}
			else break; // ���i>max_pos ˵����ǰ�ɴ�����λ�õ�ֵΪ0 �����Լ�����Ծ
		}
		return false;


		/*
		// Method 2 ��̬�滮 ������ ��ʱ��
		int len = nums.size();

		vector<bool> dp(len, false);
		dp[0] = true;

		int pos = 0;
		for (int i = 1; i < len; i++) {
			for (int j = 0; j < nums[i - 1]; j++) {
				// ��¼��nums[i+j]��������
				dp[i + j] = dp[i - 1] || dp[i + j];
				// ���Ѿ��������ұ߽� ֱ�ӷ���
				if (i + j == len - 1 && dp[len-1]) {
					break;
				}
			}
			if (dp[len-1]) {
				break;
			}
		}

		return dp[len-1];
		*/

	}
};

int main() {
	vector<int> test = { 3,2,1,0,4 };
	Solution obj;
	bool res = obj.canJump(test);

	return (res ? 1 : 0);

}

