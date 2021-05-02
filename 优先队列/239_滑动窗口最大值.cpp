# include <queue>
# include <vector>
# include <algorithm>

using namespace std;


/*
给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。

你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回滑动窗口中的最大值。

*/

class Solution {
public:
	// Method 1 优先队列
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		int len = nums.size();
		if (len <= 1) return nums;

		priority_queue<pair<int, int>> q; // 大顶堆
		// 先将窗口滑至长度k
		for (int i = 0; i < k; i++) {
			// pair第一个元素为值 第二个为值所在的位置
			q.push(pair<int,int>{ nums[i],i }); 
		}

		vector<int> res{ q.top().first };
		// 开始移动窗口
		for (int i = k; i < len; i++) {
			q.push(pair<int,int>{ nums[i],i });
			// 注意这里 如果最大值不在当前滑动窗口内 要将其从队列中移除
			while (q.top().second <= i - k) {
				q.pop();
			}
			res.push_back(q.top().first);
		}
		return res;
	}

	// Method 2 单调递减栈 使用双端队列deque
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		int len = nums.size();
		if (len <= 1) return nums;

		deque<int> q; // 双端队列中存储的是元素的位置 位置对应的值始终递减
		for (int i = 0; i < k; i++) {
			while (!q.empty() && nums[i] >= nums[q.back()]) {
				q.pop_back(); // 保持单调递减
			}
			q.push_back(i);
		}

		vector<int> res{ nums[q.front()] };
		for (int i = k; i < len; i++) {
			while (!q.empty() && nums[i] >= nums[q.back()]) {
				q.pop_back(); // 保持单调递减
			}
			q.push_back(i); // 窗口移动
			// 如果最大值不在窗口内 移除双端队列头部
			if (q.front() == i - k) {
				q.pop_front();
			}
			res.push_back(nums[q.front()]);
		}
		return res;
	}
};