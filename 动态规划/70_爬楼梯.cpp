# include <vector>
# include <algorithm>
# include <iostream>

using namespace std;

/*
������������¥�ݡ���Ҫ n ������ܵ���¥����

ÿ��������� 1 �� 2 ��̨�ס����ж����ֲ�ͬ�ķ�����������¥���أ�
*/

class Solution {
public:
	int climbStairs(int n) {
		// Method 1 ��̬�滮  �������
		if (n == 1) return 1;
		if (n == 2) return 2;

		vector<int> dp(n);
		dp[0] = 1; dp[1] = 2;
		for (int i = 2; i < n; i++) dp[i] = dp[i - 1] + dp[i - 2];
		return dp[n - 1];
	}
};