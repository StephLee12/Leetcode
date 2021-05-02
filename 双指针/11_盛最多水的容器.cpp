# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。

在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。

找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器

*/

class Solution {
public:
	// Method 1 双指针
	int maxArea(vector<int>& height) {
		int len = height.size();
		int l_p = 0; int r_p = len - 1;
		int max_area = 0;
		while (l_p < r_p) {
			// 盛水的多少 一定是取决于矮的柱子
			max_area = max(max_area,min(height[l_p], height[r_p]) * (r_p - l_p));
			// 所以 哪根柱子矮 哪边的指针就要移动
			if (height[l_p] <= height[r_p]) l_p++;
			else r_p--;
		}
		return max_area;
	}
	// Method 2 动态规划 没法用动态规划做 不具备转移特性
	int maxArea(vector<int>& height) {
		int len = height.size();
		vector<int> dp(len); // i前的柱子中的最大盛水面积
		dp[0] = 0;
	}
};