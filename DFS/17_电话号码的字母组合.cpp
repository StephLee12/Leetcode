# include <vector>
# include <string>
# include <algorithm>
# include <iostream>
# include <unordered_map>

using namespace std;

/*
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。
*/

class Solution {
public:
	vector<string> letterCombinations(string digits) {
		// Method 1 DFS
		
		vector<string> res;

		// 特殊情况
		if (digits.empty()) return res;

		// 构建电话号码与对应数字的关系
		// char是单引号 string是双引号
		unordered_map<char, string> dict = {
			{'2',"abc"},{'3',"def"},{'4',"ghi"},
			{'5',"jkl"},{'6',"mno"},{'7',"pqrs"},
			{'8',"tuv"},{'9',"wxyz"}
		};

		dfs(digits, 0, digits.size(),dict, res,"");
		return res;
	}

	// pos是当前搜索到的digits的索引 len是digits的size
	void dfs(string digits,int pos, int len,unordered_map<char, string>& dict, vector<string>& res,string s) {
		if (pos > len-1) {
			// 当搜索完全之后 将字符串加入结果vector
			res.push_back(s);
			return;
		}

		// 获得当前pos下对应的数字 所对应的字母
		string corr_s = dict.at(digits[pos]);
		// 对每个字母再次dfs
		for (int i = 0; i < corr_s.size(); i++) {
			dfs(digits, pos + 1, len, dict, res, s + corr_s[i]);
		}

	}
};