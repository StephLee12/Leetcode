# include <vector>
# include <algorithm>
# include <iostream>

using namespace std;

/*

给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

*/

class Solution {
public:
	// Method 1 暴力解法 先排序
	int majorityElement(vector<int>& nums) {
		int len = nums.size();

		sort(nums.begin(), nums.end());
		int mostElem = nums[0];
		int cnt = 1;
		for (int i = 1; i < len; i++) {
			if (nums[i] == nums[i - 1]) {
				cnt++;
				// 检查该元素是否是多数元素
				if ((double)(cnt) > (double)(len) / 2) {
					mostElem = nums[i];
					break;
				}
			}
			else {
				cnt = 1;
			}
		}

		return mostElem;
	}
	// Method 2 Boyer-Moore投票算法
	/*
	维护一个候选众数mode和它出现的次数cnt  初始时mode可以为任意值 cnt为0
	遍历nums 对于其中的每个元素x 
	在判断之前如果cnt为0 先将x赋予mode 
	随后判断 若x与mode相等 cnt+1 若不相等cnt-1
	*/
	int majorityElement(vector<int>& nums) {
		int mode = -1;
		int cnt = 0;
		for (auto&& num : nums) {
			if (cnt == 0) mode = num;
			cnt += (num == mode) ? 1 : -1;
		}
		return mode;
	}
};

int main() {
	vector<int> test{ 2,2,1,1,1,2,2 };
	Solution obj;
	obj.majorityElement(test);
	return 0;
}