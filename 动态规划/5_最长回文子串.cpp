# include <algorithm>
# include <string>
# include <iostream>
# include <vector>

using namespace std;

// �ҵ�s��������Ӵ�������

class Solution {
public:
	string longestPalindrome(string s) {
		
		// Method 1 ��̬�滮
		int len = s.length();

		if (len == 1) return s;

		// ����dp���� dp[i][j]��ʾ�ӵ�i+1���ַ�����j+1���ַ��Ƿ��ǻ��Ĵ�
		vector<vector<int>> dp(len,vector<int>(len,0));

		for (int i = 0; i < len; i++) dp[i][i] = 1; // һ���ַ�������Ȼ�ǻ��Ĵ�

		int max_len = 1;
		int start_pos = 0;
		// Ѱ������Ĵ� ʱ�临�Ӷ�n^2
		// ѭ�������� Ҫ����dp�����˳�� ��dp[i][j]=dp[i+1][j-1]�ĺϷ���
		for (int j = 0; j < len;j++) {
			for (int i = 0; i <= j;i++) {
				if (s[i] == s[j]) {
					// ��s[i]==s[j] ����s[i+1:j-1]�Ƿ��ǻ��Ĵ� ͬʱҪ��������߽粻��Խ�� ��j-1>=i+1
					if (j - i >= 2) dp[i][j] = dp[i+1][j-1];
					else dp[i][j] = 1;

					// ���dp[i][j]==1
					// ���㵱ǰ�Ӵ��ĳ����Ƿ����
					if (dp[i][j]) {
						int cur_len = j - i + 1;
						if (cur_len > max_len) {
							max_len = cur_len;
							start_pos = i;
						}
					}

				}
			}
		}

		return s.substr(start_pos, max_len);

	}
};