# include <string>
# include <vector>
# include <iostream>
# include <algorithm>
# include <unordered_map>
# include <set>

using namespace std;

/*
给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，

其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。

每个 Ai 或 Bi 是一个表示单个变量的字符串。

另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，

请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。

返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。

如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。

注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。

*/

class Solution {
public:
	vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
		// 建立有向图的邻接表 且每条边有对应的权值 key为head val为tail和edge value的pair
		unordered_map<string, vector<pair<string,double>>> adj_table;
		for (int i = 0; i < equations.size(); i++) {
			string head = equations[i][0]; string tail = equations[i][1];
			adj_table[head].push_back(pair<string, double>{tail,values[i]});
			adj_table[tail].push_back(pair<string, double>{head, 1.0/values[i]});
		}

		int q_num = queries.size(); // quries的数量
		set<pair<string, string>> records; // dfs记录遍历过的结点
		vector<double> res(q_num); // 结果数组
		for (int i = 0; i < q_num;i++) {
			auto q = queries[i];
			string head = q[0]; string tail = q[1];

			// 判断head和tail是否都是合法的
			bool flag = false;
			if (adj_table.find(head) != adj_table.end() && adj_table.find(tail) != adj_table.end()) flag = true;

			if (flag) {
				// 如果都是合法的
				double tmp = dfs(double(1), head, tail, adj_table, records);
				if (tmp == 0) res[i] = double(-1); // 如果没有找到arc到tail的路径 因为图不一定连通
				else res[i] = tmp;
			}
			else res[i]=double(-1); // 如果head或tail不是合法的 该query的值为-1
			records.clear(); // 清空records 进行下一轮dfs
		}
		return res;
	}

	double dfs(double val,string head, const string& tail, unordered_map<string, vector<pair<string, double>>>& adj_table, set<pair<string, string>>& records) {
		if (head == tail) return val; // 找到了从arc到tail的路径

		vector<pair<string, double>> neighbors = adj_table[head]; // 获取head的邻居结点
		bool dead = true; // dead为是否存在从head到tail的路 dead=true为不存在
		for (auto&& edge :neighbors) {
			string next_node = edge.first; double next_val = edge.second; // head的邻居 以及边的值
			if (records.find(pair<string, string>{head, next_node}) == records.end()) {
				// 这条边没有被遍历过
				records.insert(pair<string, string>{head, next_node}); // 记录该边
				double tmp = dfs(next_val, next_node, tail, adj_table, records);  // 从next_node继续dfs
				// 如果tmp=0 说明从next_node出发无法到tail
				if (tmp == 0) dead=true;
				else {
					// 如果tmp!=0 说明存在从next_node到tail的路径 直接break
					dead = false;
					val *= tmp;
					break;
				}
			}
		}

		return (dead ? 0 : val); // 如果不存在从arc到tail的路径 返回0 否则返回边的值
	}

};

int main() {
	vector<vector<string>> eqs;
	eqs.push_back(vector<string>{"a", "b"});
	eqs.push_back(vector<string>{"b", "c"});
	vector<double> vals{ double(2),double(3) };
	vector<vector<string>> quries;
	quries.push_back(vector<string>{"a", "c"});
	quries.push_back(vector<string>{"b", "a"});
	quries.push_back(vector<string>{"a", "e"});
	quries.push_back(vector<string>{"a", "a"});
	quries.push_back(vector<string>{"x", "x"});
	Solution obj;
	obj.calcEquation(eqs, vals, quries);
	return 0;

}