# include <vector>
# include <iostream>
# include <queue>
# include <algorithm>
# include <unordered_map>
# include <unordered_set>

using namespace std;

/*
现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。

可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组

*/

class Solution {
public:
	vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
		// BFS

		// 构造图的邻接表
		unordered_map<int, vector<int>> adj_table;
		// 获取每个结点的入度
		vector<int> in_deg(numCourses);
		for (auto&& x : prerequisites) {
			in_deg[x[0]]++;
			adj_table[x[1]].push_back(x[0]);
		}

		//将所有结点入度为0 入队
		queue<int> q;
		for (int i = 0; i < numCourses; i++) {
			if (in_deg[i] == 0) q.push(i);
		}

		vector<int> res;
		// 开始BFS
		while (!q.empty()) {
			// 弹出队首课程
			auto course = q.front();
			res.push_back(course);
			q.pop();
			numCourses--; // 所需的课程数-1

			// course指向所有结点的入度-1 如果入度-1后为0 则入队
			for (auto&& x : adj_table[course]) {
				in_deg[x]--;
				if (in_deg[x] == 0) q.push(x);
			}
		}

		return (numCourses == 0 ? res : vector<int>());
	}

	vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
		// DFS

		// 建立先修课程与要修课程的映射
		unordered_map<int, vector<int>> prev_to_next;
		for (auto&& x : prerequisites) prev_to_next[x[1]].push_back(x[0]);

		// 设置每个结点的状态
		vector<int> flags(numCourses);

		vector<int> res;
		for (int i = 0; i < numCourses; i++) {
			if (!dfs(i, res, flags, prev_to_next)) return vector<int>();
		}

		//  由于bfs是回溯 所以最初的结点在栈顶(vector末端) 最末的结点在栈底(vector首端) 故reverse再输出
		reverse(res.begin(), res.end()); 
		return res;
	}

	bool dfs(int course_id, vector<int>& res, vector<int>& flags, unordered_map<int, vector<int>>& prev_to_next) {
		if (flags[course_id] == 1) return false;
		if (flags[course_id] == 2) return true;

		flags[course_id] = 1;
		for (auto&& x : prev_to_next[course_id]) {
			if (!dfs(x, res, flags, prev_to_next)) return false;
		}
		flags[course_id] = 2;
		res.push_back(course_id); // 该结点遍历完且无环 将其入栈
		return true;
	}
};