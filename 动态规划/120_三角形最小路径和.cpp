# include <vector>
# include <iostream>
# include <algorithm>

using namespace std;

/*
����һ�������� triangle ���ҳ��Զ����µ���С·���͡�

ÿһ��ֻ���ƶ�����һ�������ڵĽ���ϡ����ڵĽ�� ������ָ���� �±� �� ��һ�����±� ��ͬ���ߵ��� ��һ�����±� + 1 ��������㡣

Ҳ����˵�������λ�ڵ�ǰ�е��±� i ����ô��һ�������ƶ�����һ�е��±� i �� i + 1

*/

class Solution {
public:
	int minimumTotal(vector<vector<int>>& triangle) {
		int t_height = triangle.size();

		// dp�ĺ��� ���õ�����·������
		vector<vector<int>> dp;
		for (int i = 0; i < t_height; i++) dp.push_back(vector<int>(triangle[i].size()));
		dp[0][0] = triangle[0][0]; // ��ʼ��

		for (int i = 1; i < t_height; i++) {
			int now_len = triangle[i].size();
			int prev_len = triangle[i - 1].size();
			for (int j = 0; j < now_len; j++) {
				// ��ȡ�����ߵ���ǰλ��i,j���ϲ���������
				int first = (j - 1 >= 0 ? dp[i - 1][j - 1] : INT_MAX);
				int second = (j <= prev_len - 1 ? dp[i - 1][j] : INT_MAX);
				dp[i][j] = min(first,second) + triangle[i][j];
 			}
		}
		
		// �����һ�����ҵ���Сֵ ��Ϊ�Զ����µ����·��
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