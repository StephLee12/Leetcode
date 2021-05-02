# include <vector>
# include <algorithm>
# include <iostream>

using namespace std;

/*
����һ���Ǹ��������飬�����λ������ĵ�һ��λ�á�

�����е�ÿ��Ԫ�ش������ڸ�λ�ÿ�����Ծ����󳤶ȡ�

���Ŀ����ʹ�����ٵ���Ծ����������������һ��λ�á�

˵��:
���������ǿ��Ե�����������һ��λ��
*/




class Solution {
public:
	int jump(vector<int>& nums) {
		
		// Method 1 ̰�� ���
		int len = nums.size();
		int max_pos = 0;
		int jump_times = 0;
		int right_bound = 0;

		// ѭ������Ҫ����nums���һ��Ԫ�� ��Ϊmax_posһ��>=len-1
		// �����޷������һ��λ��
		for (int i = 0; i <= len - 2; i++) {
			// max_pos��¼������һ�������ߵ������
			// end��¼���ǵ�ǰ���������ߵ����ֵ
			// ��i-end��Ѱ����һ�������ֵ ���߽�ʱ���±߽� �ٴ�̰��
			max_pos = max(max_pos, i + nums[i]);
			if (i == right_bound) {
				// ÿ�α������˱߽� ���±߽�
				right_bound = max_pos;
				jump_times++; // ע��ʱ��������Ծ���� �������¸���������ֵ
			}
		}
		return jump_times;


		//// Method 1 ̰�� �Լ�д�� �����whileѭ���е���
		//int len = nums.size();
		//int p = 0;// ɨ������ָ��
		//int jump = 0;// ��¼������Ծ����

		//// �о����whileѭ���е����� ���nums[p]==0����ѭ���� ��֪��Ϊɶ�ܹ�
		//while (p != len - 1) {
		//	int next_pos = 0;// ��¼�¸���ת����λ��
		//	int max_pos = 0; // ��¼�����ת��ĳλ�� ���Ե������Զλ��
		//	for (int i = 1; i <= nums[p]; i++) {
		//		//������ǰλ��p ���������п���
		//		if (p + i < len && p + i + nums[p + i] >= max_pos) {
		//			// ��Զλ�ò��ܳ��������ұ߽�
		//			max_pos = min(p + i + nums[p + i], len - 1);
		//			next_pos = p + i;
		//		}
		//	}
		//	// p���� ̰�ĵ��ص����ֻ���ĵ�ǰ�ľֲ����� û��������ʷ��Ϣ
		//	// ���ڴ�����˵ ������������ȫ�����ŵ� �������ֲ����ż�Ϊȫ������
		//	// ��һ�������̰�Ĳ��ܱ�֤���һ��ȫ������
		//	p = next_pos;
		//	jump++;
		//}

		//return jump;

	}

	
	int jump_v2(vector<int>& nums) {
		// Method 2 ��̬�滮 �е����Ϊɶ���ᳬʱ������ 55��dp���ᳬʱ
		int len = nums.size();
		const int INF = 0x3f3f3f3f;
		// dp[i]�ĺ��� ��i��Ҫ��������
		vector<int> dp(len, INF);
		dp[0] = 0;

		for (int i = 1; i < len; i++) {
			for (int j = 0; j < nums[i - 1]; j++) {
				// ��¼��nums[i+j]��������
				dp[i + j] = min(dp[i - 1] + 1, dp[i + j]);
				// ���Ѿ��������ұ߽� ֱ�ӷ��� ��ʱ��Ȼ��������
				if (i + j == len-1) goto End;
			}
		}

		End:return dp[len-1];
	}
};
