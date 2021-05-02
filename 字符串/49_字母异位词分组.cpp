# include <iostream>
# include <vector>
# include <algorithm>
# include <string>
# include <unordered_map>

using namespace std;

class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		// Method 1 哈希表 直接用哈希表存储
		int str_num = strs.size();
		if (str_num == 0) return vector<vector<string>>();

		vector<vector<string>> res;
		unordered_map<string, vector<string>> dict;
		for (int i = 0; i < str_num; i++) {
			string s = strs[i];
			sort(s.begin(), s.end());
			dict[s].push_back(strs[i]);
		}

		for (auto&& x : dict) res.push_back(x.second);

		return res;
	}
	/*void categorize(vector<string>& strs, vector<string>& vec,const int str_num,const string model) {

		for (int i = 0; i < str_num; i++) {
			if (strs[i] == "123") continue;

			if (strs[i].size() != model.size()) continue;

			string tmp = strs[i];
			sort(tmp.begin(), tmp.end());

			if (tmp == model) {
				vec.push_back(strs[i]);
				strs[i] = "123";
			}
		}
	}*/
};