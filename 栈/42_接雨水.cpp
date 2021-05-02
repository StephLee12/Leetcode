# include <iostream>
# include <vector>
# include <algorithm>
# include <queue>

using namespace std;

/*
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水
*/

class Solution {
public:
	int trap(vector<int>& height) {
		
		// Method 1 动态规划  trap_v2()优化过后
		if (height.empty()) return 0;

		int len = height.size();
		// dp数组的含义 dp[i] 以柱子i为右边界的接水总量
		vector<int> dp(len, 0);
		int max_height = height[0]; // 记录height[i]左侧最高的柱子的高度
		int max_pos = 0; // 记录height[i]左侧最高的柱子的位置

		for (int i = 1; i < len; i++) {
			if (height[i - 1] >= height[i]) {
				// 如果当前柱子高度<=前一个柱子高度
				dp[i] = dp[i - 1];
			}
			else {
				// 如果当前柱子高度>前一个柱子高度

				int rain = 0;
				if (height[i] >= max_height) {
					// 如果当前柱子高度比其左侧的最高柱子还高
					// 将max_height作为盛水容器的宽 计算max_pos:i的储水量
					rain = max_height * (i - max_pos - 1);
					for (int j = max_pos + 1; j < i; j++) {
						rain -= height[j];
					}
					dp[i] = dp[max_pos] + rain; // 状态转移

					// 更新max_height和max_pos
					max_height = height[i];
					max_pos = i;
				}
				else {
					// 当前柱子高度没有max_height高
					// 将height[i]作为盛水容器的宽 向左搜索 只要搜索到比height[i]高的柱子就停止 并计算储水量
					for (int j = i - 1; j >= 0; j--) {
						if (height[j] >= height[i]) {
							rain += (height[i] * (i - j - 1));
							dp[i] = dp[j] + rain;
							break;
						}
						else {
							rain -= height[j];
						}
					}
				}

			}

		}

		return dp[len - 1];
	}

	int trap_v2(vector<int>& height) {
		// 动态规划 未优化
		if (height.empty()) return 0;

		int len = height.size();
		// dp数组的含义 dp[i] 以柱子i为右边界的接水总量
		vector<int> dp(len, 0);

		for (int i = 1; i < len; i++) {
			if (height[i - 1] >= height[i]) {
				// 如果当前柱子高度<=前一个柱子高度
				dp[i] = dp[i - 1];
			}
			else {
				// 向左搜索有没有比当前柱子高度更高的(或相等)
				queue<int> que; // 队列 存储向左搜索的柱子高度
				que.push(height[i - 1]);

				int max_height = height[i - 1]; // 记录height[i]左侧最高的柱子的高度
				int max_pos = i - 1; // 记录height[i]左侧最高的柱子的位置 即当前第二高
				int rain = 0; // 队列内储水量
				bool find_flag = false;
				for (int p = i - 2; p >= 0; p--) {
					if (height[p] >= height[i]) {
						// height[i]左侧存在更高(或相等)的柱子

						// 计算当前栈内的储水量
						rain = height[i] * que.size();
						while (!que.empty()) {
							rain -= que.front();
							que.pop();
						}

						dp[i] = rain + dp[p]; // 状态转移
						find_flag = true; // 找到目标柱子
						break;
					}
					else {
						que.push(height[p]);
						if (height[p] > max_height) {
							max_height = height[p];
							max_pos = p;
						}
					}
				}

				// 如果没找到比height[i]高(或相等)的柱子 计算第二高到height[i]的储水量
				if (!find_flag) {
					rain = max_height * (i - max_pos - 1);
					for (int p = 0; p < i - max_pos - 1; p++) {
						rain -= que.front();
						que.pop();
					}
					dp[i] = dp[max_pos] + rain;
				}

			}

		}

		return dp[len - 1];
	}

	// Method 2 单调栈
	int trap_v2(vector<int>& height) {

	}
};

int main() {
	Solution obj;
	vector<int> test(12, 0);
	for (int i = 0; i < 12; i++) {
		cin >> test[i];
	}
	
	return obj.trap(test);
}