# include <vector>
# include <stack>
# include <iostream>
# include <string>
# include <unordered_map>

using namespace std;

/*
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合

*/

class Solution {
public:
	bool isValid(string s) {
		// Method 1 用栈将( { [ 压入栈
		int len = s.size();

		stack<char> stk;
		stk.push(s[0]);
		unordered_map<char, char> dict = {
			{'(',')'},{'[',']'},{'{','}'}
		}; // 哈希表 匹配关系

		int p = 1;
		while (p<len) {
			// 如果是待匹配的字符 入栈
			if (s[p] == '(' || s[p] == '[' || s[p] == '{') stk.push(s[p]);

			if (s[p] == ')' || s[p] == ']' || s[p] == '}') {
				if (stk.empty()) return false; // 如果栈为空 且s[p]为上述字符 该串一定不能全部匹配成功
				// 判断栈顶字符和当前字符能否匹配
				char stk_top = stk.top();
				if (dict[stk_top] == s[p]) stk.pop();
				else return false;
			}
			p++;
		}

		// 如果栈为空 则说明串匹配完全 
		return (stk.empty() ? true : false);
	}
};

int main() {
	string test = "(){}}{"
}