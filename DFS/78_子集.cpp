# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
����һ���������� nums �������е�Ԫ�� ������ͬ �����ظ��������п��ܵ��Ӽ����ݼ�����

�⼯ ���� �����ظ����Ӽ�������԰� ����˳�� ���ؽ⼯
*/

class Solution {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		// Method 1 �ݹ�DFS
		int len = nums.size();

		vector<vector<int>> res;
		// ���Ƚ��ռ�������
		res.push_back(vector<int>());

		// ��nums�������� Ϊ��ʹ�õ��ļ���������
		sort(nums.begin(), nums.end());

		vector<int> subset; // ��¼dfsʱ�ļ���
		for (int i = 0; i < len; i++) {
			// ��nums���б��� nums[i]��Ϊ��������С��Ԫ��
			subset.push_back(nums[i]);
			dfs(nums, res, subset, i, len);
			subset.pop_back(); // ע��dfs����֮��Ҫpop �Ա���һ��ѭ����dfs
		}

		return res;
	}

	void dfs(vector<int>& nums, vector<vector<int>>& res, vector<int>& vec, int pos, const int len) {
		// pos������ǰdfs��������λ��
		if (pos == len) return;  // ���pos����nums�ұ߽� ����dfs
		res.push_back(vec); // ����ǰ���ϼ�����

		for (int i = pos + 1; i < len; i++) {
			vec.push_back(nums[i]);
			dfs(nums, res, vec, i, len);
			vec.pop_back();
		}
	}
};