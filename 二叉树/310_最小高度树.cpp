# include <iostream>
# include <unordered_map>
# include <unordered_set>
# include <vector>
# include <queue>
# include <algorithm>

using namespace std;

/*
树是一个无向图，其中任何两个顶点只通过一条路径连接。 换句话说，一个任何没有简单环路的连通图都是一棵树。

给你一棵包含 n 个节点的树，标记为 0 到 n - 1 。给定数字 n 和一个有 n - 1 条无向边的 edges 列表（每一个边都是一对标签），其中 edges[i] = [ai, bi] 表示树中节点 ai 和 bi 之间存在一条无向边。

可选择树中任何一个节点作为根。当选择节点 x 作为根节点时，设结果树的高度为 h 。在所有可能的树中，具有最小高度的树（即，min(h)）被称为 最小高度树 。

请你找到所有的 最小高度树 并按 任意顺序 返回它们的根节点标签列表。

树的 高度 是指根节点和叶子节点之间最长向下路径上边的数量。

*/

class Solution {
public:
	// Method 1 暴力DFS 超时
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {

		
		if (n == 1) return vector<int>{0};
		else if (n == 2) return vector<int> {0, 1};

		// 建立树的邻接表 无向图
		unordered_map<int, vector<int>> prev_to_next;
		for (auto&& x : edges) {
			prev_to_next[x[0]].push_back(x[1]);
			prev_to_next[x[1]].push_back(x[0]);
		}

		vector<int> res;
		int min_height = INT_MAX;
		vector<int> flags(n);

		for (int i = 0; i < n; i++) {
			// 以每个结点为根结点 进行dfs遍历 每次遍历得到该结点的vector
			int height = dfs(0,i, prev_to_next, flags);
			// 如果该结点的高度小于最小高度 记录根结点 更新min_height
			if (height < min_height) {
				res.clear();
				res.push_back(i);
				min_height = height;
			}
			else if (height == min_height) res.push_back(i);
			for (auto&& x : flags) x = 0;
		}
		
		return res;

	}

	int dfs(int height,int node_id, unordered_map<int, vector<int>>& prev_to_next, vector<int>& flags) {
		
		if (flags[node_id] == 1) return height-1;
		
		flags[node_id] = 1; // 将结点设置为已遍历

		vector<int> store_height;
		for (auto&& x : prev_to_next[node_id]) store_height.push_back(dfs(height + 1, x, prev_to_next, flags));

		return *max_element(store_height.begin(), store_height.end());
	}

	// Method 2 用BFS 不断删除入度为1的结点 直到剩余的结点数量<=2 拓扑排序变式
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
		if (n == 1) return vector<int>{0};
		else if (n == 2) return vector<int> {0, 1};

		
		// 对于无向图来说 每个点的出度==入度

		// 建立邻接表 并获得每个点的入度
		unordered_map<int, vector<int>> adj_table;
		vector<int> in_deg(n);
		for (auto&& x:edges) {
			adj_table[x[0]].push_back(x[1]);
			adj_table[x[1]].push_back(x[0]);
			in_deg[x[0]]++;
			in_deg[x[1]]++;
		}

		// 入度为1的结点入队
		queue<int> q;
		for (int i = 0; i < n; i++) {
			if (in_deg[i] == 1) q.push(i);
		}

		// 删除到结点数量<=2时 循环停止
		while (n > 2) {
			int now_cnt = q.size(); // 当前队列的大小
			n -= now_cnt;
			for (int i = 0; i < now_cnt; i++) {
				auto node = q.front();
				q.pop();

				// node的邻居的入度-1
				for (auto&& x : adj_table[node]) {
					in_deg[x]--;
					if (in_deg[x] == 1) q.push(x);
				}
			}
		}

		vector<int> res;
		while (!q.empty()) {
			res.push_back(q.front());
			q.pop();
		}

		return res;
	}

	// Method 3 Longest Path(Diameter)
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
		
		// 图的直径 任意两点之间路径的最大值 直径上的中间点即为答案
		if (n == 1) return vector<int>{0};
		else if (n == 2) return vector<int> {0, 1};

		// 建立树的邻接表 无向图
		unordered_map<int, vector<int>> adj_table;
		for (auto&& x : edges) {
			adj_table[x[0]].push_back(x[1]);
			adj_table[x[1]].push_back(x[0]);
		}

		// 先随机选一个点x作为根结点 进行bfs/dfs 获得最远的结点y
		// 再从y进行bfs 找到最远结点z 从y到z就是图的直径 其中间结点即为答案
		vector<int> dis_1(n); // 第一次遍历
		vector<int> dis_2(n); // 第二次遍历
		vector<int> prev(n); // 记录前驱结点

		bfs(n,0, prev,dis_1, adj_table); // 以0为根结点 进行第一次遍历

		// 找到结点y
		int max_node = 0;
		for (int i = 1; i < n; i++) {
			if (dis_1[i] > dis_1[max_node]) max_node = i;
		}

		bfs(n, max_node, prev, dis_2, adj_table);

		// 找到结点z
		max_node = 0;
		for (int i = 1; i < n; i++) {
			if (dis_2[i] > dis_2[max_node]) max_node = i;
		}

		// 获取从z到y的路径
		vector<int> path;
		while (max_node != -1) {
			// y的前驱结点在bfs时设置为-1
			path.push_back(max_node);
			max_node = prev[max_node];
		}

		// 路径长为奇数 说明返回中间结点有1个
		if (path.size() % 2 == 1) return vector<int>{path[path.size() / 2] };
		// 路径长为偶数 说明返回中间结点有2个
		else return vector<int> {path[path.size() / 2], path[path.size() / 2 - 1]};

	}

	void bfs(int n,int root, vector<int>& prev, vector<int>& dis, unordered_map<int, vector<int>>& adj_table) {
		dis[root] = 0;
		prev[root] = -1;

		vector<int> visited(n);
		visited[root] = 1;

		queue<int> q;
		q.push(root);

		while (!q.empty()) {
			int now_cnt = q.size();
			for (int i = 1; i <= now_cnt; i++) {
				auto node = q.front();
				q.pop();

				for (auto&& x : adj_table[node]) {
					if (visited[x] == 0) {
						q.push(x);
						visited[x] = 1;
						prev[x] = node;
						dis[x] = dis[node] + 1;
					}
				}
			}
		}
	}
	 
	// Method 4 树形dp 
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
		
		if (n == 1) return vector<int>{0};
		else if (n == 2) return vector<int> {0, 1};

		// 建立树的邻接表 无向图
		unordered_map<int, vector<int>> adj_table;
		for (auto&& x : edges) {
			adj_table[x[0]].push_back(x[1]);
			adj_table[x[1]].push_back(x[0]);
		}

		vector<int> height_1(n); // 以x为根结点的下方的树的高度
		vector<int> height_2(n); // 以x为根结点的下方的树的第二高度 该数组对于向上搜索acc时有用
		vector<int> dp(n); // dp[i]即为i为根结点的树的高度

		dfs_down(0,-1,height_1,height_2,adj_table); // 向下dfs
		dfs_up(0, -1, 0, dp,height_1, height_2, adj_table); // 向上dfs

		// 找到最小高度
		int min_height = INT_MAX;
		for (int i = 0; i < n; i++) {
			if (dp[i] < min_height) min_height = dp[i];
		}

		// 找到符合最小高度的结点
		vector<int> res;
		for (int i = 0; i < n; i++) {
			if (dp[i] == min_height) res.push_back(i);
		}

		return res;
	}

	void dfs_down(int root,int parent, vector<int>& height_1, vector<int>& height_2, unordered_map<int, vector<int>>& adj_table) {
		for (auto&& node : adj_table[root]) {
			if (node != parent) {
				dfs_down(node, root, height_1, height_2, adj_table);
				int tmp = height_1[node] + 1;
				// 如果root的子结点node的高度+1 比现有的以root为根结点的树的高度还大
				// 更新height_1[root] 并将之前的height_1[root]赋给height_2[root]作为第二高高度
				if (tmp > height_1[root]) {
					height_2[root] = height_1[root];
					height_1[root] = tmp;
				}
				else if (tmp > height_2[root]) {
					// 如果小于最高高度 而大于第二高度 只更新第二高度
					height_2[root] = tmp;
				}
			}
		}
	}

	void dfs_up(int root, int parent, int acc, vector<int>& dp, vector<int>& height_1, vector<int>& height_2, unordered_map<int, vector<int>>& adj_table) {
		dp[root] = max(height_1[root], acc);
		for (auto&& node : adj_table[root]) {
			if (node != parent) {
				// 获得node的acc node的acc有两个可能 一个是承接root的acc 另一个是在node的兄弟中
				int node_acc = max(acc + 1, (height_1[root] == height_1[node] + 1 ? height_2[root] : height_1[root])+1);
				dfs_up(node, root, node_acc,dp,height_1,height_2,adj_table);
			}
		}
	}
};

int main() {
	vector<vector<int>> test;
	test.push_back(vector<int>{1, 0});
	test.push_back(vector<int>{1, 2});
	test.push_back(vector<int>{1, 3});
	Solution obj;
	obj.findMinHeightTrees(4, test);
	return 0;
}