# include <vector>
# include <algorithm>

using namespace std;

/*
你是一个专业的小偷，计划偷窃沿街的房屋。

每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，

如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，

计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

*/

class Solution {
public:
	int rob(vector<int>& nums) {
		// Method 1 动态规划
		
		int len = nums.size();
		if (len == 0) return 0;
		if (len == 1) return nums[0];

		// dp[i]为i之前抢到的最大金额
		vector<int> dp(nums.begin(),nums.end());
		// 初始化
		dp[0] = nums[0];
		dp[1] = max(nums[0], nums[1]);

		for (int i = 2; i < len; i++) {
			/*
			对于位置i来说 小偷i-1和i-2中必抢一个
			如果抢了i-1则 dp[i-1] > dp[i-2] 但就不能抢i了
			如果抢了i-2则 不能抢i-1 dp[i-1]=dp[i-2] 但是可以抢i
			所以要判断抢i-1和抢i-2哪一个更优
			即状态转移方程 max(dp[i - 1], dp[i - 2] + nums[i])
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