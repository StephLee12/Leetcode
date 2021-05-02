# include <vector>
# include <algorithm>
# include <iostream>

using namespace std;

/*
给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

说明:
假设你总是可以到达数组的最后一个位置
*/




class Solution {
public:
	int jump(vector<int>& nums) {
		
		// Method 1 贪心 题解
		int len = nums.size();
		int max_pos = 0;
		int jump_times = 0;
		int right_bound = 0;

		// 循环不需要访问nums最后一个元素 因为max_pos一定>=len-1
		// 否则无法到最后一个位置
		for (int i = 0; i <= len - 2; i++) {
			// max_pos记录的是下一步可以走的最大步数
			// end记录的是当前步数可以走的最大值
			// 在i-end中寻找下一步的最大值 到边界时更新边界 再次贪心
			max_pos = max(max_pos, i + nums[i]);
			if (i == right_bound) {
				// 每次遍历到了边界 更新边界
				right_bound = max_pos;
				jump_times++; // 注意时先增加跳跃次数 再搜索下个区间的最大值
			}
		}
		return jump_times;


		//// Method 1 贪心 自己写的 下面的while循环有点拉
		//int len = nums.size();
		//int p = 0;// 扫描数组指针
		//int jump = 0;// 记录最少跳跃次数

		//// 感觉这个while循环有点问题 如果nums[p]==0就死循环了 不知道为啥能过
		//while (p != len - 1) {
		//	int next_pos = 0;// 记录下个跳转到的位置
		//	int max_pos = 0; // 记录如果跳转到某位置 可以到达的最远位置
		//	for (int i = 1; i <= nums[p]; i++) {
		//		//遍历当前位置p 能跳的所有可能
		//		if (p + i < len && p + i + nums[p + i] >= max_pos) {
		//			// 最远位置不能超过数组右边界
		//			max_pos = min(p + i + nums[p + i], len - 1);
		//			next_pos = p + i;
		//		}
		//	}
		//	// p更新 贪心的特点就是只关心当前的局部最优 没有利用历史信息
		//	// 对于此题来说 这样搜索就是全局最优的 即到最后局部最优即为全局最优
		//	// 但一般情况下贪心不能保证最后一定全局最优
		//	p = next_pos;
		//	jump++;
		//}

		//return jump;

	}

	
	int jump_v2(vector<int>& nums) {
		// Method 2 动态规划 有点好奇为啥不会超时。。。 55题dp都会超时
		int len = nums.size();
		const int INF = 0x3f3f3f3f;
		// dp[i]的含义 到i需要的最少跳
		vector<int> dp(len, INF);
		dp[0] = 0;

		for (int i = 1; i < len; i++) {
			for (int j = 0; j < nums[i - 1]; j++) {
				// 记录到nums[i+j]的最少跳
				dp[i + j] = min(dp[i - 1] + 1, dp[i + j]);
				// 若已经搜索到右边界 直接返回 此时必然是最少跳
				if (i + j == len-1) goto End;
			}
		}

		End:return dp[len-1];
	}
};
