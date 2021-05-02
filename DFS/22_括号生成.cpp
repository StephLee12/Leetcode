# include <iostream>
# include <vector>
# include <string>
# include <algorithm>
# include <stack>
# include <unordered_map>

using namespace std;

/*
���� n �����������ŵĶ������������һ�������������ܹ��������п��ܵĲ��� ��Ч�� �������
*/


class Solution {
public:
	vector<string> generateParenthesis(int n) {
		// Method 1 DFS�ݹ�
		vector<string> res;
		// dfs(res, "", n,2*n,0);
		dfs(res, "", n, n);
		return res;
	}

	void dfs(vector<string>& res, string s, int l_num, int r_num) {
		// l_num ������ʣ����Ŀ r_num ������ʣ����Ŀ
		if (l_num == 0 && r_num == 0) {
			// ���ҽ�������������Ŀ��Ϊ0 ��һ����Ч����
			res.push_back(s);
			return;
		}

		if (l_num == r_num) dfs(res, s+"(", l_num - 1, r_num); // ����������������� ��һ��ֻ����������
		else if (l_num < r_num) {
			// �������������С�������� �¸����żȿ����������� Ҳ������������
			if (l_num > 0) dfs(res, s + "(", l_num - 1, r_num);
			dfs(res, s + ")", l_num, r_num - 1);
		}
		// �������������������� ��Ȼ����һ����Ч����
	}

	/*
	void dfs(vector<string>& res, string s, const int pair_num,int rest_len,int match_time) {
		// match_time��¼ƥ��Ĵ���
		if (rest_len == 0) {
			if (match_time == pair_num) res.push_back(s);
			return;
		}

		int len = s.size();

		dfs(res, s + "(", pair_num, rest_len - 1, match_time);
		if ((len - 1 >= 0 && s[len - 1] == '(')) dfs(res, s + ")", pair_num, rest_len - 1, match_time + 1);
		else if (len - 1 >= 0 && s[len - 1] == ')') {
			for (int i = 1; i <= match_time; i++) {
				if (len - 1- match_time * 2 >= 0 && s[len - 1- match_time * 2] == '(') {
					dfs(res, s + ")", pair_num, rest_len - 1, match_time + 1);
					break;
				}
			}
		}
	}
	*/
	
};

int main() {
	Solution obj;
	obj.generateParenthesis(3);
	return 0;
}