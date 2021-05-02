# include <vector>
# include <algorithm>
# include <iostream>

using namespace std;

/*
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
		int len = prices.size();

		if (len==1) return 0;

		// 维护一个最小价格就可以 因为只进行一次买卖
		int max_profit = INT_MIN;
		int min_price = INT_MAX;

		for (int i = 0; i < len; i++) {
			min_price = min(prices[i], min_price);
			max_profit = max(max_profit, prices[i] - min_price > 0 ? prices[i] - min_price : 0);
		}
		return max_profit;

		//vector<int> dp(len,INT_MAX);
		//int max_val = INT_MIN;

		//for (int i = 1; i < len; i++) {
		//	// 记录i前面最小的元素
		//	dp[i] = min(dp[i - 1], prices[i - 1]);
		//	max_val = max(max_val, prices[i]-dp[i]>0?prices[i]-dp[i]:0);
		//}


		//return max_val;
    }
};