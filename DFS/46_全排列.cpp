# include <vector>
# include <algorithm>
# include <iostream>

using namespace std;

/*

����һ�� û���ظ� ���ֵ����У����������п��ܵ�ȫ����

*/

class Solution {
public:
	vector<vector<int>> permute(vector<int>& nums) {
		// Method 1 DFS�ݹ� ��39�� ����ܺ��е�����
		int len = nums.size();

		if (len == 0) return vector<vector<int>>();

		vector<vector<int>> res;
		vector<int> seq;
		dfs(res, seq, nums,0, len);

		return res;
	}

	void dfs(vector<vector<int>>& res, vector<int>& seq, vector<int>& nums ,int cnt ,int len) {
		if (cnt == len) {
			// ��seq�������������г���ʱ ֹͣ�ݹ� ��seq������
			res.push_back(seq);
			return;
		}

		// ��seq�е�Ԫ�ض�Ӧ��nums���ΪINT_MAX ��ֹ�ٴα���
		for (int i = 0; i < len; i++) {
			if (nums[i] == INT_MAX) continue; // nums[i]�Ѿ���seq�г���

			int tmp = nums[i]; // �ȱ���nums[i]������ֵ
			seq.push_back(nums[i]);
			nums[i] = INT_MAX; // ��nums[i]��ֵ ��ΪINT_MAX
			dfs(res, seq, nums, cnt + 1, len);
			nums[i] = tmp; // ��ǰdfs��� �ָ�nums[i]��ֵ ׼���¸�ѭ����dfs
			seq.pop_back(); // ����ѹ��seq��nums[i]
		}
	}
};