# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

*/

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		// Method 1 双指针 
		/*
		对于这种三元组的 要固定一个 再用双指针  这样就退化成两数之和 有一个固定的target
		*/
		int len = nums.size();
		if (len <= 2) return vector<vector<int>>(); // 边界情况

		// 先对nums排序
		sort(nums.begin(), nums.end());

		vector<vector<int>> res;
		int p = 0;
		while (p < len && nums[p] <= 0) {
			int fix_num = nums[p];
			int l_p = p + 1; int r_p = len - 1;
			while (r_p - l_p >= 1) {
				// 双指针夹逼
				if (nums[l_p] + nums[r_p] == -fix_num) {
					// 找到对应的三元组
					res.push_back(vector<int>{fix_num, nums[l_p], nums[r_p]});
					// 左右指针分别移动 且跳过相同元素
					while (r_p - 1 >= 0 && nums[r_p - 1] == nums[r_p]) r_p--;
					while (l_p + 1 < len && nums[l_p + 1] == nums[l_p]) l_p++;
					r_p--; l_p++;
				}
				else if (nums[l_p] + nums[r_p] > -fix_num) r_p--; // 右指针左移
				else l_p++;  // 左指针右移
			}
			// 固定的指针p移动 跳过相同元素
			while (p + 1 < len && nums[p + 1] == nums[p]) p++;
			p++;
		}

		return res;
	}
};

int main() {
	vector<int> test{ -1,0,1,2,-1,-4 };
	Solution obj;
	obj.threeSum(test);
	return 0;
}