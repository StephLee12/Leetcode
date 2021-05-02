# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;


/*
题目描述：
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [start_i, end_i] 
请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间
*/

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		// 先按照区间的第一个元素对intervals排序
		int len = intervals.size(); // 二维数组的长度

		// 特殊情况
		if (len == 1) {
			return intervals;
		}

		vector<vector<int>> res; // 返回结果

		// 手撸一遍快排 也可直接用sort()函数
		QuickSort(intervals, 0, len - 1); 

		int l_p = 0; // 左指针
		int r_p = 1; // 右指针

		//双指针搜索
		while (r_p <= len - 1) {
			// 遍历区间左端均为intervals[l_p][0]的元素 并获得区间右端的最大值
			int max_r = intervals[l_p][1];
			while (r_p <= len-1 && intervals[r_p][0] == intervals[l_p][0]) {
				if (intervals[r_p][1] > max_r){
					max_r = intervals[r_p][1];
				}
				r_p++;
			}
			// 要判断r_p是否越界
			if (r_p > len - 1) {
				// 如果r_p越界了 说明从l_p到r_p区间左端的值都相等
				// 直接获取区间右端最大值 加入结果数组 结束循环
				intervals[l_p][1] = max_r;
				res.push_back(intervals[l_p]);
				break;
			}

			// 如果没有越界
			// 比较当前r_p位置的区间左端和当前区间右端最大值
			if (intervals[r_p][0] > max_r) {
				// 当前r_p位置的区间左端 大于 当前区间右端最大值
				// 可以合并所有区间(l_p为区间左端) 加入结果数组
				intervals[l_p][1] = max_r;
				res.push_back(intervals[l_p]);
				l_p=r_p; // 更新l_p指针
				// r_p++;
			}
			else {
				// 当前r_p位置的区间左端 小于 当前区间右端最大值
				max_r = max(intervals[r_p][1], max_r);
				// 合并区间
				// 注意！此时不能加入结果数组 更新intervals[r_p]的值
				intervals[r_p][0] = intervals[l_p][0];
				intervals[r_p][1] = max_r;
				l_p = r_p; // 更新l_p指针
			}
		}

		return res;
		
	}

	// 快排
	void QuickSort(vector<vector<int>>& intervals, int low, int high) {
		if (low < high) {
			// 计算枢轴的位置
			int pivot_pos = Partition(intervals, low, high);
			QuickSort(intervals, low, pivot_pos); // 枢轴左侧递归
			QuickSort(intervals, pivot_pos + 1, high); // 枢轴右侧递归
		}
	}

	int Partition(vector<vector<int>>& intervals, int low, int high) {
		vector<int> pivot = intervals[low]; // 设置intervals[low:high]的第一个元素为枢轴

		while (low < high) {
			// 右指针向左搜索 找到小于枢轴的元素
			while (low < high && intervals[high][0] >= pivot[0]) {
				high--;
			}
			intervals[low] = intervals[high];
			// 左指针向右搜索 找到大于枢轴的元素
			while (low < high && intervals[low][0] <= pivot[0]) {
				low++;
			}
			intervals[high] = intervals[low];
		}
		// 最后确定枢轴的位置
		intervals[low] = pivot;
		return low;

	}
};

int main() {
	Solution obj;
	vector<vector<int>> res;
	vector<vector<int>> vec(4, vector<int>(2));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			cin >> vec[i][j];
		}
	}
	res = obj.merge(vec);
	return 0;
}