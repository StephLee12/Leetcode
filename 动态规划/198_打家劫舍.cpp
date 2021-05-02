# include <vector>
# include <algorithm>

using namespace std;

/*
����һ��רҵ��С͵���ƻ�͵���ؽֵķ��ݡ�

ÿ�䷿�ڶ�����һ�����ֽ�Ӱ����͵�Ե�Ψһ��Լ���ؾ������ڵķ���װ���໥��ͨ�ķ���ϵͳ��

����������ڵķ�����ͬһ���ϱ�С͵���룬ϵͳ���Զ�������

����һ������ÿ�����ݴ�Ž��ķǸ��������飬

������ ����������װ�õ������ ��һҹ֮���ܹ�͵�Ե�����߽�

*/

class Solution {
public:
	int rob(vector<int>& nums) {
		// Method 1 ��̬�滮
		
		int len = nums.size();
		if (len == 0) return 0;
		if (len == 1) return nums[0];

		// dp[i]Ϊi֮ǰ�����������
		vector<int> dp(nums.begin(),nums.end());
		// ��ʼ��
		dp[0] = nums[0];
		dp[1] = max(nums[0], nums[1]);

		for (int i = 2; i < len; i++) {
			/*
			����λ��i��˵ С͵i-1��i-2�б���һ��
			�������i-1�� dp[i-1] > dp[i-2] ���Ͳ�����i��
			�������i-2�� ������i-1 dp[i-1]=dp[i-2] ���ǿ�����i
			����Ҫ�ж���i-1����i-2��һ������
			��״̬ת�Ʒ��� max(dp[i - 1], dp[i - 2] + nums[i])
			*/
			dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
		}

		return dp[len - 1];
	}
};

int main() {
	// vector<int> test{1,2,3,1};
	vector<int> test{ 2,7,9,3,1 };
	Solution obj;
	obj.rob(test);
	return 0;
}