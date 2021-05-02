# include <string>
# include <iostream>
# include <vector>
# include <algorithm>
# include <unordered_set>

using namespace std;


/*
����һ���ַ��� s ��һ���ַ��� t ������ s �к��� t �����ַ�����С�Ӵ���

��� s �в����ں��� t �����ַ����Ӵ����򷵻ؿ��ַ��� "" ��

ע�⣺��� s �д����������Ӵ������Ǳ�֤����Ψһ�Ĵ𰸡�

*/

class Solution {
public:
	string minWindow(string s, string t) {
		// Method 1 ��������
		vector<int>dict(128, 0); // ��vec�䵱��ϣ�� ��¼ÿ���ַ����ֵĴ���
		for (char c : t) dict[c]++; // ����t�е�Ԫ�ؼ����ϣ��

		int cnt = t.size();
		// l_p��¼������� r_p��¼�����Ҳ� start_pos��¼��̴������ min_len��¼��̴��ĳ���
		int l_p = 0, r_p = 0, start_pos = 0, min_len = INT_MAX;
		while (r_p < s.size()) {
			char c = s[r_p];
			if (dict[c] > 0) cnt--; // ���c��t�е��ַ� cnt--
			dict[c]--; // ����ǰԪ�ؼ��봰��

			if (cnt == 0) { // �����ǰ�������Ѿ�����t
				while (l_p < r_p && dict[s[l_p]] < 0) {
					// �ƶ�l_p �������ڣ��Ƴ�����t�е��ַ���
					dict[s[l_p]]++;
					l_p++;
				}
				// ��¼��ǰ���ڵĳ��� ����С���ȱȽ�
				if (r_p - l_p + 1 < min_len) {
					min_len = r_p - l_p + 1;
					start_pos = l_p;
				}
				// �ı䵱ǰ���ڵ���� ������һ��ѭ�� �����������䴰��
				dict[s[l_p]]++;
				l_p++;
				cnt++;
			}
			r_p++;
		}

		return min_len == INT_MAX ? "" : s.substr(start_pos, min_len);
	}
};