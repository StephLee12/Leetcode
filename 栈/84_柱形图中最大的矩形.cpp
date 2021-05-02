# include <vector>
# include <algorithm>
# include <iostream>
# include <stack>

using namespace std;

/*
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

*/

class Solution {
public:
	// Method 1 单调栈 自己写的栈中存的是柱子高度
	int largestRectangleArea(vector<int>& heights) {
		
		int len = heights.size();

		// 边界情况
		if (len == 0) return 0;
		if (len == 1) return heights[0];

		vector<int> vec(len); // 记录高度
		vec[0]=heights[0];

		int max_area = heights[0]; //初始化
		for (int i = 1; i < len; i++) {
			vec[i] = heights[i]; // 记录当前柱子高度
			// 如果当前高度>=前一个高度 则继续循环
			if (heights[i - 1] <= heights[i]) continue;
			else { 
				// 如果当前高度<前一个高度 
				for (int j = i - 1; j >= 0; j--) {
					if (heights[j] <= heights[i]) break; // vec向前回溯至高度<=当前高度
					int tmp_area = (i - 1 - j + 1) * vec[j]; // 回溯过程中计算以柱子j为高 (i-1-j+1)为底的矩形面积
					max_area = max(max_area, tmp_area);
					vec[j] = heights[i]; // 将回溯过程中所有>当前高度的柱子 都置为当前高度
				}
			}
		}

		// 遍历完一次heights后 此时栈是单调的
		// 从后向前遍历 
		
		int r_p = len - 1;
		int l_p = r_p;


		/*
		while (r_p >= 0) {
			if (vec[r_p] == 0) break;  // 如果遇到vec的元素为0 直接break 因为遇到的第一个0元素之前的所有元素均为0
			max_area = max(max_area, (len - 1 - r_p + 1) * vec[r_p]);
			r_p--;
		}
		*/
		
		while (l_p >= 0) {
			// 优化一下
			if (vec[l_p] == 0) break;
			while (l_p >= 0 && vec[l_p] == vec[r_p]) l_p--; // 相同的元素可以直接跳过
			max_area = max(max_area, (len - 1 - l_p) * vec[r_p]);
			r_p = l_p;
		}

		return max_area;
	}

	// Method 2 题解单调栈 栈中存的是下标 相较于自己写的更优
	int largestRectangleArea(vector<int>& heights) {
		int len = heights.size();
		if (len == 0) return 0;
		if (len == 1) return heights[0];

		int max_area = 0;
		stack<int> stk;
		for (int i = 0; i < len; i++) {
			while (!stk.empty() && heights[stk.top()] > heights[i]) {
				// 注意循环的第二个条件是严格大于
				int h = heights[stk.top()]; // 矩形的高
				stk.pop();
				int l = i ; // 矩形的长
				
				// 要注意如果栈不为空 矩形的长为已经弹出的下标到当前栈顶下标的距离
				if (!stk.empty()) l = i-1-stk.top();
				max_area = max(max_area, l * h);
			}
			stk.push(i);
		}

		while (!stk.empty()) {
			int h = heights[stk.top()];
			stk.pop();
			int l = len;
			
			if (!stk.empty()) l = len-1-stk.top();
			max_area = max(max_area, l * h);
		}

		return max_area;
	}
};

int main() {
	vector<int> test{0,2,0 };
	Solution obj;
	obj.largestRectangleArea(test);
	return 0;
}