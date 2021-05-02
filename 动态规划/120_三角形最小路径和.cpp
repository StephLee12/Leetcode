# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
给定一个三角形 triangle ，找出自顶向下的最小路径和。

每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与 上一层结点下标 相同或者等于 上一层结点下标 + 1 的两个结点。

也就是说，如果正位于当前行的下标 i ，那么下一步可以移动到下一行的下标 i 或 i + 1

*/

class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		int t_height = triangle.size();

		// dp的含义 到该点的最短路径长度
		vector<vector<int>> dp;
		for (int i = 0; i < t_height; i++) dp.push_back(vector<int>(triangle[i].size()));
		dp[0][0] = triangle[0][0]; // 初始化

		for (int i = 1; i < t_height; i++) {
			int now_len = triangle[i].size();
			int prev_len = triangle[i - 1].size();
			for (int j = 0; j < now_len; j++) {
				// 获取可以走到当前位置i,j的上层的两个结点
				int first = (j - 1 >= 0 ? dp[i - 1][j - 1] : INT_MAX);
				int second = (j <= prev_len - 1 ? dp[i - 1][j] : INT_MAX);
				dp[i][j] = min(first,second) + triangle[i][j];
 			}
		}
		
		// 在最后一层中找到最小值 即为自顶向下的最短路径
		return *min_element(dp[t_height-1].begin(),dp[t_height-1].end());
	}
};	

int main() {
	vector<vector<int>> test;
	test.push_back(vector<int>{2});
	test.push_back(vector<int>{3,4});
	test.push_back(vector<int>{6,5,7});
	test.push_back(vector<int>{4,1,8,3});
	Solution obj;
	obj.minimumTotal(test);
	return 0;
}