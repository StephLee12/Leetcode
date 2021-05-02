# include <iostream>
# include <string>
# include <unordered_set>
# include <algorithm>
# include <unordered_map>

using namespace std;

/*
����һ���ַ����������ҳ����в������ظ��ַ��� ��Ӵ� �ĳ���
*/

class Solution {
public:
	//// Method 1 ������ ��set��¼ ˫��ѭ��
	//int lengthOfLongestSubstring(string s) {
	//	
	//	int len = s.size();

	//	if (len == 0) return 0;
	//	
	//	int max_len = 1;
	//	unordered_set<char> records;
	//	for (int i = 0; i < len-1; i++) {
	//		records.insert(s[i]);
	//		for (int j = i + 1; j < len;j++) {
	//			if (records.find(s[j]) == records.end()) records.insert(s[j]);
	//			else break;
	//		}
	//		max_len = max(max_len, (int)(records.size()));
	//		records.clear();
	//	}
	//	return max_len;
	//}

	//// Method 2 �ù�ϣ�� �洢���ֵ��ַ� �Ӷ��ж��ظ��ַ�
	//int lengthOfLongestSubstring(string s) {
	//	
	//	int len = s.size();
	//	// ֻ��Ҫ��¼�����ظ��ַ��Ľ�ǰλ�ü��� =>�ù�ϣ��
	//	int start_pos = 0;  // ��ǰ�ַ�������ʼ�±� 
	//	int max_len = 0;
	//	unordered_map<char, int> record; // ��¼�ظ��ַ����ֵ�λ��

	//	for (int i = 0; i < len; i++) {
	//		char c = s[i];
	//		if (record.find(c) != record.end() && record[c] >= start_pos) {
	//			// �������ظ��ַ�(record.find(c) != record.end())�Ҹ��ַ�λ�ڵ�ǰ�ַ�����(record[c]>=start_pos)
	//			// �ӽ�ǰ��һ���ַ�λ��+1 ��������
	//			start_pos = record[c] + 1; 
	//			record[c] = i; // �����ַ�c���ֵ�����λ��
	//		}
	//		else {
	//			// ��δ�����ظ��ַ� �������� 
	//			record[c] = i; // ��¼�ַ�c���ֵ�λ��
	//			max_len = max(max_len, i - start_pos + 1); // ����max_len
	//		}
	//	}
	//	return max_len;
	//}

	// Method 3 ��������
	int lengthOfLongestSubstring(string s) {
		
		if (s.size() == 0) return 0;

		int max_len = 1;
		int l_p = 0, r_p = 0;

		vector<int> dict(128, 0); // ��¼�ַ����ֵĴ���

		while (r_p < s.size()) {
			char c = s[r_p];
			if (dict[c] == 0) {
				// �����ǰԪ����֮ǰû���ظ� ������봰��
				dict[c]++;
			}
			else { // dict[c]!=0
				// �������ظ�Ԫ�� ��������
				while (s[l_p] != c) {
					// �ƶ�l_p ֱ��������c��ȵ��ַ�
					dict[s[l_p]]--;
					l_p++;
				}
				// �ƶ���ǰ���ڵ����
				dict[s[l_p]]--;
				l_p++;
				dict[c]++;
			}
			max_len = max(max_len, r_p - l_p + 1);
			r_p++;
		}

		return max_len;
	}

};

int main() {
	string test = "abcabcbb";
	Solution obj;
	obj.lengthOfLongestSubstring(test);
	return 0;
}