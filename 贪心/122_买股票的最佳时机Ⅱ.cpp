# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
给定一个数组，它的第 i 个元素是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

*/

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		// Method 2 动态规划
		int len = prices.size();

		// dp[i]的含义 前i天的最大利润
		vector<int> dp(len, 0);

		// 注意股票要在第一天买卖掉 后一天卖掉 当天买卖没收益
		for (int i = 1; i < len; i++) {
			// 状态转移方程 
			// 如果当天的价格小于前一天的价格 则不进行任何交易
			// 如果当天的价格大于前一天的价格 则该股票必在当天卖出
			// 存在几种可能
			// 1. dp[i-1]>0 
			// 1.a.若股票是在i-1天卖出 在某一天设为j买入 则dp[i-1]=prices[i-1]-prices[j] 
			//	   而dp[i]=dp[i-1]+prices[i]-price[i-1]=prices[i]-prices[j]一定高于dp[i-1]
			// 1.b 若股票不是在i-1天卖出 则显然在i-1天买入 i天卖出会增加总收益
			// 2. dp[i-1]==0 说明i-1天前的元素都比i-1天的大 则在i-1天买入 i天卖出收益最高
			// 其实从这里分析 可以发现 只要此天比前一天高 就执行前一天买入 后一天卖出 => 贪心
			dp[i] = max(dp[i - 1], (prices[i] > prices[i - 1] ? dp[i - 1] + prices[i] - prices[i - 1] : 0));
		}

		return dp[len - 1];
	}

	int maxProfit(vector<int>& prices) {
		// Method 2 贪心
		int len = prices.size();
		int max_money = 0;
		for (int i = 1; i < len; i++) {
			max_money += max(0, prices[i] - prices[i - 1]);
		}
		return max_money;
	}
};