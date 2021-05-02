# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标
*/


class Solution {
public:
	bool canJump(vector<int>& nums) {
		
		// Method 1 贪心
		int len = nums.size();
		int max_pos = 0;
		int end = 0;

		// 注意这里循环的结束条件 是i<=len-1
		for (int i = 0; i <= len - 1; i++) {
			// 若nums[i]可达 说明num[i+1]~nums[i+nums[i]]都是可达的
			// 维护可达最右位置
			if (i <= max_pos) {
				max_pos = max(max_pos, i + nums[i]);
				if (max_pos >= len - 1) return true;
			}
			else break; // 如果i>max_pos 说明当前可达最右位置的值为0 不可以继续跳跃
		}
		return false;


		/*
		// Method 2 动态规划 呜呜呜 超时了
		int len = nums.size();

		vector<bool> dp(len, false);
		dp[0] = true;

		int pos = 0;
		for (int i = 1; i < len; i++) {
			for (int j = 0; j < nums[i - 1]; j++) {
				// 记录到nums[i+j]的最少跳
				dp[i + j] = dp[i - 1] || dp[i + j];
				// 若已经搜索到右边界 直接返回
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

