# include <string>
# include <vector>
# include <algorithm>
# include <unordered_map>
# include <unordered_set>
# include <queue>
# include <map>

using namespace std;

/*
给定一个机票的字符串二维数组 [from, to]，子数组中的两个成员分别表示飞机出发和降落的机场地点，
对该行程进行重新规划排序。所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 开始。

提示：

如果存在多种有效的行程，请你按字符自然排序返回最小的行程组合。例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前
所有的机场都用三个大写字母表示（机场代码）。
假定所有机票至少存在一种合理的行程。
所有的机票必须都用一次 且 只能用一次。
 
*/

class Solution {
public:
	// Method 1 BFS+手动记忆路径 有bug
	vector<string> findItinerary(vector<vector<string>>& tickets) {

		int ticket_num = tickets.size();
		if (ticket_num == 0) return vector<string>();

		// 获得机票及其对应张数的哈希表
		map<pair<string, string>, int> ticket_hash; // 用pair做key 不能用unordered_map要用map
		unordered_map<string, vector<string>> adj_table;
		bool find_JFK = false;
		for (auto t : tickets) {
			if (t[0] == "JFK") find_JFK = true;
			adj_table[t[0]].push_back(t[1]);
			pair<string, string> tmp{ t[0],t[1] };
			ticket_hash[tmp]++;
		}

		// 没有从JFK起飞的机票
		if (!find_JFK) return vector<string>();

		//// 获取飞行记录 避免重复遍历
		//unordered_set<pair<string, string>> fly_records;

		// BFS队列
		queue<string> q;
		q.push("JFK");

		// 记录每一轮遍历的行程
		vector<unordered_map<string, vector<string>>> memo(ticket_num + 1);
		memo[0]["JFK"].push_back("JFK");
		// 
		int loop_cnt = 0;
		while (!q.empty()) {
			loop_cnt++;
			int now_cnt = q.size();
			for (int i = 1; i <= now_cnt; i++) {
				auto src = q.front();
				q.pop();

				vector<string> path = memo[loop_cnt - 1][src];
				if (path.size() == ticket_num + 1) goto End;
				else if (path.size() != ticket_num + 1 && adj_table.find(src) == adj_table.end()) {
					// 如果是无效路径 就要释放路径
					for (int i = 0; i < path.size() - 1; i++) {
						pair<string, string> ticket{ path[i],path[i + 1] };
						ticket_hash[ticket]++;
					}
				}

				for (auto&& des : adj_table[src]) {
					pair<string, string> ticket{ src,des };
					if (ticket_hash[ticket] == 0) continue;
					else {
						vector<string> tmp = path;
						// 记录目前路径
						ticket_hash[ticket]--;
						tmp.push_back(des);
						q.push(des);
						for (auto&& s : tmp) memo[loop_cnt][des].push_back(s);
					}
				}
			}
		}
	End:
		vector<vector<string>> res_lst;
		for (auto&& dict : memo[ticket_num]) {
			res_lst.push_back(dict.second);
		}
		vector<string> res = res_lst[0];
		for (int i = 1; i < res_lst.size(); i++) {
			vector<string> tmp = res_lst[i];
			if (nature_sort(res, tmp)) res = tmp;
		}
		return res;
	}

	bool nature_sort(vector<string>& res, vector<string>& tmp) {
		for (int j = 1; j < res.size(); j++) {
			if (res[j] != tmp[j]) {
				for (int k = 0; k < res[j].size(); k++) {
					if (char(tmp[j][k] < char(res[j][k]))) {
						return true;
					}
				}
			}
		}
		return false;
	}

	// Method 2 求欧拉通路(给定起点是从JFK) Hierholzer算法

	/*
	Step1 从起点出发，dfs
	Step2 每次沿着某条边从某个结点移动到另一个结点时，都要删除这条边
	Step3 如果没有可移动的路径，则将所在结点加入栈中 并回溯
	*/

	/*
	 由于该题保证了至少存在一种合理的路径 所以图是半欧拉图或欧拉图
	 若未说 则需要证明该图是半欧拉图或欧拉图
	 无向图证半欧拉图 G是连通且恰有2个奇度顶点
	 无向图证欧拉图   G是连通且没有奇度顶点
	 有向图证半欧拉图 G属于同一个强连通分量且
		 恰有一个顶点out_deg-in_deg=1 恰有一个一个顶点in_deg-out_deg=1 其它顶点入度和出度相同
	 有向图证欧拉图 G中所有顶点属于同一个强连通分量且每个顶点出入度相同
	*/
	vector<string> findItinerary(vector<vector<string>>& tickets) {
		
		// 记录每个结点及其邻居 邻居用优先队列存储(小顶堆) 堆顶为字典序最小的
		// 贪心策略 每次选字典序最小的
		unordered_map<string, priority_queue<string, vector<string>, greater<string>>> adj_table;
		for (auto&& t : tickets) adj_table[t[0]].push(t[1]);
		
		vector<string> res;
		dfs("JFK",res,adj_table);

		// 对于dfs来说 肯定是先遇到死胡同(入度-出度=1) 行程的最后一站 在更栈底的位置 而始发站肯定是最后一个入栈
		// 所以要将栈逆序输出
		reverse(res.begin(), res.end());
		return res;
	}

	void dfs(const string& start,vector<string>& res, unordered_map<string, priority_queue<string, vector<string>, greater<string>>>& adj_table) {
		while (adj_table.find(start) != adj_table.end() && adj_table[start].size() > 0) {
			// 保证有从start出发的机票 且保证以start为始点的边没有被走完
			string min_order = adj_table[start].top(); // 获取堆顶结点
			adj_table[start].pop();
			dfs(min_order,res,adj_table);
		}
		// 如果到了死胡同了 则按照算法流程 将结点入栈
		res.push_back(start);
	}
};

int main() {

	vector<vector<string>> test;
	test.push_back(vector<string>{"JFK", "SFO"});
	test.push_back(vector<string>{"JFK", "ATL"});
	test.push_back(vector<string>{"SFO", "ATL"});
	test.push_back(vector<string>{"ATL", "JFK"});
	test.push_back(vector<string>{"ATL", "SFO"});
	Solution obj;
	obj.findItinerary(test);
	return 0;
}